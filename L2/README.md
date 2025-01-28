# Library Management System Design Document

## Overview

This document outlines the design for a **Library Management System** implemented in C++. The system allows for managing books, library members, and their interactions (borrowing and returning books). The system consists of a set of operations for adding books, registering members, borrowing and returning books, and printing relevant details about books and members.

---

## Table of Contents

1. [System Components](#1-system-components)
    - [Book Class](#11-book-class)
    - [Member Class](#12-member-class)
    - [Library Class](#13-library-class)
2. [Operations](#2-operations)
3. [Input/Output](#3-inputoutput)
4. [Error Handling](#4-error-handling)

---

## 1. System Components

### 1.1 Book Class

The `Book` class represents a book in the library. It maintains details such as title, author, ISBN, and the count of available and total copies of the book.

**Attributes:**
- `title` (string): The title of the book.
- `author` (string): The author of the book.
- `isbn` (string): The ISBN number of the book.
- `copiesAvailable` (int): The number of available copies of the book.
- `totalCopies` (int): The total number of copies of the book in the library.

**Methods:**
- **Constructor**: Initializes a book with title, author, ISBN, available copies, and total copies.
- **updateCopies()**: Updates the available copies of the book. If copies are added or removed, the total copies are also updated accordingly.
- **borrowBook()**: Decreases the available copies by 1 if available and returns `true`; otherwise, it prints an error.
- **returnBook()**: Increases the available copies by 1, ensuring that it doesn't exceed the total copies.
- **getisbn()**: Returns the ISBN of the book.
- **cA()**: Returns the current count of available copies.
- **tC()**: Returns the total number of copies.
- **printDetails()**: Prints the title and author of the book.

---

### 1.2 Member Class

The `Member` class represents a library member who can borrow and return books.

**Attributes:**
- `name` (string): The name of the member.
- `memberID` (string): The unique ID of the member.
- `borrowLimit` (int, default=3): The maximum number of books a member can borrow.
- `borrowedBooks` (map<string, int>): A map tracking the number of each book borrowed by the member.
- `borrowedCurr` (int): The current count of borrowed books by the member.

**Methods:**
- **Constructor**: Initializes the member's name, memberID, and borrow limit.
- **borrowBook()**: Checks if the member has exceeded their borrow limit and borrows the book if available.
- **returnBook()**: Returns a borrowed book, ensuring it was borrowed previously.
- **getmemberID()**: Returns the member's ID.
- **printDetails()**: Prints details of borrowed books and the number of copies borrowed.

---

### 1.3 Library Class

The `Library` class manages the collection of books and members and allows operations like borrowing and returning books.

**Attributes:**
- `books` (vector<Book*>): A collection of books in the library.
- `members` (vector<Member*>): A collection of library members.

**Methods:**
- **addBook()**: Adds a new book to the library after checking for duplicates (based on ISBN).
- **registerMember()**: Registers a new library member, ensuring no duplicate member IDs.
- **borrowBook()**: Allows a member to borrow a book, updating both the member's and book's status.
- **returnBook()**: Allows a member to return a book, updating both the member's and book's status.
- **getBook()**: Retrieves a book by its ISBN.
- **getMem()**: Retrieves a member by their ID.
- **printLibraryDetails()**: Prints details of all books and members in the library.

---

## 2. Operations

The system supports the following operations:

1. **Book**:
   - Add a new book (either existing or new).
   - Operations for adding an existing book or creating a new one.

2. **UpdateCopiesCount**:
   - Update the available copies of a book.

3. **Member**:
   - Register a new member, either with or without a borrowing limit.

4. **Borrow**:
   - A member borrows a book, subject to availability and borrowing limits.

5. **Return**:
   - A member returns a borrowed book.

6. **PrintBook**:
   - Print the details of a specific book.

7. **PrintMember**:
   - Print the details of a specific member.

8. **PrintLibrary**:
   - Print the details of all books and members in the library.

9. **Done**:
   - Exit the system.

---

## 3. Input/Output

### Input Format:
The system accepts commands from the user in the following format:

- **Book**:
  - `ExisitingBook oldisbn newisbn`: Create a new book by copying an existing book with a new ISBN.
  - `None`: Create a new book with default attributes.
  - `<BookTitle> <Author> <ISBN> <copiesAvailable> <totalCopies>`: Add a new book with given attributes.

- **UpdateCopiesCount**:
  - `<ISBN> <newCount>`: Update the available copies for a book by its ISBN.

- **Member**:
  - `NoBorrowLimit <memberID> <name>`: Register a member with no borrowing limit.
  - `<memberID> <name> <borrowLimit>`: Register a member with a specified borrowing limit.

- **Borrow**:
  - `<memberID> <ISBN>`: Borrow a book by ISBN.

- **Return**:
  - `<memberID> <ISBN>`: Return a borrowed book.

- **PrintBook**:
  - `<ISBN>`: Print details of a book by ISBN.

- **PrintMember**:
  - `<memberID>`: Print details of a member by memberID.

- **PrintLibrary**:
  - Print all books and members in the library.

### Output Format:
The system outputs:
- **Success Messages**: Confirmation of successfully completed operations.
- **Error Messages**: Indicating invalid operations (e.g., borrowing more books than allowed, trying to borrow an unavailable book).
- **Printed Details**: Details of books, members, or the entire library as requested.

---

## 4. Error Handling

The system handles the following errors:

- **Duplicate Book**: If a book with the same ISBN already exists, the system prevents adding the duplicate.
- **Borrow Limit Exceeded**: If a member attempts to borrow more books than allowed, an error is shown.
- **Book Not Available**: If a member attempts to borrow a book that is unavailable, an error is displayed.
- **Book Not Borrowed**: If a member attempts to return a book they haven't borrowed, an error is shown.
- **Negative Copies Count**: If the available copies fall below zero during an update, an error is displayed.

---
