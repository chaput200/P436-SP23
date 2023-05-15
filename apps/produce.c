#include <xinu.h>
#include <prodcons.h>

void producer(int count, sid32 sem_consumed, sid32 sem_produced) {  
	for(int i=0; i<=count; i++){
		//COMMENTING OUT WORK FROM LAB 02
		//n = i;
        	//printf("PRODUCED: %d\n", n);
		
		//LAB 03 WORK
		wait(sem_consumed);
		n=i;
		printf("produced : %d\n", n);
		signal(sem_produced);
	}
}

