// future_mode_t mode : MODE THE FUTURE WILL OP IN (ONLY FUTURE_EXCLUSIVE RN)
// uint size : SIZE OF DATA ELEMS IN BYTES
// uint nelem : NUMBER OF ELEMS (USED BY FUTURE_QUEUE) HARDCODE TO 1 RN

// FUTURE_EMPTY : STAE OF FUTURE AFTER ALLOCATION
// FUTURE_WAITING : FUTURES WAITED ON BY PROCESS - WAITING ENDS WHEN VAL OF FUTURE IS SET
// FUTURE_READY : FUTURE THAT HAS VAL - B/C  FUTURE_SET WAS CALLED
#include <xinu.h>
#include <stdio.h>
#include <future.h>

future_t* future_alloc(future_mode_t mode, uint size, uint nelem) {
	intmask mask;
	mask = disable();
	// TODO: write your code here
	// HARD CODE TO 1
	uint nelems = 1;
	// MAKE FUTURE
	future_t *f;
	// GETMEM TO ALLOCATE MEMORY - SIZE OF DATA ELEMS IN BYTES * NUM OF ELEMS & THE SIZE OF THE FUTURE
	f = (future_t *)getmem(sizeof(future_t));
	f->mode = mode;
	f->state = FUTURE_EMPTY;
	f->size = size;
	f->data = getmem(size);
	if(mode == FUTURE_EXCLUSIVE){
		restore(mask);
        	return f;
	}
	else{
		return SYSERR;
	}
}

//FREE ALLOCATED FUTURE 
syscall future_free(future_t* f){
	// SINCE I USED GETMEM USE FREEMEM
	intmask mask;
        mask = disable();
	restore(mask);
	//kill(f->pid)
	return freemem(f, sizeof(future_t) + f->size);
}

// GET VAL OF FUTURE (IF SET)
syscall future_get(future_t* f, void* out){
	intmask mask;
        mask = disable();
	// CHECK MODE
	if(f->mode == FUTURE_EXCLUSIVE){
		// CHECK FUTURE ISN'T WAITING
		if(f->state == FUTURE_WAITING){
			return SYSERR;
		}
		else if (f->state == FUTURE_READY){
			// CPY F->DATA INTO OUT BY SIZE OF F->DATA
			memcpy(out, f->data, f->size);
			f->state = FUTURE_EMPTY;
			return OK;
		}
		else if(f->state == FUTURE_EMPTY){
			// NOT SURE - MAYBE THE SAME AS READY BY CHECKING THE PID???
			f->state = FUTURE_WAITING;
			f->pid = getpid();
			suspend(f->pid);
			
			memcpy(out, f->data, f->size);
			return OK;
		}
	}
	restore(mask);
}

// SET VAL OF FUTURE
syscall future_set(future_t* f, void* in){
        intmask mask;
        mask = disable();
        // CHECK MODE
        if(f->mode == FUTURE_EXCLUSIVE){
                // CHECK FUTURE STATE 
                if(f->state == FUTURE_EMPTY){
                	memcpy(f->data, in, f->size);
			f->state = FUTURE_READY;
			return OK;
                }
		else if(f->state == FUTURE_READY){
			return SYSERR;
		}
		else if(f->state ==FUTURE_WAITING){
			memcpy(f->data, in, f->size);
			f->state = FUTURE_READY;
			resume(f->pid);
			return OK;
		}
        }
        restore(mask);
}



