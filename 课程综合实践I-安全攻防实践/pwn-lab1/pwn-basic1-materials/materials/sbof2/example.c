// gcc -no-pie -fno-stack-protector example.c -o example

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE (64)

void prepare()
{
	setvbuf(stdin, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
	alarm(60);
}

void never_reachable_backdoor()
{
	char *args[2] = {"/bin/sh", NULL};
	execve(args[0], args, NULL);
}

int main(int argc, char *argv[])
{
	int size;
	char buffer[BUFFER_SIZE];

	prepare();

	printf("size: ");
	scanf("%d", &size);

	printf("plase enter: ");
	read(STDIN_FILENO, buffer, size);
	return 0;
}