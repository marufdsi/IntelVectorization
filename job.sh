#!/bin/bash


#SBATCH -J myjob           # Job name
#SBATCH -o myjob.o%j	   # Name of stdout output file
#SBATCH -e myjob.e%j	   # Name of stderr error file
#SBATCH -p normal          # Queue (partition) name
#SBATCH -N 1               # Total # of nodes
#SBATCH -n 1              # Total # of mpi tasks
#SBATCH -t 00:50:00        # Run time (hh:mm:ss)

export OMP_NUM_THREADS=$1

./matmul.o
