#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[] )
{
	//check params
	if ( argc != 2 ) 
    {
        printf( "Usage: %s <dir> \n", argv[0] );
        exit(-1);
    }
	
	pid_t  pid;

	// fork another process
	pid = fork();

	if (pid < 0)
	{
		// error occurred
		printf("Fork failed\n");
		exit(-1);
	}
	else if (pid == 0)
	{
		// child process
		int ret;
		//changing directory
		char *directory = argv[1];
		ret = chdir (directory);
		
		//String for current working dir 
		char cwd[1024];
		//get cwd
		getcwd(cwd, sizeof(cwd));
		//print cwd
		printf("Current working dir: %s\n", cwd);
		
		//we arent actually executing this exactly...
		//but this is what the parent sees the child do
		printf("Executing ls %s -all -l --all-readable\n",argv[1]);
		fflush(stdout);
		//So we changed directory
		//which means we need to run ls in current directory
		ret = execl("/bin/ls", "ls", ".", "-all", "-l", "--human-readable", NULL);
		//So it looks like the child was... *takes off sunglasses*
		//"executed" YEEEEEEEEEEEEEAAAAAAAHHH!(csi miami)
	}
	else
	{
		// parent process
		// wait for the child to complete
		wait(NULL);
		exit(0);
	}
}
