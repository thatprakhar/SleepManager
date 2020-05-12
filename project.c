#include "project.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

/*
 * Method to create a user
 */

user_t *create_user(char *name, int age) {
  assert(name);
  assert(age > 0);

  user_t *new_user = NULL;
  new_user = malloc(sizeof(user_t));
  assert(new_user);

  new_user->name = malloc(strlen(name) > 25 ? 25 : strlen(name));
  assert(new_user->name);
  strncpy(new_user->name, name, strlen(name) > 25 ? 25 : strlen(name));
  new_user->age = age;
  new_user->sleep_data = NULL;

  return new_user;
}

/*
 * Method to add sleep data
 */

int add_sleep_data(user_t *user, int date, int month, int year, float sleep_hour) {
  assert(user);
  assert(date > 0 && date <= 31);
  assert(month > 0 && month < 13);
  assert(year > 0);
  float total_sleep = 0;

  node_t * month_ptr = user->sleep_data->months;
  node_t * date_ptr = user->sleep_data->date;
  node_t * year_ptr = user->sleep_data->years;
  node_t *sleep_ptr = user->sleep_data->sleep_hour;

  while (date_ptr->next != NULL) {
    if (date_ptr->val == date && month_ptr->val == month && month_ptr->val == month) {
      return DATA_EXISTS;
    }
    total_sleep += sleep_ptr->val;
    sleep_ptr = sleep_ptr->next;
    month_ptr = month_ptr->next;
    date_ptr = date_ptr->next;
    year_ptr = year_ptr->next;
  }

  month_ptr->next = malloc(sizeof(node_t));
  assert(month_ptr->next);
  month_ptr->next->val = month;

  date_ptr->next = malloc(sizeof(node_t));
  assert(date_ptr->next);
  date_ptr->next->val = date;

  year_ptr->next = malloc(sizeof(node_t));
  assert(year_ptr->next);
  year_ptr->next->val = year;

  sleep_ptr->next = malloc(sizeof(node_t));
  assert(sleep_ptr->next);
  sleep_ptr->next->val = sleep_hour;
  
  user->sleep_data->data_size++;
  total_sleep += sleep_hour;

  user->sleep_data->avg_sleep = total_sleep / user->sleep_data->data_size;

  return DATA_ADDED;
}

/*
 * Writes the user sleep data in
 * a text file with their name
 */

void write_user_data(user_t *user) {
  assert(user);

  FILE *file_ptr = NULL;
  file_ptr = fopen(strcat(user->name, ".txt"), "w");

  fprintf(file_ptr, "|------Sleep Data------|\n");
  fprintf(file_ptr, "Name: %s\n", user->name);
  fprintf(file_ptr, "Age: %d\n", user->age);
  fprintf(file_ptr, "Record Size: %d\n", user->sleep_data->data_size);
  fprintf(file_ptr, "Avg. Sleep : %0.1f\nSleep Data:\n", user->sleep_data->avg_sleep);

  node_t * month_ptr = user->sleep_data->months;
  node_t * date_ptr = user->sleep_data->date;
  node_t * year_ptr = user->sleep_data->years;
  node_t *sleep_ptr = user->sleep_data->sleep_hour;

  while (sleep_ptr) {
    fprintf(file_ptr, "%d / %d / %d : %d\n", date_ptr->val, month_ptr->val, year_ptr->val, sleep_ptr->val);
    date_ptr = date_ptr->next;
    year_ptr = year_ptr->next;
    month_ptr = month_ptr->next;
    sleep_ptr = sleep_ptr->next;
  }

  fprintf(file_ptr, "|------END OF DATA------|\n");
  fclose(file_ptr);
  file_ptr = NULL;
}

/*
 * Frees the memory assosciated with a user
 */

void free_user(user_t *user) {
  assert(user);

  free(user->name);
  user->name = NULL;
  free_sleep_data(user->sleep_data);
  free(user);

  user = NULL;
}


/*
 * Frees the sleep data
 */

void free_sleep_data(sleep_data_t *sleep_data) {
  assert(sleep_data);

  node_t * month_ptr = sleep_data->months;
  node_t * date_ptr = sleep_data->date;
  node_t * year_ptr = sleep_data->years;
  node_t *sleep_ptr = sleep_data->sleep_hour;

  while (sleep_ptr) {
    node_t *next_date_ptr = date_ptr->next;
    node_t *next_year_ptr = year_ptr->next;
    node_t *next_month_ptr = month_ptr->next;
    node_t *next_sleep_ptr = sleep_ptr->next;

    free(date_ptr);
    free(month_ptr);
    free(sleep_ptr);
    free(year_ptr);

    date_ptr = next_date_ptr;
    month_ptr = next_month_ptr;
    year_ptr = next_year_ptr;
    sleep_ptr = next_sleep_ptr;
  }

  free(sleep_data);
  sleep_data = NULL;
}