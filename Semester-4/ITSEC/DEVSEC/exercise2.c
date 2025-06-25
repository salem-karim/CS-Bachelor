#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Dummy-Database for users (in case of a real)
// This is not an failure it is just to make the exercise a little bit easier
// for you
struct User {
  char username[50];
  char password[50];
  char sessionID[50];
  int isAdmin;
};

#define MAX_USERS 5
struct User users[MAX_USERS];
int userCount = 0;

// Function to register users
void registerUser() {
  char username[50];
  char password[50];

  printf("Enter a username: ");
  scanf("%s", username);

  printf("Enter a password: ");
  scanf("%s", password);

  strcpy(users[userCount].username, username);
  strcpy(users[userCount].password, password);
  users[userCount].isAdmin = 0;
  userCount++;

  printf("User %s registered successfully!\n", username);
}

// Funktion for login
void loginUser() {
  char username[50];
  char password[50];

  while (true) {
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
      if (strcmp(users[i].username, username) == 0 &&
          strcmp(users[i].password, password) == 0) {
        printf("Login successful! Welcome, %s\n", username);

        strcpy(users[i].sessionID, "123456");
        return;
      }
    }

    printf("Invalid username or password. Try again.\n");
  }
}

// Function for password reset
void resetPassword() {
  char username[50];
  char securityAnswer[50];
  char newPassword[50];

  printf("Enter your username: ");
  scanf("%s", username);

  printf("What is your favorite color? ");
  scanf("%s", securityAnswer);

  if (strcmp(securityAnswer, "blue") == 0) {
    printf("Enter your new password: ");
    scanf("%s", newPassword);

    for (int i = 0; i < userCount; i++) {
      if (strcmp(users[i].username, username) == 0) {
        strcpy(users[i].password, newPassword);
        printf("Password reset successful for user %s.\n", username);
        return;
      }
    }
  } else {
    printf("Security answer incorrect.\n");
  }
}

// Extremely simple File-Upload to make it easier for you
void uploadFile() {
  char filename[100];
  printf("Enter the filename to upload: ");
  scanf("%s", filename);

  file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error creating temporary file.\n");
    return;
  }

  fprintf(file, "Example data in the uploaded file.\n");
  fclose(file);

  printf("File %s uploaded successfully!\n", filename);
}

// Main Function
int main() {
  int choice;

  while (1) {
    printf("\n1. Register\n2. Login\n3. Reset Password\n4. Upload File\n5. "
           "Exit\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      registerUser();
      break;
    case 2:
      loginUser();
      break;
    case 3:
      resetPassword();
      break;
    case 4:
      uploadFile();
      break;
    case 5:
      exit(0);
    default:
      printf("Invalid choice.\n");
    }
  }

  return 0;
}
