#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
using namespace std;

int main() {
	//Step One occurs
	puts("server started");
	int shmid;
	key_t key = ftok("shmfile", 65);
	shmid = shmget(key, 1024, 0666|IPC_CREAT);
	//Step two occurs below
	char *str = (char*) shmat(shmid, (void*)0, 0);
	puts("CLIENT REQUEST RECIEVED");
	puts("\tMEMORY OPEN");
	//Step three occurs
	puts(str);
	//Step four occurs below
	printf("\tOPENING: %s\n", str);
	FILE *in_file = fopen(str, "r");
	if (!in_file) {
		perror("fopen");
		exit(1);
	}
	struct stat sb;
	if (stat(str, &sb) == -1) {
		perror("stat");
		exit(1);
	}
	str = (char*) malloc(sb.st_size);
	char *file_contents =(char*) malloc(sb.st_size);
	//int index = 0;
	printf("The value of str is: %s\n", str);
	while (fgets(file_contents, sb.st_size, in_file)) {
		strcat(str, file_contents);
		//strcat(str, "\n");
	}
	fclose(in_file);
	shmdt(str);
	puts("\tFILE CLOSED");
	puts("\tMEMORY CLOSED");
	return 0;
}
