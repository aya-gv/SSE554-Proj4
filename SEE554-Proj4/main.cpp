#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>
#include "time.h"

#include <iostream>

using namespace std;

static inline unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	//__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
	return ((unsigned long long)lo) | (((unsigned long long)hi) << 32);
}

//#define N 4
//#define N 8
//#define N 16
#define N 32
//#define N 64 //thread count

#define SIZE 1024 //1KB
//#define SIZE (32*1024) //32KB
//#define SIZE (256*1024) //256KB
//#define SIZE (512*1024) //512KB
//#define SIZE (1024*1024) //1MB
//#define SIZE (2*(1024*1024)) //2MB

int sum[N];
int *a;

int * fill_array(int *a) {
	int x;
	a = (int *)malloc((SIZE) * sizeof(int));
	for (x = 0; x < SIZE; x++) {
		a[x] = 1;
	}
	return a;
}

void *sum_thread(void *id, int *a) {
	int X = (int)id;
	int i;
	sum[X] = 0;
	for (i = X; i < SIZE; i += N) {
		sum[X] = sum[X] + a[i];
	}

	//printf("%d\n", sum);
	//printf("sum[%d] = %d\n", X, sum[X]);
	return NULL;
}

int print_sum(int n) {
	int x;
	int finalsum = 0;
	for (x = 0; x < n; x++) {
		finalsum = finalsum + sum[x];
	}
	return finalsum;
}

int main() {
	int x;
	pthread_t threads[N];
	void *exit_status;

	
	fill_array(a);

	unsigned long long start_time;
	unsigned long long end_time;

	start_time = rdtsc();

	for (x = 0; x < N; x++) {
		pthread_create(&threads[x], NULL, sum_thread, (void *)x);
	}

	for (x = 0; x < N; x++) {
		pthread_join(threads[x], &exit_status);
	}

	end_time = rdtsc() - start_time;
	printf("time: %.9f\n", end_time / (1.2 * 1000000000));
	cout << print_sum(N) << endl;

	int finalsum = 0;
	for(x = 0; x < N; x++) {
		finalsum = finalsum + sum[x];
	}
	free(a);

	printf("grand total: %d\n", finalsum);
	
	return 0;
}