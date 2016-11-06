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

	pid_t child;
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
		//check to see if we can chdir
		if (chdir(argv[1]) != 0) 
		{
			//print error if cant and exit with status -1
			printf("Can't chdir to %s\n", argv[1]); 
			exit(-1);
		}
		else
			//if we can change directory then NIKE! (just do it)
			chdir (argv[1]);
		//create string to store current directory	
		char cwd[1024];
		//get current directory
		getcwd(cwd, sizeof(cwd));
		//print current directory
		printf("Current working dir: %s\n", cwd);						
		
		//we arent actually executing this exactly...
		//but this is what the parent sees the child do
		printf("Executing ls %s -all -l --all-readable\n",argv[1]);
		fflush(stdout);
		//So we changed directory
		//which means we need to run ls in current directory
		execl("/bin/ls", "ls", ".", "-all", "-l", "--human-readable", NULL);
		//So it looks like the child was... *takes off sunglasses*
		//"executed" YEEEEEEEEEEEEEAAAAAAAHHH!(csi miami)
	}
	else
	{
		// wait for the child to complete
		wait(&c_status);
		//shift c_status (-1) to 1
		c_status = c_status >> 15;
		printf ("exited with status: %d\n", c_status);
		exit(0);
	}
}
