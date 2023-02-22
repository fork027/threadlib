#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

struct uthread_tcb {
    uthread_ctx_t ctx;    // thread context
    void *stack;          // pointer to the bottom of the thread's stack
    uthread_func_t func;  // thread function
    void *arg;            // argument to the thread function
    bool blocked;         // whether the thread is blocked
    bool exited;          // whether the thread has exited
};

struct uthread_tcb *uthread_current(void)
{
  return (struct uthread_tcb *) uthread_ctx_get();
  
}

void uthread_yield(void)
{
	struct uthread_tcb *current = uthread_current();
  struct uthread_tcb *next = uthread_next();
  uthread_ctx_switch(&current->ctx, &next->ctx);
}

void uthread_exit(void)
{
	struct uthread_tcb *current = uthread_current();
  current->exited = true;
  uthread_yield();
}

int uthread_create(uthread_func_t func, void *arg)
{
  struct uthread_tcb *thread = (struct uthread_tcb *) malloc(sizeof(struct uthread_tcb));
  if (thread == NULL) {
      return -1;
  }
  thread->stack = uthread_ctx_alloc_stack();
  if (thread->stack == NULL) {
      free(thread);
      return -1;
  }
  if (uthread_ctx_init(&thread->ctx, thread->stack, func, arg) != 0) {
      uthread_ctx_destroy_stack(thread->stack);
      free(thread);
      return -1;
  }
  thread->func = func;
  thread->arg = arg;
  thread->blocked = false;
  thread->exited = false;
  uthread_add(thread);
  return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	// create initial thread
	// return uthread_create(func, arg);

	// while (there is a thread) 
		// yield to next thread
	
}

void uthread_block(void)
{
	/* TODO Phase 3 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 3 */
}


///Users/jessicaeaton/projects/threads/libuthread/uthread.c