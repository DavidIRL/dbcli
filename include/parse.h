#ifndef PARSE_H
#define PARSE_H

#define HEADER_MAGIC 0x4442574a

struct dbheader_t {
    unsigned int magic;
    unsigned short version;
    unsigned short count;
    unsigned int filesize;
};

struct employee_t {
    char name[64];
    char address[64];
    unsigned int hours;
};

int create_db_header(int fd, struct dbheader_t **headerOut);
int validate_db_header(int fd, struct dbheader_t **headerOut);
int read_emplyees(int fd, struct dbheader_t *, struct employee_t **employeesOut);
void output_file(int fd, struct dbheader_t *, struct employee_t *employees);


#endif















