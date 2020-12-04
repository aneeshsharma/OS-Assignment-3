#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>

#define PERMS 0644

#define NO_OF_STUDENTS 5

struct MsgBuffer {
	long mtype;
	char mtext[200];
};


int nextInt(char* string, int* index, int* out) {
	int len = strlen(string);
	int num = 0;
	int neg = 1;
	while ((*index < len) && (string[*index])) {
		char c = string[*index];
		*index += 1;
		if (isdigit(c)) {
			num *= 10;
			num += (int) c - '0';
		} else if (c == '-') {
			neg = -1;
		} else if (c == ' ' || c == '\n' || c == '\r') {
			*out = neg * num;
			return 0;
		} else {
			return -1;
		}
	}
}

int main(int argc, char** argv) {
	struct MsgBuffer buf;
	int msgid;
	int toend;
	int std_id;
	key_t key;

	std_id = argv[1][0] - '0';

	char buffer_name[20];
	char tmp[50];

	printf("Student - %d\n", std_id);
	sprintf(buffer_name, "S%d.txt", std_id);

	
	if ((key = ftok(buffer_name, 69 + std_id)) == -1) {
		perror("ftok");
		exit(1);
	}


	if ((msgid = msgget(key, PERMS)) == -1) {
		perror("msgget");
		exit(1);
	}


	if (msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
		perror("msgrcv");
		exit(1);
	}

	int index = 0;
	int marks;

	if (nextInt(buf.mtext, &index, &marks) == -1) {
		perror("invalid text");
		exit(1);
	}

	printf("Marks - %d\n", marks);
	
	sprintf(buffer_name, "S%d.txt", std_id);
	sprintf(tmp, "rm %s", buffer_name);
	system(tmp);

	if (msgctl(msgid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	return 0;
}
