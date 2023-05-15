/*------------------------------------------------------------------------
 * xsh_prodcons_bb - this file contains the code pertaining to prodcons_bb command
 *------------------------------------------------------------------------
 */

#include <xinu.h>
#include <prodcons_bb.h>

// DECLARE SEMAPHORE & ARR_Q ARRAY
int arr_q[5];
sid32 sem, sem_produced, sem_consumed;
int head = 0;
int tail = 0;

void prodcons_wrapper_bb(int argc, char* argv[]){
        //printf("IN WRAPPER\n");
        xsh_prodcons_bb(argc, argv);
        signal(sem);
}

shellcmd xsh_prodcons_bb(int nargs, char * args[]){
        //printf("got to bb\n");
	sem_produced = semcreate(0);
	sem_consumed = semcreate(1);
        //printf("%d %s", nargs, args[0]);

        //IF NUM ARGS TOO BIG
        if(nargs > 5){
                fprintf(stderr, "%s: too many arguments\n", args[0]);
        }
        //NUM ARGS TOO SMALL
        else if (nargs < 5){
                fprintf(stderr, "%s: not enough arguments\n", args[0]);
        }
        // NUM ARGS JUST RIGHT LOL
        else if (nargs == 5){
		//printf("GOT TO == 5\n");
                int num_producers = atoi(args[1]);
                int num_consumers = atoi(args[2]);
                int num_producer_iterations = atoi(args[3]);
                int num_consumer_iterations = atoi(args[4]);
	
	
		// CREATE 0 TO NUM_PRODUCERS-1 PROCESSES
               	for(int k=0; k<num_producers; k++){
                       	//printf("%s\n", p);
			resume(create(producer_bb, 200, 20, "p", 4, k, num_producer_iterations, sem_consumed, sem_produced));
               	}

		// CREATE 0 TO NUM_CONSUMER-1 PROCESSES
               	for(int k=0; k<num_consumers; k++){	
			//printf("%s\n", c);
			resume(create(consumer_bb, 200, 20, "c", 4, k, num_consumer_iterations, sem_consumed, sem_produced));
               	}
       
	}
}

