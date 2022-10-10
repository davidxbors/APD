#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 16

void *f(void *arg) {
  	long id = *(long*)arg;
	for (int i = 0; i < 100; ++i)
		printf("Hello World din thread-ul %ld; iteratia: %d!\n", id, i);
  	pthread_exit(NULL);
}

void *f1(void *arg) {
	long id = *(long*)arg;
	printf("f1 - thread id = %ld\n", id);
  	pthread_exit(NULL);
}

void *f2(void *arg) {
	long id = *(long*)arg;
	printf("f2 - thread id = %ld\n", id);
  	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
  	int r;
  	long id;
  	void *status;
	long ids[NUM_THREADS];

	long cores = sysconf(_SC_NPROCESSORS_CONF);
	printf("No cores: %ld\n", cores);

  	for (id = 0; id < NUM_THREADS; id++) {
		ids[id] = id;
		// r = pthread_create(&threads[id], NULL, f, &ids[id]);
		if (id % 2) {
			r = pthread_create(&threads[id], NULL, f1, &ids[id]);
		} else {
			r = pthread_create(&threads[id], NULL, f2, &ids[id]);
		}

		if (r) {
	  		printf("Eroare la crearea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	for (id = 0; id < NUM_THREADS; id++) {
		r = pthread_join(threads[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	pthread_exit(NULL);
}
