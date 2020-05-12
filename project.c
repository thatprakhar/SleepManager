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
  new_user->avg_sleep = 0.0;
  new_user->data_size = 0;

  return new_user;
}

/*
 * Method to add sleep data
 */

int add_sleep_data(user_t *user, int date, int month, int year, int sleep_hour) {
  assert(user);
  if (date < 1 || date > 31) {
    return INVALID_DATE;
  }
  if (month < 0 || month > 12) {
    return INVALID_DATE;
  }
  if (year < 0) {
    return INVALID_DATE;
  }
  if (sleep_hour < 0) {
    return INVALID_SLEEP;
  }
  int total_sleep = 0;

  sleep_data_t *date_ptr = user->sleep_data;

  if (!date_ptr) {
    user->sleep_data = malloc(sizeof(sleep_data_t));
    assert(user->sleep_data);
    user->sleep_data->date = date;
    user->sleep_data->month = month;
    user->sleep_data->year = year;
    user->sleep_data->sleep_hour = sleep_hour;
    user->sleep_data->next = NULL;

    user->data_size = 1;
    user->avg_sleep = sleep_hour;
    return DATA_ADDED;
  }

  while (date_ptr->next != NULL) {
    total_sleep += date_ptr->sleep_hour;
    date_ptr = date_ptr->next;
  }
  total_sleep += date_ptr->sleep_hour;
  total_sleep += sleep_hour;
  
  date_ptr->next = malloc(sizeof(sleep_data_t));
  date_ptr->next->month = month;
  date_ptr->next->date = date;
  date_ptr->next->year = year;
  date_ptr->next->sleep_hour = sleep_hour;
  date_ptr->next->next = NULL;

  user->data_size++;
  user->avg_sleep = (double)total_sleep / user->data_size;

  return DATA_ADDED;
}

/*
 * Writes the user sleep data in
 * a text file with their name
 */

void write_user_data(user_t *user) {
  assert(user);

  FILE *file_ptr = NULL;
  file_ptr = fopen(user->name, "w");
  printf("Writing data....\n");
  fprintf(file_ptr, "|------Sleep Data------|\n");
  fprintf(file_ptr, "Name: %s\n", user->name);
  fprintf(file_ptr, "Age: %d\n", user->age);
  fprintf(file_ptr, "Record Size: %d\n", user->data_size);
  fprintf(file_ptr, "Avg. Sleep : %0.1f\n\nSleep Data:\n", user->avg_sleep);

  sleep_data_t * sleep_ptr = user->sleep_data;

  while (sleep_ptr) {
    fprintf(file_ptr, "%d/%d/%d : %d\n", sleep_ptr->date, sleep_ptr->month, sleep_ptr->year, sleep_ptr->sleep_hour);
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
  sleep_data_t *sleep_ptr = sleep_data;

  while (sleep_ptr) {
    sleep_data_t  *next_sleep_ptr = sleep_ptr->next;
    free(sleep_ptr);
    sleep_ptr = next_sleep_ptr;
  }

  sleep_data = NULL;
}