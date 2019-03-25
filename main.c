#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

/*
Creates an object for the movie files
*/
struct movie {
  char* title;
  char* genre;
  char* runtime;
  char* yearReleased;
  char* dateAcquired;//TODO maybe make month/day/year?
  int mediaType;
};


/*
char getMediaType(int i){
  if (int i == 1) return ""
}
*/

int firstTime = 1;
FILE *currentFile;

/*
This function creates a BST of all IMDB data
*/
void load(){
  FILE* database = fopen("title.basics.tsv", "r");
  char buffer[BUFFER_SIZE];
  //char delimiter = "\t";
  char* token;

  printf("Now loading...\n\n");

  while( fgets(buffer, BUFFER_SIZE, database) != NULL ){
    struct movie currentMovie;
    token = strtok(buffer, "\t");
    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    currentMovie.title = token;
    //printf("%s\n", currentMovie.title);
    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    currentMovie.yearReleased = token;
    //printf("%s\n", token);
    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    currentMovie.runtime = token;
    //printf("%s\n", token);
    token = strtok(NULL, "\t");
    currentMovie.genre = token;
    //printf("%s\n", token);
      /*
      while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, "\t");
        }
        */
  }
  return;
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
