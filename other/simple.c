#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#define RD_END 0
#define WR_END 1
int next_pipe(char **tab, int index)
{
    while (tab && tab[++index])
    {
        if (!strcmp(tab[index], "|"))
            return (index);
    }
    return (index);
}
char **sub_str_tab(char **av, int begin, int end)
{
    char **sub;
    int i = 0;

    if (!(sub = (char **)malloc(sizeof(char *) * (end - begin + 1))))
        return (NULL);
    while (begin < end)
    {
        // printf("av qu'on copie <%s>\n", av[begin]);
        sub[i++] = av[begin++];
    }
    // printf("i(%d) || begin(%d) || end(%d)\n", i, begin, end);
    sub[i] = 0;
    return (sub);
}

void execute_pipe(char **arg, char **env, int nb_pipes, int i, int *fd)
{
    int pipefd[2];
    pid_t pid;

    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        close(pipefd[RD_END]);
        dup2(*fd, STDIN_FILENO);
        if (i + 1 < nb_pipes)
            dup2(pipefd[WR_END], STDOUT_FILENO);
        close(pipefd[WR_END]);
        execve(arg[0], arg, env);
        // exit(0);    ca change rien puisqu on kill non ?
    }
    else
    {
        close(pipefd[WR_END]);
        waitpid(pid, NULL, 0);
        kill(pid, SIGTERM);
        if (i + 1 < nb_pipes)
            *fd = pipefd[RD_END];
        // close(pipefd[RD_END]);  /!\ ne surtout pas close
        free(arg);
    }
}

int main(int ac, char **av, char **env)
{
    int fd = 0;
    int i = 0;
    int nb = 1;
    int pipe_index = 0;

    if (ac < 2)
    {
        write(1, "gne", 3);
        return 1;
    }
    while ((i = next_pipe(av, i)) < ac)
        nb++;
    i = 0;
    while (i < nb)
    {
        int next = next_pipe(av, pipe_index);
        execute_pipe(sub_str_tab(av, pipe_index + 1, next), env, nb, i, &fd);
        pipe_index = next;
        i++;
    }
    return 0;
}
/*
// Nombre total de thread
#define NB_FORK 2
// Taille du message
#define LENGTH_MSG 30
// Tableau contenant le message
char message[LENGTH_MSG] = "";

// Fonction exécutée dans le fork
void job(int * tube) {
	int tid = getpid();
	// timer pour attendre maximum 5 secondes
	int i = 5;
	while (i > 0) {
		// lecture dans le tube
		if (read(*tube, message, LENGTH_MSG) > 0) {
			printf("Message du processus [%i] : %s", tid, message);
			break;
		}
		sleep(1);
	}
}
// Fonction qui attend chacun des processus fils
void waitForAll() {
	int status;
	pid_t pid;
	int n = 0;
	while (n < NB_FORK) {
		pid = wait(&status);
		n++;
	}
}

int main() {
	for (int i = 0; i < NB_FORK; i++) {
		int tube[2];
		pipe(tube);
		pid_t pid = fork();
		if (pid == -1) {
			// Il y a une erreur
			perror("fork");
			return EXIT_FAILURE;
		} else if (pid == 0) {
			// On est dans le fils
			close(tube[1]);
			job(&tube[0]);
			close(tube[0]);
			exit(EXIT_SUCCESS);
		} else {
			// On est dans le père
			// Ecriture du message dans le tableau
			sprintf(message, "Fork[%i],i'm yo dad!\n", pid);
			// Ecriture du message dans le tube
			write(tube[1], message, LENGTH_MSG);
			close(tube[0]);
			close(tube[1]);
		}
	}
	waitForAll();
	return EXIT_SUCCESS;
} */