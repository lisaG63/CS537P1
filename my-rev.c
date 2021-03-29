/* Copyright 2021 Weihang Guo */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    void reverse(FILE *file) {
        char buffer[100];
        while (fgets(buffer, 100, file) != NULL) {
            int length = strlen(buffer);
            char *begin, *end, temp;
            begin = buffer;
            if (buffer[length - 1] == '\n') {
                end = buffer + length - 2;
            } else {
                end = buffer + length - 1;
            }
            for (int i = 0; i < length / 2; i ++) {
                temp = *end;
                *end = *begin;
                *begin = temp;
                begin++;
                end--;
            }
            printf("%s", buffer);
        }
    }
    opterr = 0;
    int count = 0;
    int c;
    while ((c = getopt(argc, argv, "Vhf:")) != -1) {
        count++;
        switch (c) {
            case 'V':
                printf("my-rev from CS537 Spring 2021\n");
                exit(0);

            case '?':
                printf("my-rev: invalid command line\n");
                exit(1);

            case 'h':
                printf("Usage: ./my-rev [-V] [-h] [-f <filename>]\n\t");
                printf("V\tprints information about this utility\n\t-h\t");
                printf("prints help information\n\t-f\t");
                printf("uses <filename> as the input dictionary\n");
                exit(0);

            case 'f':

                if (argc != 3) {
                    printf("my-rev: invalid command line\n");
                    exit(1);
                }

                FILE *file = fopen(optarg, "r");
                if (file == NULL) {
                    printf("my-rev: cannot open file\n");
                    exit(1);
                }

                reverse(file);

                fclose(file);

                break;
        }
    }

    if (count == 0) {
        if (argc != 1) {
            printf("my-rev: invalid command line\n");
            exit(1);
        }

        reverse(stdin);
    }

        return 0;
}

