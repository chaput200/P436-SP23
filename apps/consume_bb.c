#include <xinu.h>
#include <prodcons_bb.h>

void consumer_bb(int c, int num_consumer_iterations, sid32 sem_consumed, sid32 sem_produced){
	for(int k =0; k<num_consumer_iterations; k++){
		wait(sem_produced);
		int r = arr_q[tail];
		printf("name : consumer_%d, read : %d\n",c, r);
		arr_q[tail] = 0;
		tail++;
		tail = tail % 5;
                signal(sem_consumed);
        }

}

