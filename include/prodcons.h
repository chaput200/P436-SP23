/* Global variable for producer consumer */
extern int n; /* this is just declaration */

/* Function Prototype */
void consumer(int count, sid32 sem_consumed, sid32 sem_produced);
void producer(int count, sid32 sem_consumed, sid32 sem_produced);
void prodcons_wrapper(int argc, char* argv[]);
