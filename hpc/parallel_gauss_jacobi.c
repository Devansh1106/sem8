// parallel gauss-jacobi method
// diagonal = n +1 
// vector = n*2

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double* matrix_vec_prod(double* A, double* vec, int n, double* result_vec, int size, MPI_Comm comm);

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    double* A=NULL;
    double* rhs_vec=NULL;
    double* diag=NULL;
    double* initial_guess=NULL;
    double* result_vec=NULL;
    double* temp=NULL;
    int n = 6; 
    int local_n = n/size;            // n % size should be 0 for now
    double start_time = 0.0;
    double end_time = 0.0, time = 0.0;
    double tol = 1.0;
    int iter = 0.0;
    double sum = 0.0;
    int flag = -1;

    if (rank == 0){
        printf("hi0");
        fflush(stdout);
        A = malloc(n * n * sizeof(double));
        rhs_vec = malloc(n * n * sizeof(double));
        diag = malloc(n * sizeof(double));
        initial_guess = calloc(n, sizeof(double));
        result_vec = calloc(local_n, sizeof(double));
        temp = calloc(n, sizeof(double));

        for(size_t i = 0; i < n; i++){
            for(size_t j = 0; j < n; j++){
                // B[i * n + j] = 2.0;
                A[i * n + j] = 1.0;
            }
            A[i * n] = 0.0;
            diag[i] = 1/(n + 1.0);
            rhs_vec[i] = 2*n;
        }
        printf("hi1");
        start_time = MPI_Wtime();
        MPI_Scatter(A, (local_n * n), MPI_DOUBLE, MPI_IN_PLACE, (local_n * n), MPI_DOUBLE, 0, comm);
        MPI_Scatter(diag, local_n, MPI_DOUBLE, diag, local_n, MPI_DOUBLE, 0, comm);
        MPI_Bcast(rhs_vec, n, MPI_DOUBLE, 0, comm);
        MPI_Bcast(initial_guess, n, MPI_DOUBLE, 0, comm); 
        end_time = MPI_Wtime();
        time = start_time - end_time;

    }
    else{
        printf("hi2");
        A = malloc(local_n * n * sizeof(double));
        rhs_vec = malloc(n * sizeof(double));
        initial_guess = calloc(n, sizeof(double));
        result_vec = calloc(local_n, sizeof(double));
        diag = malloc(local_n * sizeof(double));
        temp = calloc(local_n, sizeof(double));        

        MPI_Scatter(A, (local_n * n), MPI_DOUBLE, A, (local_n * n), MPI_DOUBLE, 0, comm);
        MPI_Scatter(diag, local_n, MPI_DOUBLE, diag, local_n, MPI_DOUBLE, 0, comm);
        MPI_Bcast(rhs_vec, n, MPI_DOUBLE, 0, comm);
        MPI_Bcast(initial_guess, n, MPI_DOUBLE, 0, comm); 
    }

    // start_time = MPI_Wtime();
    // MPI_Scatter(A, (local_n * n), MPI_DOUBLE, A, (local_n * n), MPI_DOUBLE, 0, comm);
    // MPI_Scatter(diag, local_n, MPI_DOUBLE, diag, local_n, MPI_DOUBLE, 0, comm);
    // MPI_Bcast(rhs_vec, n, MPI_DOUBLE, 0, comm);
    // MPI_Bcast(initial_guess, n, MPI_DOUBLE, 0, comm); 
    // end_time = MPI_Wtime();
    // time = start_time - end_time;


    start_time = MPI_Wtime();
    printf("hi3");
    fflush(stdout);
    while(tol > 1e-6 && iter != 5){
        printf("hi");
        sum = 0.0;
        result_vec = matrix_vec_prod(A, initial_guess, local_n, result_vec, size, comm);
        for (size_t i = 0; i < local_n; i++){
            temp[i] = rhs_vec[i] - result_vec[i];
            temp[i] = temp[i] * diag[i];
            sum += (temp[i] - initial_guess[i]);
        }
        MPI_Allgather(temp, local_n, MPI_DOUBLE, initial_guess, local_n, MPI_DOUBLE, comm);
        MPI_Allreduce(&sum, &tol, 1, MPI_DOUBLE, MPI_SUM, comm);
        iter++;
    }
    end_time = MPI_Wtime();
    if (rank == 0){
        if (iter == 2000){
            printf("Failed to converge, max iterations reached!\n");
            fflush(stdout);
        }
        else{
            MPI_Gather(temp, local_n, MPI_DOUBLE, temp, local_n, MPI_DOUBLE, 0, comm);
            printf("Solution: \n");
            for (size_t i = 0; i < n; i++){
                printf("%d ", temp[i]);
            }
        }
    }

    time += (start_time - end_time);

    if (rank == 0){
        // for (size_t i = 0; i < n; i++){
        //     for (size_t j = 0; j < n; j++){
        //         printf("%f\t", result_mat[j]);
        //     }
        //     printf("\n");
        // }
        printf("\nTime taken is: %f sec.\n", end_time - start_time);
    }
    free(A);
    free(rhs_vec);
    free(result_vec);
    free(temp);
    free(diag);
    free(initial_guess);

    MPI_Finalize();
    return 0;
}

double* matrix_vec_prod(double* A, double* vec, int n, double* result_vec, int size, MPI_Comm comm){
    int local_n = n/size;            // n % size should be 0 for now
    for(size_t i = 0; i < local_n; i++){
        for(size_t j = 0; j < n; j++){
            result_vec[i] += A[i * n + j] * vec[j];
        }
    }
    return result_vec;
    // MPI_Gather(result_vec, local_n, MPI_DOUBLE, result_vec, local_n, MPI_DOUBLE, 0, comm);
}