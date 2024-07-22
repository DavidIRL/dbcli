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
void list_employees(struct dbheader_t *, struct employee_t *);
int read_employees(int fd, struct dbheader_t *, struct employee_t **employeesOut);
int add_employees(struct dbheader_t *, struct employee_t *, char *addstring);
void output_file(int fd, struct dbheader_t *, struct employee_t *employees);


#endif















