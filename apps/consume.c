#include <xinu.h>
#include <prodcons.h>


void consumer(int count, sid32 sem_consumed, sid32 sem_produced) {
  // TODO: implement the following:
  // - Iterates from 0 to count (count including)
  //   - reading the value of the global variable 'n' each time
  //   - print consumed value (the value of 'n'), e.g. "consumed : 8"

	//LAB 02 WORK
	/*for(int i=0; i<count+1; i++){
		printf("CONSUMED: %d\n", n);
	}*/
	
	//LAB 03 WORK
	for(int i=0; i<=count; i++){
                wait(sem_produced);
		printf("consumed : %d\n", n);
		signal(sem_consumed);
       }
}


