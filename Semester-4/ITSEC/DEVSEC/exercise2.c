#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_LEN 50
#define MAX_USERS 5
#define true 1

// Dummy-Database for users (in case of a real)
// This is not an failure it is just to make the exercise a little bit easier
// for you
typedef struct {
  char username[BUF_LEN];
  char password[BUF_LEN];
  char sessionID[BUF_LEN];
  uint isAdmin;
} User;

// Function to register users
void registerUser(User users[MAX_USERS], int *userCount) {
  char username[BUF_LEN];
  char password[BUF_LEN];

  // BUG: CWE-306: Missing Authentication for Critical Function
  // If user already has a session return

  printf("Enter a username: ");
  // BUG: CWE-120 Bufferoverflow possible
  // scanf("%s", username);

  // scanf("%49s", username); or better
  fgets(username, sizeof(username), stdin);

  printf("Enter a password: ");
  // BUG: CWE-120 Bufferoverflow possible
  // scanf("%s", password);

  // scanf("%49s", password); or better
  fgets(password, sizeof(password), stdin);

  // TODO: Add in check for safe Password CWE-521

  // BUG: CWE-120 Bufferoverflow possible
  // strcpy(users[userCount].username, username);
  strncpy(users[*userCount].username, username, sizeof(username));
  // BUG: CWE-120 Bufferoverflow possible
  // strcpy(users[userCount].password, password);
  strncpy(users[*userCount].password, password, sizeof(password));
  users[*userCount].isAdmin = 0;
  userCount++;

  printf("User %s registered successfully!\n", username);
}

// Function for login
void loginUser(User users[MAX_USERS], const int userCount) {
  char username[BUF_LEN];
  char password[BUF_LEN];

  // BUG: CWE-306: Missing Authentication for Critical Function
  // If user already has a session return

  while (1) {
    printf("Enter your username: ");

    // BUG: CWE-120 Bufferoverflow possible
    // scanf("%s", username);

    // scanf("%49s", username); or better
    fgets(username, sizeof(username), stdin);

    printf("Enter your password: ");

    // BUG: CWE-120 Bufferoverflow possible
    // scanf("%s", password);

    // scanf("%49s", password); or better
    fgets(password, sizeof(password), stdin);

    // BUG: CWE-307: Improper Restriction of Excessive Authentication Attempts
    for (int i = 0; i < userCount; i++) {
      if (strcmp(users[i].username, username) == 0 &&
          strcmp(users[i].password, password) == 0) {
        printf("Login successful! Welcome, %s\n", username);

        // BUG: CWE-613: Insufficient Session Expiration
        // BUG: CWE-384: Session Fixation
        strcpy(users[i].sessionID, "123456");
        return;
      }
    }

    printf("Invalid username or password. Try again.\n");
  }
}

// Function for password reset
void resetPassword(User users[MAX_USERS], const int userCount) {
  char username[BUF_LEN];
  char securityAnswer[BUF_LEN];
  char newPassword[BUF_LEN];

  // BUG: CWE-306: Missing Authentication for Critical Function

  printf("Enter your username: ");
  scanf("%s", username);

  // BUG: CWE-640: Weak Password Recovery Mechanism for Forgotten Password
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
  // BUG: CWE-306: Missing Authentication for Critical Function

  char filename[BUF_LEN * 2];
  printf("Enter the filename to upload: ");
  // BUG: CWE-434: Unrestricted Upload of File with Dangerous Type
  scanf("%s", filename);

  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    printf("Error creating temporary file.\n");
    // BUG: CWE-460: Improper Cleanup on Thrown Exception
    return;
  }

  fprintf(file, "Example data in the uploaded file.\n");
  fclose(file);

  printf("File %s uploaded successfully!\n", filename);
}

// Main Function
int main() {
  int choice = 0;
  User users[MAX_USERS];
  memset(users, 0, sizeof(users));
  int userCount = 0;

  enum { REGISTER = 1, LOGIN, RESETPASSWD, UPLOADFILE, EXIT };

  while (true) {
    printf("\n1. Register\n2. Login\n3. Reset Password\n4. Upload File\n5. "
           "Exit\n");
    printf("Choose an option: ");
    // BUG: UNSAFE
    scanf("%d", &choice);

    switch (choice) {
    case REGISTER:
      registerUser(users, &userCount);
      break;
    case LOGIN:
      loginUser(users, userCount);
      break;
    case RESETPASSWD:
      resetPassword(users, userCount);
      break;
    case UPLOADFILE:
      uploadFile();
      break;
    case EXIT:
      exit(EXIT_SUCCESS);
    default:
      printf("Invalid choice.\n");
    }
  }

  return EXIT_SUCCESS;
}
