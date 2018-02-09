#ifndef roulette
#define roulette

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <time.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define exit_on_error(s,m) if ( s < 0 ) { perror(m); exit(1); }
#define exit_on_null(s,m) if (s== NULL) { perror(m); exit(1);}

#define INTERVAL 60

#define BUY 100
#define BET 101
#define BET_CANCEL 102
#define BALANCE 103
#define PL_MAX 6



typedef struct
{
	long type;
	int pid;
	int operation;

	union {
		  struct
		  	{
			int cash_value;
			int credits;
		  	} buy;
		  
	 	  struct
		  	{
			int credits;
			int bet_no;
		  	} bet;
		  
		  struct
			{
			char lot[50];
			} status;
	     } request;
} message;

//shmem struct creditos
typedef struct
{
	int pid;
	int credits;
} credit;

//shmem struct mesa
typedef struct
{
	int pid;
	int credits;
	int num;
} table;

#define SIZEOF_MSG (sizeof(message) - sizeof(long))
#endif
