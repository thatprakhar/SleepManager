#ifndef PROJECT_H
#define PROJECT_H

#define MAX_NAME_LEN (25)
#define DATA_EXISTS (0)
#define DATA_ADDED (1)


typedef struct node {
  int val;
  struct node* next;
} node_t;

typedef struct sleep_data {
  float avg_sleep;
  int data_size;
  node_t *months;
  node_t *date;
  node_t *years;
  node_t *sleep_hour;
} sleep_data_t; 



typedef struct user {
  char *name;
  int age;
  sleep_data_t *sleep_data;
} user_t;


user_t *create_user(char *, int);
int add_sleep_data(user_t *, int, int, int, float);
void write_user_data(user_t *);
void view_data(user_t *);
void free_user(user_t *);
void free_sleep_data(sleep_data_t *);
void show_options();
void handle_user_create();
#endif //PROJECT_H