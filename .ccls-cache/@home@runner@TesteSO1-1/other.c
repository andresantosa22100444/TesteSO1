#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void dormida(long tempo) {
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = tempo;
  nanosleep(&ts, NULL);
}

void lerFifo(char *nomeDoFicheiro) {

  FILE *fp;
  fp = fopen(nomeDoFicheiro, "r");

  long sono;
  char texto[500];

  fscanf(fp, "%s %ld", texto, &sono);

  dormida(sono);

  printf("Recebeu mensagem %s %ld de %s\n", texto, sono, nomeDoFicheiro);

  fclose(fp);
}

int main(int argc, char **argv) {

  int numeroClientes = 0;

  puts("Quantos clientes?");
  scanf(" %d", &numeroClientes);

  if (numeroClientes == 0) {
    printf("Numero de argumentos invalido\n");
    exit(EXIT_FAILURE);
  }

  if (argc >= 2) {
    char comando[100];
    sprintf(comando, "/bin/bash ./testscript.sh %s &", argv[1]);
    system(comando);
  }

  for (int i = 1; i <= numeroClientes; i++) {

    char nomeDoFicheiro[35];
    sprintf(nomeDoFicheiro, "fifo%i.txt", i);
    // Se ficheiro existe apaga
    if (access(nomeDoFicheiro, F_OK) == 0) {
      remove(nomeDoFicheiro);
    } else {
    }

    mkfifo(nomeDoFicheiro, 0666);

    printf("FIFO %s criado com sucesso!\n", nomeDoFicheiro);
  }

  for (int i = 1; i <= numeroClientes; i++) {

    char nomeDoFicheiro[35];
    pid_t pid;

    sprintf(nomeDoFicheiro, "fifo%i.txt", i);
    pid = fork();

    if (pid != 0) { // processo pai

      while (wait(NULL) > 0) {
      }
      exit(EXIT_SUCCESS);

    } else {

      lerFifo(nomeDoFicheiro);
    }
  }
  return 0;
}