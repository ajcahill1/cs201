#include <stdio.h>
#include <string.h>

FILE *currentFile;
int firstTime = 1;

/*
This function creates a BST of all IMDB data
*/
void load(){
  //write the shit to be loaded in
}

/*
Checks if a file exists
*/
int exists(const char *fname) {
  FILE *file;
  if ((file = fopen(fname, "r"))) {
    fclose(file);
    return 1;
  }
  return 0;
}

/*
Creates or opens a file for the given user
*/
void openFile(const char *fname) {
  currentFile = fopen(fname, "w");
  return;
}

/*
This is the introductory function which asks for the username, and then
either creates a new log, or opens an existing one
*/
void intro() {
  char username[100];
  if (firstTime == 1) {
    printf("Welcome to the IMDB Database!\n\n");
    firstTime = 0;
  }
  printf("Enter username (case sensitive): ");
  scanf(" %s", username);
  printf("\n");

  char fileName[100];
  strcat(strcpy(fileName, username), ".log");
  if (exists(fileName) == 1) {
    printf("Welcome back, %s, your movie log is being opened...\n\n", username);
    openFile(fileName);
  }
  else {
    printf("Welcome, %s, we're creating a new movie log for you...\n\n", username);
    openFile(fileName);
  }
  return;
}

/*
This menu gives the user CRUD options
*/
void menu() {
  int choice = 0;
  while(1){
    printf("What would you like to do?\n\n");
    printf("1. Create a new movie catalog\n");
    printf("2. View an existing movie catalog\n");
    printf("3. Edit an existing movie catalog\n");
    printf("4. Delete an existing movie catalog\n");
    printf("5. Change user\n");
    printf("6. Quit\n\n");
    printf("Please insert a number (1-6): ");
    scanf("%d", &choice);
    printf("\n");
    
    if (choice == 1){
      //createCatalog();
    }
    else if (choice == 2){
      //retrieveCatalog();
    }
    else if (choice == 3){
      //editCatalog();
    }
    else if (choice == 4){
      //deleteCatalog();
    }
    else if (choice == 5){
      intro();
      menu();
      return;
    }
    else if (choice == 6){
      printf("Thank you! Goodbye for now.\n\n");
      return;
    }
    else printf("Not a valid input. Please insert a number 1-6.\n\n");
  }
}


int main(int argc, char const *argv[]) {
  load();
  intro();
  menu();
  return 0;
}
