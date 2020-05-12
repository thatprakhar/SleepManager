#include "project.h"

#include <stdio.h>

user_t *g_user;

void handle_user_create() {
  printf("\n\nUSER CREATION SELECTED\n");
  printf("Enter user name: ");
  char name[MAX_NAME_LEN] = "";
  int age;
  scanf("%s[^\n]\n", name);
  printf("Enter age : ");
  scanf("%d", &age);
  getchar();
  g_user = create_user(name, age);
  printf("User created successfully\n");
  printf("\n\n");
  show_options();
}

void handle_add_data() {
  int date = -1;
  int month = -1;
  int year = -1;
  int sleep_hour = -1;
  printf("ENTER DATA SELECTED\n");

  printf("Enter data : ");
  scanf("%d", &date);
  getchar();
  printf("\n");

  printf("Enter month : ");
  scanf("%d", &month);
  getchar();
  printf("\n");

  printf("Enter year : ");
  scanf("%d", &year);
  getchar();
  printf("\n");

  printf("Enter sleep hour (number) : ");
  scanf("%d", &sleep_hour);
  getchar();
  printf("\n");

  int return_val = add_sleep_data(g_user, date, month, year, sleep_hour);
  if (return_val == INVALID_DATE) {
    printf("Please Enter correct data format\n");
    handle_add_data();
    return;
  }
  if (return_val == INVALID_SLEEP) {
    printf("Please Enter correctly formatted sleep hour\n");
    handle_add_data();
    return;
  }
  if (return_val == DATA_EXISTS) {
    printf("Data Already exists in the file\n");
  } else {
    write_user_data(g_user);
    printf("Data Successfully Added and Written to %s.txt\n", g_user->name);
  }
  printf("\n\n");
  show_options();
}

void show_options() {
  int option = -1;
  while (option < 1 || option > 3) {
    printf("1. Create User\n");
    printf("2. Add Sleep Data\n");
    printf("3. Exit\n");
    printf("Enter choice : ");
    scanf("%d", &option);
    getchar();
    if (option < 1 || option > 3) {
      printf("Please enter a valid option.\n");
    }
  }

  switch(option) {
    case 1:
      handle_user_create();
    break;
    case 2:
     handle_add_data();
    break;
    case 3:
      return;
  }
}



int main() {
  printf("Welcome to Sleep Data System\n");
  show_options();
  printf("Thank you for using sleep data system\n");
  return 0;
}