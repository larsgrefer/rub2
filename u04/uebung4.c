#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	//ls -l /etc | wc -l 2>x >y
	
	pid_t pid;
	int fd[2], fdf;

	pid = fork();
	if (pid == 0) {
		pipe(fd);
	
		pid = fork();
		if (pid == 0) {
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			
			execlp("ls", "ls", "-l", "/etc", NULL);
		}
				
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		
		fdf = open("x", O_WRONLY | O_CREAT, 0600);
		dup2(fdf, STDERR_FILENO);
		close(fdf);
		
		fdf = open("y", O_WRONLY | O_CREAT, 0600);
		dup2(fdf, STDOUT_FILENO);
		close(fdf);
		
		execlp("wc", "wc", "-l", NULL);
	}
	
	wait(NULL);
	
	return EXIT_SUCCESS;
}
