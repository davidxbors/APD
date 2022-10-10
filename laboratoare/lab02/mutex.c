#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

int a = 0;
pthread_mutex_t zavor;

void *f(void *arg)
{
	pthread_mutex_lock(&zavor);
	a += 2;
	pthread_mutex_unlock(&zavor);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	int i, r;
	void *status;
	pthread_t threads[NUM_THREADS];
	int arguments[NUM_THREADS];
	r = pthread_mutex_init(&zavor, NULL);
	if (r) {
		printf("Eroare la crearea mutex-ului %d\n", r);
		exit(-1);
	}

	for (i = 0; i < NUM_THREADS; i++) {
		arguments[i] = i;
		r = pthread_create(&threads[i], NULL, f, &arguments[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {
		r = pthread_join(threads[i], &status);

		if (r) {
			printf("Eroare la asteptarea thread-ului %d\n", i);
			exit(-1);
		}
	}

	printf("a = %d\n", a);

	r = pthread_mutex_destroy(&zavor);
	if (r) {
		printf("Erooare la crearea mutex-ului %d\n", r);
		exit(-1);
	}

	return 0;
}
