/*------------------------------------------------------------------------
 * xsh_prodcons - this file contains the code pertaining to prodcons command
 *------------------------------------------------------------------------
 */

#include <xinu.h>
#include <prodcons.h>
//#include <semaphore.h>

//GLOBAL VAR N DEFINITION
int n;

// GLOBAL ARRAY DEF
int arr_q[5];

sid32 sem, sem_consumed, sem_produced;

void prodcons_wrapper(int argc, char* argv[]){
	//printf("IN WRAPPER");
	xsh_prodcons(argc, argv);
	signal(sem);
}


shellcmd xsh_prodcons(int nargs, char * args[]){
	//ARGUMENT VERIFY
        int count; // LOCAL VAR COUNT
	sem_produced = semcreate(0);
        sem_consumed = semcreate(1);

	//IF NUM ARGS TOO BIG
	if(nargs > 2){
                fprintf(stderr, "%s: not enough arguments\n", args[0]);
        }

	// IF NUM ARGS CORRECT
	if(nargs == 2){
		//ARGUMENT VERIFY
		count = atoi(args[1]);
		//printf("COUNT IS %d\n", count);
                
		// CREATE PRODUCE PROCESS
                resume(create(producer, 200, 20, "producer", 3, count, sem_consumed, sem_produced));
		// CREATE CONSUME PROCESS
		resume(create(consumer, 200, 20, "consumer", 3, count, sem_consumed, sem_produced));
	}

	// IF NUM ARGS TOO SMALL
        if(nargs == 1){
		//REMOVE LAB 02 COUNT
		//count = 2000;
		
		//LAB 03 NEW COUNT = 200
		count = 200;
                //printf("COUNT IS %d\n", count);
                
		// CREATE PRODUCE PROCESS
                resume(create(producer, 200, 20, "producer", 3, count, sem_consumed, sem_produced));
		//CREATE CONSUME PROCESS
		resume(create(consumer, 200, 20, "consumer", 3, count, sem_consumed, sem_produced));
	}
	
	
	// IF NUM ARGS TOO SMALL
	if(nargs < 1){
		fprintf(stderr, "%s: not enough arguments\n", args[0]);
	}
	return 0;
}




