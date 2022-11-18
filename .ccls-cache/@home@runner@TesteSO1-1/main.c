#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define exit_on_error(s, m)                                                    \
  if (s < 0) {                                                                 \
    perror(m);                                                                 \
    exit(1);                                                                   \
  }
#define F_OK 0
#define MAX_LINE_LENGTH 1000

/* lê caracteres do fifo. */
void ler_do_fifo(int fd, char nomeFicheiro[20]) {
	char arr1[90];
	long temp = 0;

	/* Este e o processo filho. */
	//close(fd);
	//ler_do_pipe(file);
	// Open FIFO for Read only
	fd = open(nomeFicheiro, O_RDONLY);

	// Read from FIFO
	read(fd, arr1, sizeof(arr1));

	char *p = &arr1;
	while (*p) { // While there are more characters to process...
		if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) {
			// Found a number
			long val = strtol(p, &p, 10); // Read number

			temp = val;
			//printf("%ld\n", temp); // and print it.
		} else {
			// Otherwise, move on to the next character.
			p++;
		}
	}

	dormida(temp);

	// Print the read message
	printf("Recebeu mensagem %s de %s ", arr1, nomeFicheiro);

	close(fd);
}

void dormida(long tempo) {
	//printf("Vou xonar: %ld", tempo);
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = tempo;
	nanosleep(&ts, NULL);
	//printf("Já xonei");
}

int main(int argc, char **argv) {

	int numeroClientes = 0;

	printf("Quantos clientes? ");
	scanf(" %d", &numeroClientes);
	if (numeroClientes == 0) {
		printf("Numero de argumentos invalido\n");
		exit(EXIT_SUCCESS);
	}

	if (argc >= 2) {
		argv[1] = "msgB";
	}

	if (argc >= 2) {
		char comando[200];
		puts("asd");
		sprintf(comando, "/bin/bash ./testscript.sh %s &", argv[1]);
		system(comando);
	}

	for (int i = 1; i <= numeroClientes; i++) {
		//puts("Estou no for");

		int file = 1;
		int fd = 0;

		char comando2[32];
		char nomeFicheiro[20];
		pid_t pid;

		/* Criar o processo filho. */
		pid = fork();

		if (pid == (pid_t) 0) {
			sleep(0.1);
			ler_do_fifo(fd, nomeFicheiro);
			//puts("já li");
			return EXIT_SUCCESS;
		} else if (pid < (pid_t) 0) {

			/* O fork falhou. */
			fprintf(stderr, "Fork falhou.\n");
			return EXIT_FAILURE;

		} else {
			sprintf(comando2, "fifo%i.txt %s &", i, argv[1]);
			sprintf(nomeFicheiro, "fifo%i.txt", i);

			if (access(nomeFicheiro, F_OK) == 0) {
				//remove(nomeFicheiro);
			}
			//mkfifo(nomeFicheiro, 0666 != 0
			if (0) {
				printf("erro ao criar FIFO %s ", nomeFicheiro);
			} else {
				printf("FIFO %s criado com sucesso! ", nomeFicheiro);
			}
		}

	}
	return 0;
}
