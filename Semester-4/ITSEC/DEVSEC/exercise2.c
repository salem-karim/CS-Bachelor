#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  // BUG: CWE-306: Missing Authentication for Critical Function

  printf("Enter a username: ");
  // BUG: CWE-120 Bufferoverflow possible
  scanf("%s", username);

  printf("Enter a password: ");
  // BUG: CWE-120 Bufferoverflow possible
  scanf("%s", password);
  // BUG: CWE-521: Weak Password Requirements

  // BUG: CWE-120 Bufferoverflow possible
  strcpy(users[userCount].username, username);
  // BUG: CWE-120 Bufferoverflow possible
  strcpy(users[userCount].password, password);
  users[userCount].isAdmin = 0;
  userCount++;

  printf("User %s registered successfully!\n", username);
}

// Funktion for login
void loginUser() {
  char username[50];
  char password[50];

  // BUG: CWE-306: Missing Authentication for Critical Function

  // BUG: CWE-307: Improper Restriction of Excessive Authentication Attempts
  while (1) {
    printf("Enter your username: ");
    // BUG: CWE-120 Bufferoverflow possible
    scanf("%s", username);
    printf("Enter your password: ");
    // BUG: CWE-120 Bufferoverflow possible
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
      if (strcmp(users[i].username, username) == 0 &&
          strcmp(users[i].password, password) == 0) {
        // BUG: CWE-120 Bufferoverflow possible ?
        printf("Login successful! Welcome, %s\n", username);

        // BUG: CWE-613: Insufficient Session Expiration ?
        // BUG: CWE-384: Session Fixation
        // bigger then 50
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
  // BUG: CWE-120 Bufferoverflow possible
  scanf("%s", username);

  // BUG: CWE-640: Weak Password Recovery Mechanism for Forgotten Password
  printf("What is your favorite color? ");
  // BUG: CWE-120 Bufferoverflow possible
  scanf("%s", securityAnswer);

  if (strcmp(securityAnswer, "blue") == 0) {
    printf("Enter your new password: ");
    // BUG: CWE-120 Bufferoverflow possible
    scanf("%s", newPassword);
    // BUG: CWE-521: Weak Password Requirements

    for (int i = 0; i < userCount; i++) {
      if (strcmp(users[i].username, username) == 0) {
        // BUG: CWE-120 Bufferoverflow possible
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
  // BUG: CWE-306: Missing Authentication for Critical Function

  char filename[100];
  printf("Enter the filename to upload: ");
  // BUG: CWE-120 Bufferoverflow possible
  scanf("%s", filename);
  // BUG: CWE-434: Unrestricted Upload of File with Dangerous Type

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error creating temporary file.\n");
    // BUG: CWE-460: Improper Cleanup on Thrown Exception
    return;
  }

  fprintf(file, "Example data in the uploaded file.\n");
  fclose(file);

  // BUG: CWE-120 Bufferoverflow possible
  printf("File %s uploaded successfully!\n", filename);
}

// Main Function
int main() {
  int choice;

  while (1) {
    printf("\n1. Register\n2. Login\n3. Reset Password\n4. Upload File\n5. "
           "Exit\n");
    printf("Choose an option: ");
    // BUG: CWE-120 Bufferoverflow possible
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
