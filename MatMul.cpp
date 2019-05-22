#include<iostream>
#include<stdlib.h>
#include<omp.h>

using namespace std;
void sequentialMatMul(){
  std::cout<<"Sequential Process Start"<<std::endl;
  int a[1000000], b[1000000], c[1000000];
#pragma novector
  for(int i=0; i<1000000; ++i){
    a[i] = i+1;
    b[i] = 1000000-i;
  }
  struct timespec start, end;
  double elapsed_time;
  clock_gettime(CLOCK_MONOTONIC, &start);
#pragma novector
  for(int i=0; i<1000000; ++i){
    #pragma novector
    for(int k=0; k<20; ++k)
      c[i] = a[i]*b[i];
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  elapsed_time = ((end.tv_sec * 1000 + (end.tv_nsec / 1.0e6)) - (start.tv_sec * 1000 + (start.tv_nsec / 1.0e6)));
  std::cout<<"Elapsed Time: " << elapsed_time << std::endl;
}


void parallelMatMul(){
  std::cout<<"Parallel Process Start"<<std::endl;
  int a[1000000], b[1000000], c[1000000];
  #pragma novector
  for(int i=0; i<1000000; ++i){
    a[i] = i+1;
    b[i] = 1000000-i;
  }

  struct timespec start, end;
  double elapsed_time;
  clock_gettime(CLOCK_MONOTONIC, &start);
  
#pragma novector
  for(int i=0; i<1000000; ++i){
    #pragma novector
    for(int k=0; k<20; ++k)
      c[i] = a[i]*b[i];
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  elapsed_time = ((end.tv_sec * 1000 + (end.tv_nsec / 1.0e6)) - (start.tv_sec * 1000 + (start.tv_nsec / 1.0e6)));
  std::cout<<"Elapsed Time: " << elapsed_time << std::endl;

}


void vectorizeMatMul(){
  std::cout<<"Vectorize Process Start"<<std::endl;
  int a[1000000], b[1000000], c[1000000];
#pragma omp simd
  for(int i=0; i<1000000; ++i){
    a[i] = i+1;
    b[i] = 1000000-i;
  }
  struct timespec start, end;
  double elapsed_time;
  clock_gettime(CLOCK_MONOTONIC, &start);
 
#pragma omp simd aligned(a, b: 32)
    for(int i=0; i<1000000; ++i){
      c[i] = a[i]*3;
    }
  
  clock_gettime(CLOCK_MONOTONIC, &end);
  elapsed_time = ((end.tv_sec * 1000 + (end.tv_nsec / 1.0e6)) - (start.tv_sec * 1000 + (start.tv_nsec / 1.0e6)));
  std::cout<<"Elapsed Time: " << elapsed_time << std::endl;
}

int main(int argc, char **argv){
  sequentialMatMul();
  parallelMatMul();
  vectorizeMatMul();
  return 0;
}
