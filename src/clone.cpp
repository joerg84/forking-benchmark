#define _GNU_SOURCE
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sched.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)
#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */


static int              /* Start function for cloned child */
childFunc(void *arg)
{
  printf("BEFORE: child (sid, tid, pid, gpid, uid) %d %d %d %d %d\n",getsid(0), syscall(SYS_gettid), getpid(), getpgid(0), getuid());


  if (setsid() == -1) {
    errExit("Failed to put child in a new session");
  }
  if (setuid(200) == -1) {
    errExit("Failed to setuid()");
  }
  _exit(EXIT_SUCCESS);
  printf("After setsid/uid: child (sid, tid, pid, gpid, uid) %d %d %d %d %d\n",getsid(0), syscall(SYS_gettid), getpid(), getpgid(0), getuid());




  sleep(10);

  char *argv[] = { "echo", "hello", "world", NULL };
  char *environ[] = { NULL };
  execvpe("echo", argv, environ);

  return 0;           /* Child terminates now */
}


int
main(int argc, char *argv[])
{
  char *stack;                    /* Start of stack buffer */
  char *stackTop;                 /* End of stack buffer */
  pid_t pid;

  // create dummy
  char* x = new char;
  *x = 'a';

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  //printf("session id in Parent before:  %d\n", getsid(0) );
  printf("BEFORE: parent (sid, tid, pid, gpid, uid) %d %d %d %d %d\n",getsid(0), syscall(SYS_gettid), getpid(), getpgid(0), getuid());

  /* Allocate stack for child */

  stack = (char*)malloc(STACK_SIZE);
  if (stack == NULL) {
   errExit("malloc");
  }
  stackTop = stack + STACK_SIZE;  /* Assume stack grows downward */

  // CLONE_FS
  /* Create child that commences execution in childFunc() */
  pid = clone(childFunc, stackTop, CLONE_VFORK | CLONE_VM | SIGCHLD, (void *)x);
  if (pid == -1) {
    errExit("clone");
  }
  printf("clone() returned %ld\n", (long) pid);

  /* Parent falls through to here */

  if (waitpid(pid, NULL, 0) == -1)    /* Wait for child */
    errExit("waitpid");
  printf("child has terminated\n");

  printf("After clone parent: child (sid, tid, pid, gpid, uid) %d %d %d %d %d\n",getsid(0),
      syscall(SYS_gettid), getpid(), getpgid(0), getuid());

  printf("Dummy Var %c\n",*x);
  delete x;


  exit(EXIT_SUCCESS);
}
