#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
    schelet pentru exercitiul 5
*/
#define SERIAL 0
#define NUM_THREADS 5
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int* arr;
int array_size;

void *f(void *arg) {
    long id = *(long*)arg;
    int start = id * (double)array_size / NUM_THREADS;
    int end = MIN((id + 1) * (double)array_size / NUM_THREADS, array_size);
    for (int i = start; i < end; i++)
        arr[i] += 100;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    array_size = atoi(argv[1]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

#if SERIAL
    // TODO: aceasta operatie va fi paralelizata
  	// for (int i = 0; i < array_size; i++) {
    //     arr[i] += 100;
    // }
#else
    pthread_t threads[NUM_THREADS];
    int r;
    long id;
    void *status;
    long ids[NUM_THREADS];
    for (id = 0; id < NUM_THREADS; id++) {
        ids[id] = id;
        r = pthread_create(&threads[id], NULL, f, &ids[id]);
		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
    }
    for (id = 0; id < NUM_THREADS; id++) {
        r = pthread_join(threads[id], &status);
		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
    }
#endif

    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

  	pthread_exit(NULL);
}
