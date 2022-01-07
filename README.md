# RingCommunication
Message passing around a ring topology network using MPI

## Description

Message Passing Interface (MPI) is a commonly used tool in HPC for communication between distributed memory systems. This repositpory illustrates the use of MPI to pass messages around a ring topology network. This is achieved by a given process passing a message to the neighbour on its right, and recieving messages from its left. 

The program determines the total of a sum of numbers, where each number is local only to its parent process. In this example the number is just the rank (the unique number given to the process in an MPI communicator). However, this number could be the result of a program run by an independent process or a part of a larger solution. The number is then passed to every process and added to the local total. Once the number has been fully passed around the ring the total is the same on all processes. The code shown will collect all of the local totals and use a 'gather' operation to collect them to the default rank, rank 0. This has been implemented to better simulate a real- world use case of this problem, such as collecting data on to an individual process to then be written to file or analysed further. 

### Note:

The code shown here is somewhat contrived and there is not expected to be any parallel speedup when compared to a serial implementation however as a coding exercise it is a great introduction to the features offeres by MPI. 

