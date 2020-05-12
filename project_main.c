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