#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "common.h"
#include "file.h"
#include "parse.h"

void print_usage(char *argv[]) {
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\t -n - create a new database file\n");
    printf("\t -f - (required) path to database file\n");
    
    return 0;
}


int main(int argc, char *argv[]) {
    boot newfile = false;
    char *filepath = NULL;
    int c;

    while ((c = getopt(argc, argv, "nf:")) != -1) {
        switch (c) {
            case 'n':
                newfile = true;
            case 'f':
                filepath = optarg;
                break;
            case '?':
                printf("Unknown option - %c\n", c)
                break;
            default:
                return -1;
        }
    }

    if (filepath == NULL) {
        printf("Filepath is a required argument\n");
        print_usage(argv[]);

        return 0;
    }

    printf("Newfile: %d\n", newfile);
    printf("Filepath: %s\n", filepath);


    return 0;
}















