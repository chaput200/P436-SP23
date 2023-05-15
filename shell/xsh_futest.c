#include <xinu.h>
#include <future.h>
#include <stdlib.h>

extern sid32 print_sem;

syscall xsh_futest(int nargs, char *args[]) {
  print_sem = semcreate(1);
  future_t* f_exclusive;
  f_exclusive = future_alloc(FUTURE_EXCLUSIVE, sizeof(int), 1);

  // First, try to iterate through the arguments and make sure they are all valid based on the requirements
  //printf("NARGS IS: %d\n",nargs);
  //printf("ARGS IS: %s %s\n", args[1], args[2]);
  
  // IF NOT ENOUGH ARGS
  if(nargs < 3){
    fprintf(stderr, "Syntax: run futest [g ...] [VALUE ...]\n");
  }
  int i = 1;
  int num_get = 0;
  int num_set = 0;
  while (i < nargs) {
    // TODO: write your code here to check the validity of arguments
    // IF GETTER IS GIVEN 
    uint8 val = atoi(args[i]);
    //printf("val is %d\n", val);
    if(strcmp(args[i], "g") == 0){
      num_get++;
      //printf("num_get is %d\n", num_get);
    }
    //uint8 val = atoi(args[i]);
    // IF A SETTER
    else if(val != 0){
      num_set++;
      //printf("num_set is %d\n", num_set);
    }
    // IF IT IS NOT A G OR VALUE
    else{
      fprintf(stderr, "Syntax: run futest [g ...] [VALUE ...]\n");
    }
    //printf("testing\n");
    i++;
  }
  
  //CHECK IF NUM GETTERS AND SETTERS EQUAL
  /*if(num_get != num_set){
  	fprintf(stderr, "Syntax: number of getters and setters uneven");
  }*/

  // Iterate again through the arguments and create the following processes based on the passed argument ("g" or "VALUE")
 // printf("%d", i);
  i = 1;
  while (i < nargs) {
    if (strcmp(args[i], "g") == 0) {
      char id[10];
      sprintf(id, "fcons%d",i);
      resume(create(future_cons, 2048, 20, id, 1, f_exclusive));
    }
    else {
      uint8 number = atoi(args[i]);
      resume(create(future_prod, 2048, 20, "fprod1", 2, f_exclusive, number));
      sleepms(5);
    }
    i++;
  }
  sleepms(100);
  future_free(f_exclusive);
  return OK;
}


