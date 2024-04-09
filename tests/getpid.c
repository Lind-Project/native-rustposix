#undef _GNU_SOURCE
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include "lind_platform.h"

int main(void)
{
	lindrustinit(0);
	

	puts("printing pid");
	printf("%d\n", lind_getpid(1));
	puts("getpid() succeeded");
	lindrustfinalize();
	return 0;
}
