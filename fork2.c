#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	//check params
	if ( argc != 2 )
	{
        printf( "Usage: %s <dir> \n", argv[0] );
        exit(-1);
	}

	pid_t pid, child;
	int c_status;

	// fork another process
	child = fork();
	if (child < 0)
	{
		// error occurred
		printf("Fork failed\n");
		exit(-1);
	}
	else if (child == 0)
	{
		int ret;
		
		//char cwd[1024];
		//getcwd(cwd, sizeof(cwd));
		
		//char *directory = argv[1];
	
	
		//ret = chdir (directory);
		
		printf("Current working dir: %s\n", cwd);
		printf("Executing ls %s -all -l --all-readable\n",argv[1]);
		fflush(stdout);
		
		// child process
		//fflush(stdout);
		char* args[] = { "ls","-l","-all", "--human-readable", NULL };
//		char* args[] = { "ls", "-z", NULL };
		execvp(args[0], args);
	//	fprintf(stderr, "Error with execvp\n");
	//	exit(1);
	}
	else
	{
		// parent process
		// wait for the child to complete
		//printf("Parent PID=%d\n", getpid());
		pid = wait(&c_status);
		printf ("exited with status: %d\n", c_status);
		exit(0);
	}
}
