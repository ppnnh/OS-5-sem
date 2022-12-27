#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sched.h>

// sudo ./OS5_7
// ps -e -o uid,pri,ni,cmd|grep OS
void thread1() {
	pid_t pid = getpid();
	int cnice = nice(0);
	printf("nice %d\nz", cnice);
	
	for(int i = 0; i < 1000000000; i++) {
		if(i == 10) {
			cnice = nice(-10);
			printf("nice %d\n", cnice);
		}
		printf("TH1 OS05_07 main PID %d\n", pid);
		sleep(1);
	}
}

void thread2() {
	pid_t pid = getpid();
	for(int i = 0; i < 1000000000; i++) {
		printf("TH1  OS05_07 main PID %d\n", pid);
		sleep(1);
	}
}

int main() {
	pid_t pid;
	switch(pid = fork()) {
		case -1: 
			perror("fork");
			exit(1);
		case 0:
			thread1();
		default:
			thread2();
			wait(NULL);	
	}
}	
