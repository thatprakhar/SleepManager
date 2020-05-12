#ifndef PROJECT_H
#define PROJECT_H

#define MAX_NAME_LEN (25)
#define DATA_EXISTS (0)
#define DATA_ADDED (1)
#define INVALID_DATE (-1)
#define INVALID_SLEEP (-2)

typedef struct sleep_data {
  int month;
  int date;
  int year;
  int sleep_hour;
  struct sleep_data *next;
} sleep_data_t;


typedef struct user {
  char *name;
  int age;
  float avg_sleep;
  int data_size;
  sleep_data_t *sleep_data;
} user_t;


user_t *create_user(char *, int);
int add_sleep_data(user_t *, int, int, int, int);
void write_user_data(user_t *);
void view_data(user_t *);
void free_user(user_t *);
void free_sleep_data(sleep_data_t *);
void show_options();
void handle_user_create();
void handle_add_data();
#endif //PROJECT_H