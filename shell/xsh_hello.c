/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - create hello command which takes a single string and print "hello <string>, welcome to xinu!!"
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int argc, char * argv[]){
	//CHECK NUM ARGS
	//IF NUM ARGS TOO SMALL
	if(argc < 2){
		fprintf(stderr, "%s: not enough arguments\n", argv[0]);
		return 1;
	}
	//IF NUM ARGS TOO BIG
	if(argc > 2){
                fprintf(stderr, "%s: too many arguments\n", argv[0]);
                return 1;
        }

	//IF NUM ARGS CORRECT
	if(argc == 2){
		printf("Hello %s, Welcome to the world of Xinu!!\n", argv[1]);
	}
	return 0;

}
