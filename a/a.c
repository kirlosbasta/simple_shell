#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char str[]="i am who i am && i love it && ";

	char *cp=strtok(str,"&");
	printf("%s\n",cp);
	char *cp1=strtok(NULL,"&");
	printf("%s\n",cp1);
}
