#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <unistd.h>
#define NOT_READY -1
#define  FILLED 0
#define TAKEN 1

struct Memory {
	int status;
	int size;
	char* str;
};

int main(int argc, char *argv[]) {
	if (argc != 3) {
		puts("Function not called correctly.");
		exit(1);
	}
	key_t key;
	int shmid;
	struct Memory *shmptr;
	//&shmptr -> str = argv[1];
        key = ftok("shmfile", 65);
	shmid =shmget(key, sizeof(struct Memory), 0666|IPC_CREAT);
		if (shmid < 0) {
			perror("shmget error.");
			exit(1);
		}
	shmptr = (struct Memory *) shmat(shmid, NULL, 0);
		if ((size_t) shmptr == -1) {
			puts("shamt error");
			exit(1);
		}
	shmptr-> status = NOT_READY;
	char *boo = argv[1];
	shmptr -> size = strlen(boo);
	for (int a = 0; a < strlen(boo); a++) {
		shmptr-> str[a] = boo[a];
	}
	shmptr-> status = FILLED;
	while (shmptr -> status != TAKEN)
		sleep(1);
	shmdt((void *) shmptr);
	shmctl(shmid, IPC_RMID,NULL);
	exit(0);
}
