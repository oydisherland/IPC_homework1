# Homework 1

## Task 1
 
###Description of code 
The file task1.c includes the function routine1(), which adds the two matrices A an B and stores the result in C. The function returns the calculation time in ns. In the main function routine1() function is executed 10 times with different matrix sizes each time. The calculation time is then printed. 

The task1.pbs file is for running the code on the cluster. In this file it the code is compiled and ran four times, using different compilation each time. 

###How to run the code 
The pbs file must be edited in order to run on the cluster. Under "Select the working directory", change "/home/oeydis.herland/homework1/task1.1" with the current path to the task1.c file. 

I ran task1.c on the cluster by writnig in the command promt:
- qsub task1.pbs 

## Task 2

###Description of code 
The file task2.c includes the function routine1(), which copies the elements from one matrix into another, but deviding the matrix into blocks and reversing the order of the blocks. The function returns the calculation time in ns. In the main function the function routine1() is executed four times, using different block sizes each time. 

The task2.pbs file is for running the code on the cluster. In this file it the code is compiled and ran four times, using different compilation each time.

###How to run the code 

The pbs file must be edited in order to run on the cluster. Under "Select the working directory", change "/home/oeydis.herland/homework1/task2.1" with the current path to the task2.c file. 

I ran task2.c on the cluster by writnig in the command promt:
- qsub task2.pbs 