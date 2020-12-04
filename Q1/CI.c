#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0644

#define NO_OF_STUDENTS 5

struct MsgBuffer {
	long mtype;
	char mtext[200];
};

int main() {
	struct MsgBuffer buf;
	int msgid;
	int len;
	key_t key;

	key_t keys[NO_OF_STUDENTS];
	int msgids[NO_OF_STUDENTS];
	system("touch CI-TA.txt");
	for (int i = 0; i < NO_OF_STUDENTS; i++) {
		char buffer_name[20];
		char tmp[20];
		sprintf(buffer_name, "S%d.txt", i + 1);
		sprintf(tmp, "touch %s", buffer_name);
		system(tmp);

		if ((keys[i] = ftok(buffer_name, 69 + i + 1)) == -1) {
			perror("msgget");
			exit(1);
		}

		if ((msgids[i] = msgget(keys[i], PERMS | IPC_CREAT)) == -1) {
			perror("msgget");
			exit(1);
		}
	}

	if ((key = ftok("CI-TA.txt", 69)) == -1) {
		perror("msgget");
		exit(1);
	}

	if ((msgid = msgget(key, PERMS | IPC_CREAT)) == -1) {
		perror("msgget");
		exit(1);
	}

	int marks[NO_OF_STUDENTS];

	printf("Enter marks:\n");
	for (int i = 0; i < NO_OF_STUDENTS; i++) {
		printf("S%d - ", i + 1);
		scanf("%d", &marks[i]);
	}

	int index = 0;
	for (int i = 0; i < NO_OF_STUDENTS; i++)
		index += sprintf(buf.mtext + index, "%d ", marks[i]);

	buf.mtype = 1;
	if (msgsnd(msgid, &buf, index + 1, 0) == -1)
		perror("msgsnd");
	
	if (msgrcv(msgid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
		perror("msgrcv");
		exit(1);
	}

	char grades[NO_OF_STUDENTS];

	for (int i = 0; i < NO_OF_STUDENTS; i++) {
		grades[i] = buf.mtext[i * 2];
	}

	printf("Grades-\n");

	for (int i = 0; i < NO_OF_STUDENTS; i++) {
		printf("S%d - %c\n", i + 1, grades[i]);
	}

	system("rm CI-TA.txt");

	if (msgctl(msgid, IPC_RMID, NULL) == -1) {
		perror("msgctl");
		exit(1);
	}
	
	for (int i = 0; i < NO_OF_STUDENTS; i++) {
		char buffer_name[20];
		char tmp[20];
		
		index = sprintf(buf.mtext, "%d ", marks[i]);
		buf.mtype = 1;
		if (msgsnd(msgids[i], &buf, index + 1, 0) == -1)
			perror("msgsnd");
		
	}
	printf("Done\n");

	return 0;
}
