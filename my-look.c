/* Copyright 2021 Weihang Guo */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    void look(FILE *file, const char *prefix) {
        char buffer[4096];
        while (fgets(buffer, 4096, file) != NULL) {
            if (strncasecmp(prefix, buffer, strlen(prefix)) == 0) {
                printf("%s", buffer);
            }
        }
    }


    if (argc < 2) {
        printf("my-look: invalid command line\n");
        exit(1);
    }


    opterr = 0;
    int count = 0;
    int c;
    while ((c = getopt(argc, argv, "Vhf:")) != -1) {
        count++;
        switch (c) {
            case 'V':
                printf("my-look from CS537 Spring 2021\n");
                exit(0);

            case '?':
                printf("my-look: invalid command line\n");
                exit(1);

            case 'h':
                printf("Usage: ./my-look [-V] [-h] [-f <filename>] prefix\n\t");
                printf("V\tprints information about this utility\n\t-h\t");
                printf("prints help information\n\t-f\t");
                printf("uses <filename> as the input dictionary\n\tprefix\t");
                printf("the string to look up for\n");
                exit(0);

            case 'f':
                if (argc != 4) {
                    printf("my-look: invalid command line\n");
                    exit(1);
                }

                FILE *file = fopen(optarg, "r");
                if (file == NULL) {
                    printf("my-look: cannot open file\n");
                    exit(1);
                }

                look(file, argv[3]);

                fclose(file);

                break;
        }
    }

    if (count == 0) {
        if (argc != 2) {
            printf("my-look: invalid command line\n");
            exit(1);
        }

        look(stdin, argv[1]);
    }

    return 0;
}
