/*------------------------------------------------------------------------
 * Cassandra Chaput
 * 2/1/2023
 * CSCI-P436
 * xsh_run - this file contains the code for command run to internal functions
 *------------------------------------------------------------------------
 */

#include <xinu.h>
#include <shprototypes.h>
#include <prodcons.h>
#include <prodcons_bb.h>

void futest_wrapper(int argc, char* argv[]);
void memtest_wrapper(int argc, char* argv[]);

sid32 sem;
//sid32 sem_bb;

shellcmd xsh_run(int argc, char * argv[]){
	sem = semcreate(0);
	//sem_bb = semcreate(0);
	//IF NUM ARGS TOO SMALL
	/*if(argc < 2){
                printf(stderr, "%s: not enough arguments\n", argv[0]);
        }*/

	//PRINT LIST OF AVAIL FUNCTIONS
	if((argc == 1) || (strncmp(argv[1], "list", 4) == 0)){
		printf("hello\n");
		printf("list\n");
		printf("prodcons\n");
        	printf("prodcons_bb\n");
		printf("futest\n");
		printf("memtest\n");
		return OK;
	}
	//DO HELLO
	else if(strncmp(argv[1], "hello", 13)==0){
		resume(create((void *) xsh_hello, 4096, 20, "hello", 2, argc-1, &argv[1]));
	}
	//DO PRODCONS_BB
	else if(strncmp(argv[1], "prodcons_bb", 15)==0){
        resume(create((void*)prodcons_wrapper_bb, 4096, 1, "prodcons_bb", 2, argc-1, &(argv[1])));
	}
	//DO PRODCONS
	else if(strncmp(argv[1], "prodcons", 8)==0){
		resume(create((void*)prodcons_wrapper, 4096, 1, "prodcons", 2, argc-1, &(argv[1])));
    	}
	//DO FUTURES
	else if(strncmp(argv[1], "futest", 6)==0){
		resume(create((void*)futest_wrapper, 4096, 1, "futest", 2, argc-1, &(argv[1])));
    	}
	// SO MEMTEST / MALLOC
	else if (strncmp(argv[1], "memtest", 7)==0){
		resume(create((void*)memtest_wrapper, 4096, 1, "memtest", 2, argc-1, &(argv[1])));
        }
	wait(sem);
	return 0;
}

void futest_wrapper(int argc, char* argv[]){
//	printf("IN WRAPPER");
	xsh_futest(argc, argv);
	signal(sem);
}

void memtest_wrapper(int argc, char* argv[]){
//	printf("IN WRAPPER");
        xsh_memtest(argc, argv);
        signal(sem);
}
