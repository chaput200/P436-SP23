
extern int arr_q[5];
extern int head;
extern int tail;

void prodcons_wrapper_bb(int argc, char* argv[]);
void consumer_bb(int p, int num_consumer_iterations, sid32 sem_consumed, sid32 sem_produced);
void producer_bb(int c, int num_consumer_iterations, sid32 sem_consumed, sid32 sem_produced);

