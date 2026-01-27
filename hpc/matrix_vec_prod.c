// matrix vector product (parallel)

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    int** A=NULL;
    int* vec=NULL;
    int n = 100;
    int local_n = n/size;               // n % size should be 0


    if (rank = 0){
        A = malloc(n * n * sizeof(int));
        for(size_t i = 0; i < n; i++){
            A[i] = malloc(n * sizeof(int));
            for(size_t j = 0; j < n; j++){
                A[i][j] = 1.0;
            }
        }
        MPI_Scatter();
    }
    else{
        A = malloc(local_n * local_n * sizeof(int));
        for(size_t i = 0; i < local_n; i++){
            A[i] = malloc(local_n * sizeof(int));
            for(size_t j = 0; j < local_n; j++){
                A[i][j] = 1.0;
            }
        }
    }

    for(size_t i = 0; i < local_n; i++){

    }



    MPI_Finalize();
    return 0;
}