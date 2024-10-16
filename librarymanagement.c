#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TITLE_LENGTH 100
#define MAX_BOOKS 100
#define MAX_USERS 100
#define MAX_BORROWED_BOOKS 5
#define MAX_BORROW_DAYS 14
#define FINE_PER_DAY 1

typedef struct {
    char title[MAX_TITLE_LENGTH];
    int availableCopies;
    int totalCopies;
    bool reserved;
} Book;

typedef struct {
    char username[50];
    char password[50];
    int borrowedBooks[MAX_BORROWED_BOOKS];
    int numBorrowedBooks;
} User;

Book books[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0;
int userCount = 0;

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Cannot add more books. Library is full.\n");
        return;
    }

        printf("Enter the title of the book: ");
    scanf(" %[^\n]", books[bookCount].title);
    printf("Enter total copies of the book: ");
    scanf("%d", &books[bookCount].totalCopies);
    books[bookCount].availableCopies = books[bookCount].totalCopies;
    books[bookCount].reserved = false;
    bookCount++;
    printf("Book added successfully.\n");
}
void displayAllBooks() {
    printf("List of Books:\n");
    if (bookCount == 0) {
        printf("No books available.\n");
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        printf("%d. %s - Available Copies: %d/%d\n", i + 1, books[i].title,
               books[i].availableCopies, books[i].totalCopies);
    }
}
void borrowBook(int userId) {
    printf("Enter the title of the book you want to borrow: ");
    char title[MAX_TITLE_LENGTH];
    scanf(" %[^\n]", title);

    int bookIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            bookIndex = i;
            break;
        }
    }
        if (bookIndex != -1) {
        if (books[bookIndex].availableCopies > 0) {
            books[bookIndex].availableCopies--;
            users[userId].borrowedBooks[users[userId].numBorrowedBooks++] = bookIndex;
            printf("'%s' has been borrowed successfully.\n", title);
        } else {
            printf("Sorry, the book '%s' is currently unavailable.\n", title);
        }
    } else {
        printf("Book with title '%s' not found.\n", title);
    }
}
void returnBook(int userId) {
    printf("Enter the title of the book you want to return: ");
    char title[MAX_TITLE_LENGTH];
    scanf(" %[^\n]", title);

    int bookIndex = -1;
    for (int i = 0; i < users[userId].numBorrowedBooks; i++) {
        if (strcmp(books[users[userId].borrowedBooks[i]].title, title) == 0) {
            bookIndex = i;
            break;
        }
    }
        if (bookIndex != -1) {
        int returnedBookIndex = users[userId].borrowedBooks[bookIndex];
        books[returnedBookIndex].availableCopies++;
        for (int i = bookIndex; i < users[userId].numBorrowedBooks - 1; i++) {
            users[userId].borrowedBooks[i] = users[userId].borrowedBooks[i + 1];
        }
        users[userId].numBorrowedBooks--;
        printf("'%s' has been returned successfully.\n", title);
    } else {
        printf("You have not borrowed the book '%s'.\n", title);
    }
}
void deleteUser(int userId) {
    printf("Deleting user '%s'.\n", users[userId].username);
    // Additional logic to delete user if needed
}

int findUser(const char *username, const char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1; // User not found
}
int findBook(const char *title) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            return i;
        }
    }
    return -1; // Book not found
}
void addUser() {
    if (userCount >= MAX_USERS) {
        printf("Cannot add more users. User limit reached.\n");
        return;
    }
        printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    users[userCount].numBorrowedBooks = 0;
    userCount++;
    printf("User added successfully.\n");
}
int main() {
    int choice;
    int currentUser = -1;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Delete User\n");
        printf("6. Add User\n");
        printf("7. Login\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
                switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                if (currentUser != -1)
                    borrowBook(currentUser);
                else
                    printf("Please login first.\n");
                break;
            case 4:
                if (currentUser != -1)
                    returnBook(currentUser);
                else
                    printf("Please login first.\n");
                break;
            case 5:
                if (currentUser != -1)
                    deleteUser(currentUser);
                else
                    printf("Please login first.\n");
                break;
            case 6:
                addUser();
                break;
            case 7:
                printf("Enter username: ");
                char username[50], password[50];
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                currentUser = findUser(username, password);
                if (currentUser != -1)
                    printf("Login successful.\n");
                else
                    printf("Login failed. Invalid username or password.\n");
                break;
            case 8:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
