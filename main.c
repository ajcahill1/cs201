#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

int firstTime = 1;
FILE *currentFile;


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

struct node {
  struct movie* movie;
  struct node* left;
  struct node* right;
  int ht;
};

////////////////////////////////////////////////////////////////////////////////
struct movie* holder;

struct node* newNode (struct node* n, struct movie* m) {
  struct node* node = (struct node*) malloc(sizeof(struct node));

  holder = (struct movie*) malloc(sizeof(struct movie));

  holder->title = malloc(strlen((m->title)+1));
  holder->genre = malloc(strlen((m->genre)+1));
  holder->runtime = malloc(strlen((m->runtime)+1));
  holder->yearReleased = malloc(strlen((m->yearReleased)+1));
  strcpy(holder->title, m->title);
  strcpy(holder->genre, m->genre);
  strcpy(holder->runtime, m->runtime);
  strcpy(holder->yearReleased, m->yearReleased);

  node->movie = holder;
  node->left = NULL;
  node->right = NULL;
  node->ht = 1;

  return (node);
}

int height(struct node* T) {
  int lh,rh;
	if(T==NULL)
		return(0);

	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;

	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;

	if(lh>rh)
		return(lh);

	return(rh);
}
struct node* rotateright(struct node* x) {
	struct node* y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}

struct node* rotateleft(struct node* x) {
	struct node* y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);

	return(y);
}

struct node* RR(struct node* T) {
	T=rotateleft(T);
	return(T);
}

struct node* LL(struct node* T) {
	T=rotateright(T);
	return(T);
}

struct node* LR(struct node* T) {
	T->left=rotateleft(T->left);
	T=rotateright(T);

	return(T);
}

struct node* RL(struct node* T) {
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}

int BF(struct node* T) {
	int lh,rh;
	if(T==NULL)
		return(0);

	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;

	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;

	return(lh-rh);
}

void preorder(struct node* T) {
	if(T!=NULL) {
		printf("%s(Bf=%d)",T->movie->title,BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}

struct node* insert(struct node* T, struct movie *m) {
  if (T!=NULL){
    printf("now inserting %s\ncomparing to %s\n", m->title, T->movie->title);
    printf("%d\n", strcmp(m->title, T->movie->title));
  }

	if(T==NULL) {
    printf("creating new node with %s\n", m->title);
		return(newNode(T,m));
	}
	else if(strcmp(m->title, T->movie->title) > 0) {	// insert in right subtree
    printf("trying to insert into right tree\n");
    T->right=insert(T->right,m);
		if(BF(T)==-2){
			if(strcmp(m->title, T->right->movie->title) > 0)
				T=RR(T);
		  else{
				T=RL(T);
      }
    }
	}
	else if(strcmp(m->title, T->movie->title) < 0) {
		T->left=insert(T->left,m);
		if(BF(T)==2){
			if(strcmp(m->title, T->left->movie->title) < 0)
				T=LL(T);
			else{
				T=LR(T);
      }
    }
	}

	T->ht=height(T);
  printf("%s\n\n", T->movie->title);
	return(T);
}
////////////////////////////////////////////////////////////////////////////////

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
This function creates a BST of all IMDB data
*/
void load(){
  FILE* database = fopen("title.basics.tsv", "r");
  char buffer[BUFFER_SIZE];
  //char delimiter = "\t";
  char* token;
  struct node* root = NULL;
  struct movie* currentMovie;
  printf("Now loading...\n\n");
  int counter = 0;

  while( fgets(buffer, BUFFER_SIZE, database) != NULL ) {
    currentMovie = (struct movie*) malloc(sizeof(struct movie));

    //if (root != NULL)
      //printf("before declaration root = %s\n", root->movie.title);
    token = strtok(buffer, "\t");
    token = strtok(NULL, "\t");
    if (strcmp(token,"movie") != 0 && strcmp(token,"tvMovie") != 0) continue;

    token = strtok(NULL, "\t");
    currentMovie->title = token;
    //printf("%s\n", token);

    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    currentMovie->yearReleased = token;
    //printf("%s\n", token);

    token = strtok(NULL, "\t");
    token = strtok(NULL, "\t");
    currentMovie->runtime = token;
    //printf("%s\n", token);

    token = strtok(NULL, "\t");
    currentMovie->genre = token;
    //printf("%s\n\n", token);

    if (root != NULL)
      printf("before insert root = %s, current movie = %s\n", root->movie->title, currentMovie->title);
    root = insert(root, currentMovie);
    printf("after insert root = %s, current movie = %s\n\n", root->movie->title, currentMovie->title);
    counter++;
    if (counter == 10) break;
  }
  preorder(root);
  return;
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
      fclose(currentFile);
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
