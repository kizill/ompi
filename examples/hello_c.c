/*
 * Copyright (c) 2004-2006 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2006      Cisco Systems, Inc.  All rights reserved.
 *
 * Sample MPI "hello world" application in C
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include "mpi.h"
#include <time.h> /* for the work function only */
#include <unistd.h>

int main(int argc, char* argv[])
{
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    int i, pid;
    int bcast_value = 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    printf("Hostname: %s\n", hostname);
    printf("Hello, world, I am %d of %d, (%s, %d)\n", rank, size, version, len);

    if (!rank) {
        bcast_value = 42;
    }
    MPI_Bcast(&bcast_value,1 ,MPI_INT, 0, MPI_COMM_WORLD );
    printf("%s\t- %d - %d - %d\n", hostname, rank, size, bcast_value);
    fflush(stdout);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}
