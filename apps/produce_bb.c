#include <xinu.h>
#include <prodcons_bb.h>

void producer_bb(int p, int num_producer_iterations, sid32 sem_consumed, sid32 sem_produced) {
        //printf("name : producer_%s,", );
        for(int k=0; k<num_producer_iterations; k++){
                wait(sem_consumed);
		arr_q[head] = k;
		head++;
		head = head % 5;
                printf("name : producer_%d, write : %d\n", p, k);
                signal(sem_produced);
        }
}


