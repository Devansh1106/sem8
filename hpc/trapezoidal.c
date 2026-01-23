#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

double fun(double x){
    return (pow(x,2.0))*exp(-x);
}

double trap(double a, double b, int local_n){
    // double* mesh;
    // mesh = malloc(local_n * sizeof(double));
    double h = (b-a)/(local_n-1);

    double approx = (fun(a) + fun(b))/2.0;
    for (size_t i = 0; i < local_n; i++){
        approx += fun(a + i*h);
    }
    approx = h*approx;
    return approx;
}


int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    int n;
    double a, b, local_area, area;
    double fun(double x);
    double trap(double a, double b, int local_n);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    a = 0; b = 1; n = 100;
    double h = (b-a)/size;
    int local_n = n/size;       // assuming n is divisible by size for now

    // for (size_t i = 0; i < size; i++){
    a = rank*h;
    b = a + (rank+1)*h;
    // }
    local_area = trap(a, b, local_n);

    MPI_Barrier(comm);
    MPI_Reduce(&local_area, &area, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

    if (rank == 0){
        printf("%f", area);
    }
    MPI_Finalize();

    
    return 0;
}