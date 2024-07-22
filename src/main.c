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
    
    return;
}


int main(int argc, char *argv[]) {
    bool newfile = false;
    char *filepath = NULL;
    char *addstring = NULL;
    int c;
    int fdDb = -1;

    struct dbheader_t *dbhdr = NULL;
    struct emplyee_t *employees = NULL;

    while ((c = getopt(argc, argv, "nf:a:")) != -1) {
        switch (c) {
            case 'n':
                newfile = true;
            case 'f':
                filepath = optarg;
                break;
            case 'a':
                addstring = optarg;
                break;
            case '?':
                printf("Unknown option - %c\n", c);
                break;
            default:
                return -1;
        }
    }

    if (filepath == NULL) {
        printf("Filepath is a required argument\n");
        print_usage(argv);

        return 0;
    }

    if (newfile) {
        fdDb = create_db_file(filepath);
        if (fdDb == STATUS_ERROR) {
            printf("Cannot create database file\n");
            return -1;
        }
        
        if (create_db_header(fdDb, &dbhdr) == STATUS_ERROR) {
            printf("Failed to create database header\n");
            return -1;
        }
    } else {
        fdDb = open_db_file(filepath);
        if (fdDb == STATUS_ERROR) {
            printf("Cannot open database file\n");
            return -1;
        }

        if (validate_db_header(fdDb, &dbhdr) == STATUS_ERROR) {
            printf("Failed to validate database header\n");
            return -1;
        }

    }

    if (read_employees(fdDb, dbhdr, &employees) != STATUS_SUCCESS) {
        printf("Failed to read employee information\n");
        return 0;
    }

    if (addstring) {
        dbhdr->count++;
        employees = realloc(employees, dbhdr->count*(sizeof(struct emplyee_t)));

        add_employee(dbhdr, employees, addstring);
    }




    output_file(fdDb, dbhdr, employees);

    return 0;
}















