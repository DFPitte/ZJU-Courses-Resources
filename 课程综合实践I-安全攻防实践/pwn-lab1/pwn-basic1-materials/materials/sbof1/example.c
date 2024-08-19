// gcc -g -fno-stack-protector example.c -o example
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 64

void get_admin_password(char *buf)
{
	int fd = open("password.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("something wrong\n");
		exit(-1);
	}
	read(fd, buf, BUFFER_SIZE);
	close(fd);
}

int main(int argc, char* argv[])
{
	char password[64] = {0};
	char input[64] = {0};
	bool verified = false;

	get_admin_password(password);
	gets(input);

	if (strcmp(input, password) == 0) {
		verified = true;
	}

	if (verified)
		puts("Access Granted");
		// ...
	else
		puts("Access Failed");
		// ...

	return 0;
}
