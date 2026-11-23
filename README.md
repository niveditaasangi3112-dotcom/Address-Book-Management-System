# Address Book Management System in C

A menu-driven, console-based Address Book Management System developed using the C programming language. The application allows users to create, search, edit, delete, and display contacts. It uses file handling to save contact records in a CSV file and load them when the program starts.

## Features

- **Create contacts:** Add a contact with a name, 10-digit phone number, and email address.
- **Search contacts:** Find contacts by name, phone number, or email address.
- **Edit contacts:** Update a contact's name, phone number, or email address.
- **Delete contacts:** Delete contacts by name, phone number, or email address, with a confirmation prompt.
- **List contacts:** Display contacts alphabetically by name.
- **Input validation:** Check names, phone numbers, and email addresses before accepting them.
- **File handling:** Load saved contacts from `contacts.csv` at startup and save contacts to that file through the menu.
- **Capacity:** Store up to 100 contacts in memory.

## Technologies Used

- C programming language
- Structures and arrays
- Functions and header files
- String handling
- Standard C library (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`)
- File handling (`fopen`, `fscanf`, `fprintf`, `fclose`)
- CSV format for persistent contact storage

## Project Structure

```text
AddressBook-NewDesign/
├── main.c          # Program entry point and menu
├── contact.c       # Contact operations and input validation
├── contact.h       # Contact structures and function declarations
├── file.c          # Loading and saving contacts
├── file.h          # File-handling declarations
├── populate.c      # Optional sample contact data
├── populate.h      # Sample-data function declaration
├── contacts.csv    # Contact data file
├── .gitignore      # Files excluded from Git
└── README.md       # Project documentation
```

## Requirements

- GCC or another C compiler that supports C11
- A terminal or command prompt
- Git (for uploading the project to GitHub)

## Compile the Project

Open a terminal in the project directory and run:

```bash
gcc -std=c11 -Wall -Wextra main.c contact.c file.c populate.c -o addressbook
```

## Run the Project

On Linux or macOS:

```bash
./addressbook
```

On Windows using MinGW:

```bash
addressbook.exe
```

## Application Menu

When the program starts, it displays the following menu:

```text
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
```

Choose an option by entering its number and follow the prompts.

## Contact Data Format

The `contacts.csv` file stores a contact count on its first line, followed by one contact per line in this format:

```text
name,phone,email
```

The first line is a number indicating how many contact records follow. The program reads this file during initialization. The save option writes the current contacts to `contacts.csv` in the project directory.

## Implementation Overview

- `main.c` initializes the address book and handles the menu loop.
- `contact.c` implements contact creation, validation, searching, editing, deletion, and alphabetical listing.
- `contact.h` defines the `Contact` and `AddressBook` structures and declares the contact functions.
- `file.c` implements CSV file reading and writing.
- `file.h` declares the file-handling functions.
- `populate.c` contains optional sample contact records. The call to populate sample contacts is currently commented out in `initialize()`.

## Current Limitations / Notes

- The address book holds a maximum of 100 contacts.
- The save option writes to `contacts.csv`, but the current menu implementation does not exit after saving, despite the displayed message. Selecting Exit does not automatically save changes. Select Save contacts before exiting.
- The CSV format uses commas as separators, so names or other fields containing commas are not supported by the current file-reading and writing logic.
- Email validation is a basic check, not full standards-based email validation.

## Future Improvements

- Save automatically when the user exits.
- Improve input handling for invalid menu entries.
- Support more flexible email validation.
- Support CSV fields containing commas and quoted values.
- Add unit tests and stronger error handling.
- Allow sorting by additional fields.

## Author

Add your name here.

## License

No license has been specified for this project. Add a license file if you want to define how others may use, modify, and distribute the code.
