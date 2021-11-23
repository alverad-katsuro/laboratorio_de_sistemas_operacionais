#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    char fn[10], buff[100];
    int fd, n, i;
    printf("Entre com o nome de um arquivo novo:\n");
    scanf("%s", fn);
    printf("\nEntre com um texto qualquer:");
    scanf("%s", buff);
    //fgets consome os chars de buff
    //fgets(buff, 100, stdin);
    fd = open(fn, O_CREAT|O_WRONLY, 0764);
    n = write(fd, buff, strlen(buff));
    close(fd);
    printf("\n\nVeja o conteúdo do arquivo criado\n");
    return 0;
}