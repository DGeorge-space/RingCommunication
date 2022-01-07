#include <mpi.h>
#include <stdio.h>

int calculateTotal(int size)
{
	int total = size*(size-1)/2;

	return total;
}

void verifyCorrectness(int totals[], int size)
{	
	int totalCalculated = calculateTotal(size);	
	
	int success = 1;

	for (int i =0; i<size; i++)
	{

		if( totals[i] != totalCalculated)
		{
			success=0;
		}
	}
	if(success==1)
	{
		printf("Total verified to be %d \n", totalCalculated); 
	}
	else
	{
		printf("Incorrect result \n");
	}

}


int main()
{

	MPI_Comm world;
	MPI_Status status;


	int size;
	int rank;

	MPI_Init(NULL,NULL);
	
	world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &size);
	MPI_Comm_rank(world, &rank);

	//printf("Size of communicator: %d as told by rank %d \n", size, rank);

	int total[size];

	//initialise values to zero
	
	for(int i =0; i<size;i++)
	{
		total[i] =0;
	}
	
	int myval=rank;
	int recdval=0;
	int tag;
	
	//set Left and right Neighbours 

	int neighbourRight = (rank+1)%size;
	int neighbourLeft = (rank-1)%size;
	
	int count =0;

	total[rank] =rank;

	while(count <size-1)
	{

		MPI_Request request[size]; 

		MPI_Issend(&myval, 1, MPI_INT, neighbourRight, tag, world, &request[neighbourRight]);

		MPI_Irecv(&recdval, 1, MPI_INT, neighbourLeft, tag, world, &request[rank]);
		
		MPI_Wait(&request[rank], MPI_STATUS_IGNORE);

		total[rank]+=recdval;
		myval = recdval;
		count++;
	}

	int checkTotal = calculateTotal(size);
	

	//printf("rank: %d, total: %d, calculated total: %d \n", rank, total, checkTotal);
	
	int recieved[size];
	for (int i=0; i<size; i++)
	{
		recieved[i]=0;
	}


	MPI_Reduce(&total,&recieved,size, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);
	
	

	if(rank==0)
	{
		verifyCorrectness(recieved, size);
	}

	MPI_Finalize();


}


