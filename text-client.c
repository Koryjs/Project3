#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/stat.h>
//void readFile1()
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
	bool cycle = true;
	int counter = 0;
	while (cycle) {
		if (counter == 5) {
			cycle = false;
		}
		counter = counter+1;
		sleep(2);
	}
	shmctl(shmid, IPC_RMID, NULL);
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
	char *leng;
	leng = (char*) malloc(sb.st_size);
	char *file_contents = (char*) malloc(sb.st_size);
	while (fgets(file_contents, sb.st_size, in_file)) {
		strcat(leng, file_contents);
	}
	fclose(in_file);
	for (int a = 0; a < strlen(leng); a++) {
		printf("%c", (char) leng[a:]);
	}
	/*bool same = true;
	while (true) 
		if (strcmp(str, boo)!= 0)
			same = false;*/
	return 0;
}
