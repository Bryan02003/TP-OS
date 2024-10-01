#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>

int main()
{
    char *filename="Text.txt";
    int fd=open(filename,O_RDWR);

    if(fd==-1)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    struct stat file_stat;
    if(fstat(fd, &file_stat)==-1)
    {
        perror("Erreur lors de la récupération de la taille du fichier");
        close(fd);
        return EXIT_FAILURE;
    }   

    size_t file_size = file_stat.st_size;

    char *file_in_memory = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(file_in_memory==MAP_FAILED)
    {
        perror("Erreur lors du mapping");
        return EXIT_FAILURE;
    }

    for(size_t i=0;i<file_size/2;++i)
    {
        char temp=file_in_memory[i];
        file_in_memory[i]=file_in_memory[file_size-i-1];
        file_in_memory[file_size-i-1]=temp;

    }

    if (munmap(file_in_memory,file_size)==-1)
    {
        perror("Erreur lors du demapping mémoire");
    }

    close(fd);

    printf("Fichier inversé\n");
    system("cat Text.txt");


    return 0;
}