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

char grade(int score, float avg) {
	float factor = 25 / avg;
	float rel = score * factor;
	printf("score - %d\tfactor - %f\trel - %f\n", score, factor, rel);
	if (rel >= 45)
		return 'S';
	if (rel >= 40)
		return 'A';
	if (rel >= 35)
		return 'B';
	if (rel >= 30)
		return 'C';
	if (rel >=25)
		return 'D';
	if (rel >= 20)
		return 'E';
	return 'F';
}

int main() {
	struct MsgBuffer buf;
	int msgid;
	int toend;
	key_t key;
	
	if ((key = ftok("CI-TA.txt", 69)) == -1) {
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
	int marks[NO_OF_STUDENTS];

	for (int i = 0; i < NO_OF_STUDENTS; i++) {
		if (nextInt(buf.mtext, &index, &marks[i]) == -1) {
			perror("invalid text");
			exit(1);
		}
	}

	printf("Marks-\n");

	for (int i = 0; i < NO_OF_STUDENTS; i++)
		printf("%d\n", marks[i]);

	float avg = 0;

	for (int i = 0; i < NO_OF_STUDENTS; i++)
		avg += marks[i];
	avg /= NO_OF_STUDENTS;

	printf("Avg - %f\n", avg);

	index = 0;
	for (int i = 0; i < NO_OF_STUDENTS; i++)
		index += sprintf(buf.mtext + index, "%c ", grade(marks[i], avg));

	if (msgsnd(msgid, &buf, index + 1, 0) == -1)
		perror("msgsnd");

	return 0;
}
