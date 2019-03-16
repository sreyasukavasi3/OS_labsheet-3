#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int shmid;
	char *str;
	shmid=shmget(IPC_PRIVATE,1024,IPC_CREAT|0666);
	//printf("%d",shmid);
	pid_t pid=fork();
	if(pid<0)
		printf("Fork failed");
	if(pid==0)
	{
		printf("Child: ");
		str=(char*)shmat(shmid, 0, 0);
		printf("Enter String: ");
		scanf("%s",str);
	}
	else
	{
		wait(NULL);
		str=(char*)shmat(shmid, 0, 0);
		int i=0;
		while(str[i]!='\0')
		{
			str[i]=toupper(str[i]);
			i++;
		}
		printf("Parent: Finale String: %s",str);
	}
	exit(0);
	return 0;
}
