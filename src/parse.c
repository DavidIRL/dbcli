#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "common.h"
#include "parse.h"

//----------------------------------------------------------------//

int validate_db_header(int fd, struct dbheader_t **headerOut) {
    if (fd < 0) {
        printf("Bad file descriptor received\n");
        return STATUS_ERROR;
    }

    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (*header == -1) {
        printf("Failed to create db header\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(dbheader_t)) {
        free(header);
        return STATUS_ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->filesize = ntohl(header->filesize);
    
    if (header->magic != HEADER_MAGIC) {
        printf("Improper header magic\n");
        free(header);
        return -1;
    }

    if (header->version != 1) {
        printf("Improper header version\n");
        free(header);
        return -1;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if (header->filesize != dbstat.st_size) {
        printf("Database Corrupt\n");
        free(header);
        return -1;
    }

    *headerOut = header;
    return STATUS_SUCCESS;

}


int create_db_header(int fd, struct dbheader_t **headerOut) {
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (*header == -1) {
        printf("Failed to create db header\n");
        return STATUS_ERROR;
    }

    header->version = 0x1;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->filesize = sizeof(struct dbheader_t);

    *headerOut = header;
    return STATUS_SUCCESS;
}

void output_file(int fd, struct dbheader_t *dbhdr) {
    if (fd < 0) {
        printf("Bad file descriptor received\n");
        return;
    }

    dbhdr->version = htons(header->version);
    dbhdr->count = htons(header->count);
    dbhdr->magic = htonl(header->magic);
    dbhdr->filesize = htonl(header->filesize);

    lseek(fd, 0, SEEK_SET);

    write(fd, dbhdr, sizeof(struct dbheader_t));
    return;

}
