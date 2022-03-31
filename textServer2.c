#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <sys/stat.h>

#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
using namespace std;

struct Memory {
	int status;
	int size;
	char *str[];
};

int main(int argc, char *argv[]) {
	if (argc != 1) {
		puts("Function not called properly.");
		exit(1);
	}
	key_t key;
	int shmid;
	struct Memory *shmptr;
	key = ftok("shmfile", 65);
	shmid = shmget(key, sizeof(struct Memory), 0666);
	if (shmid < 0) {
		puts("shmget error");
		exit(1);
	}
	shmptr = (struct Memory *) shmat(shmid, NULL, 0);
	if ((size_t) shmptr == -1) {
		puts("shmat error");
		exit(1);
	}
	printf("\tOPENING: %s\n", shmptr->str);
	char *boo;
	for (int a = 0; a < shmptr-> size; a++) 
		boo[a] = (size_t) shmptr-> str[a];
	FILE *in_file = fopen(boo, "r");
	if (!in_file) {
		perror("fopen");
		exit(1);
	}
	struct stat sb;
	if (stat(boo, &sb) == -1) {
		perror("stat");
		exit(1);
	}
	boo = (char*) malloc(sb.st_size);
	char *file_contents = (char*) malloc(sb.st_size);
	int counter = 0;
	while (fgets(file_contents, sb.st_size, in_file)) {
		char grd = *file_contents;
		boo[counter] = grd;
		counter++;
	}
	fclose(in_file);
	shmptr-> status = TAKEN;
	shmdt((void *) shmptr);
	exit(0);
}
