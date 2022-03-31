#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Function not called properly.");
		exit(1);
	}
	key_t key = ftok("shmfile", 65);
	int shmid;
	shmid = shmget(key, 1024, 0666|IPC_CREAT);
	printf("Key of shared memory is %d\n", shmid);
	char *str = (char*) shmat(shmid, (void*)0, 0);
	char *boo = argv[1];
	for (int a = 0; a < strlen(argv[1]); a++) {
		str[a] = boo[a];
	}
	puts(str);
	shmdt(str);
	//shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
