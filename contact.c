#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int is_valid_name(char temp_name [])
{
    for(int i=0;temp_name[i]!='\0';i++){
        if (!isalpha(temp_name[i]) && temp_name[i] != ' ')
            return 0;  // invalid Name
    }
    return 1; // valid Name
}

int is_valid_phno(AddressBook *addressBook, char temp_phno[]) 
{
    int len = strlen(temp_phno);

    // Number should be 10 digits
    if (len != 10) 
        return 0;
    
    // i want number in digits not alpha,spl char
    for (int i = 0; i < len; i++) 
    {
        if (!isdigit(temp_phno[i]))
            return 0;
    }
 // Checking number unique or not double
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, temp_phno) == 0)
            return 0;
    }

    return 1; //valid number
}
// validate email @ ,position,unique
int is_valid_email(AddressBook *addressBook, char temp_email[]) {
    int len = strlen(temp_email);

    char *at = strchr(temp_email, '@');
    // must contain @
    if (at == NULL) 
        return 0;
    // must be present in the middle
    if (at == temp_email || at == temp_email + len - 1) 
        return 0;  

    char *dot = strchr(at, '.');
    // must contain .
    if (dot == NULL || dot == at + 1) 
        return 0; 
    // must not have . at end
    if (dot == temp_email + len - 1) 
        return 0; 
    
    for (int i = 0; i < len; i++) 
    {
        // space will not consider to valid email
        if (isspace(temp_email[i])) 
            return 0;
 if (!(isdigit(temp_email[i]) || islower(temp_email[i]) || temp_email[i] == '.' || temp_email[i] == '@'))
            return 0;
    }
    // Check uniqueness or single email
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].email, temp_email) == 0)
            return 0;
    }

    return 1; //valid
}
//List by contact
int compareByName(const void *a, const void *b) {
    Contact *c1 = (Contact *)a;
    Contact *c2 = (Contact *)b;
    return strcmp(c1->name, c2->name); // A â†’ Z
}
void listContacts(AddressBook *addressBook) 
{
    int sortCriteria = 1;
    if (addressBook->contactCount == 0) {
        printf(" No contacts to display!\n");
        return;
    }

    // If sorting by name, create a copy and sort it
    if (sortCriteria == 1) {
        AddressBook temp = *addressBook; // copy all contacts
        qsort(temp.contacts, temp.contactCount, sizeof(Contact), compareByName);

        printf(" Contacts (Sorted by Name A-Z):\n");
        for (int i = 0; i < temp.contactCount; i++) {
            printf("%d) %s | %s | %s\n", i + 1,
                   temp.contacts[i].name,
                   temp.contacts[i].phone,
                   temp.contacts[i].email);
        }
    }
    // If recently added (default order)
    else if (sortCriteria == 2) {
        printf(" Contacts (Recently Added):\n");
        for (int i = 0; i < addressBook->contactCount; i++) {
            printf("%d) %s | %s | %s\n", i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
        }
    }
    else
        printf(" Invalid choice.\n");
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


// *Create Contact*

void createContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount >= 100) 
    {
        printf("Address book is full! Cannot add more contacts.\n");
        return;
    }
    int ind=addressBook->contactCount;
    char temp[50];
    int valid;

    printf("\n==========================\n");
    printf("        Add a temp Contact\n");
    printf("=====================================\n");

    //  By the Name
    do {
        printf(" Enter Name: ");
        scanf(" %[^\n]", temp);
        valid = is_valid_name(temp);
        if (!valid) 
            printf(" Invalid name! Use only letters & spaces.\n");
        else
            strcpy(addressBook->contacts[ind].name,temp);
    } while (!valid);

    // Phone
    do{
        printf(" Enter Phone (10 digits): ");
        scanf(" %[^\n]", temp);
        valid = is_valid_phno(addressBook,temp);
        if (!valid) 
            printf(" Invalid phone number! Try again.\n");
            else
            strcpy(addressBook->contacts[ind].phone,temp);
    } 
    while (!valid);

    // Email
    do 
    {
        printf(" Enter Email: ");
        scanf(" %[^\n]", temp);
        valid = is_valid_email(addressBook,temp);
        if (!valid) 
            printf(" Invalid email! Try again.\n");
            else
            strcpy(addressBook->contacts[ind].email,temp);
    } while (!valid);

    //addressBook->contacts[addressBook->contactCount++] = Contact;
    printf("Name: '%s' saved successfully!\n",  addressBook->contacts[ind].name);
    printf("Phone: '%s' saved successfully!\n", addressBook->contacts[ind].phone);
    printf("Email: '%s' saved successfully!\n", addressBook->contacts[ind].email);
    printf(" Contact saved successfully!\n");
    addressBook->contactCount++;
}

// Search by Name


void searchByName(AddressBook *addressBook, char *search) 
{
    if (!is_valid_name(search)) 
    {
        printf("Invalid name format! Please enter the valid name.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0) 
        { 
            printf("\n Contact Found!\n");
            printf("--------------------------\n");
            printf("Name : %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf(" Email: %s\n", addressBook->contacts[i].email);
            printf("-----------\n");
            found = 1;
        }
    }
    if (!found) 
        printf("No contact found with that name.\n");
}
// Search by Phone number
void searchByPhone(AddressBook *addressBook, char *search) 
{
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, search) == 0) 
        {
            printf("Contact Found!\n");
            printf("----------------\n");
            printf("Name : %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            printf("---------------\n");
            found = 1;
        }
    }
    if (!found) 
        printf("No contact found with that phone number.\n");
}
// Search by Email
void searchByEmail(AddressBook *addressBook, char *search) {
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, search) == 0) {
            printf("Contact Found!\n");
            printf("--------------------\n");
            printf(" Name : %s\n", addressBook->contacts[i].name);
            printf(" Phone: %s\n", addressBook->contacts[i].phone);
            printf(" Email: %s\n", addressBook->contacts[i].email);
            printf("-----------------\n");
            found = 1;
        }
    }
    if (!found) 
        printf("\n No contact found with that email.\n");
}

void searchContact(AddressBook *addressBook) 
{
    int q;
    printf("for searching contact by name enter 1\n");
    printf("for searching contact by phone number 2\n");
    printf("for searching contact by email_id 3\n");
    printf("\nenter the choice:");
    char ch[50];
    scanf("%d",&q);
    switch(q)
    {
        case 1:
        scanf(" %[^\n]",ch);
        searchByName(addressBook,ch);
        break;

        case 2:
        scanf(" %[^\n]",ch);
        searchByPhone(addressBook,ch);
        break;

        case 3:
        scanf(" %[^\n]",ch);
        searchByEmail(addressBook,ch);
        break;

        default:
        printf("enter the valid choice !\n\n");
    }

}
     //By Edit 
void editContact(AddressBook *addressBook)
{
    
    int searchChoice;
    char temp[70];
    int index;

    printf("\n============\n");
    printf("   Edit Contact\n");
    printf("========================\n");
    printf(" 1)  Search by Name\n");
    printf(" 2)  Search by Phone\n");
    printf(" 3)  Search by Email\n");
    printf("===============\n");
    printf("Enter choice: ");
    scanf("%d", &searchChoice);

    if (searchChoice == 1) {
        printf("Enter name to search: ");
        scanf(" %[^\n]", temp);
        if (!is_valid_name(temp)) {
            printf(" Invalid name format!\n");
            return;
        }
        int matchedIndices[50];
        int matchedCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].name, temp) == 0) {
                matchedIndices[matchedCount++] = i;
                printf("[%d] %s | %s | %s\n", matchedCount,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
            }
        }
 if (matchedCount == 0) {
            printf(" No contacts found with that name.\n");
            return;
        }
        int choice;
        printf("Enter index of contact to edit (1-%d): ", matchedCount);
        scanf("%d", &choice);
        if (choice < 1 || choice > matchedCount) {
            printf(" Invalid choice!\n");
            return;
        }
        editMenu(addressBook, matchedIndices[choice - 1]);
    }
    else if (searchChoice == 2) {
        printf("Enter phone number: ");
        scanf(" %[^\n]", temp);
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone, temp) == 0) {
                editMenu(addressBook, i);
                return;
            }
        }
        printf(" No contact found with that phone number.\n");
    }
    else if (searchChoice == 3) {
        printf("Enter email: ");
        scanf(" %[^\n]", temp);
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].email, temp) == 0) {
                editMenu(addressBook, i);
                return;
            }
        }
        printf(" No contact found with that email.\n");
 }
    else {
        printf(" Invalid search choice!\n");
    }
}
void editMenu(AddressBook*addressBook,int index){
    int choice;
    char temp[70];
    printf("\n=============\n");
    printf("  Edit Menu\n");
    printf("==================\n");
    printf(" 1) Edit Name\n");
    printf(" 2) Edit Phone Number\n");
    printf(" 3) Edit Email\n");
    printf("====================\n");
    printf("Enter choice: ");
    
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            while (1) {
                printf("Enter temp name: ");
                scanf(" %[^\n]", temp);
                
                if (is_valid_name(temp)) {
                    strcpy(addressBook->contacts[index].name, temp);
                    printf(" Name updated successfully!\n");
                    break;
                } 
                else 
                    printf(" Invalid name format! Try again.\n");
            }
            break;
            case 2:
            while (1) {
                printf("Enter temp phone number: ");
                scanf(" %[^\n]", temp);
                if (is_valid_phno(addressBook, temp)) {
                    strcpy(addressBook->contacts[index].phone, temp);
                    printf(" Phone updated successfully!\n");
                    break;
                } 
                else 
                    printf(" Invalid phone number! Try again.\n");
            }
            break;

        case 3:
            while (1) {
                printf("Enter temp email: ");
                scanf(" %[^\n]", temp);
                if (is_valid_email(addressBook, temp)) {
                    strcpy(addressBook->contacts[index].email, temp);
                    printf(" Email updated successfully!\n");
                    break;
                } 
                else 
                    printf(" Invalid email format! Try again.\n");
            }
            break;

        default:
            printf(" Invalid choice!\n");
    }
}

// Compare by Name

/*int compareByName(const void *a, const void *b) {
    Contact *c1 = (Contact *)a;
    Contact *c2 = (Contact *)b;
    return strcmp(c1->name, c2->name); // A â†’ Z
}*/
void deleteContact(AddressBook *addressBook)
{
    int choice;
    char temporary[70];
    int deleteIndexes[10];
    int deleteCount = 0;

    printf("\n========\n");
    printf("  Delete Contact\n");
    printf("=================\n");
    printf(" 1)  Delete by Name\n");
    printf(" 2)  Delete by Phone Number\n");
    printf(" 3)  Delete by Email ID\n");
    printf("======================\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Enter search temporary: ");
    scanf(" %[^\n]", temporary);

    if (choice == 1) {
        int matches[100], matchCount = 0;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].name, temporary) == 0) {
                matches[matchCount++] = i;
            }
        }
        if (matchCount == 0) {
            printf(" No contacts found with that name.\n");
            return;
        }
        printf("\nFound %d contact(s):\n", matchCount);
        for (int i = 0; i < matchCount; i++) {
            int idx = matches[i];
            printf("[%d] %s | %s | %s\n", idx, addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
        }
        printf("\nEnter indexes to delete (space separated, -1 to stop): ");
        while (1) {
            int idx;
            scanf("%d", &idx);
            if (idx == -1) 
                break;
            deleteIndexes[deleteCount++] = idx;
        }
    }
    else if (choice == 2 || choice == 3) {
        int found = -1;
        for (int i = 0; i < addressBook->contactCount; i++) {
            if ((choice == 2 && strcmp(addressBook->contacts[i].phone, temporary) == 0) || (choice == 3 && strcmp(addressBook->contacts[i].email, temporary) == 0)) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            printf("Contact not found.\n");
            return;
        }
        deleteIndexes[deleteCount++] = found;
    }
    else {
        printf(" Invalid choice.\n");
        return;
    }

    printf("\nAre you sure to delete %d contact(s)? (y/n): ", deleteCount);
    char confirm;
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf(" Deletion cancelled.\n");
        return;
    }
     for (int i = 0; i < deleteCount; i++) {
        int idx = deleteIndexes[i];
        for (int j = idx; j < addressBook->contactCount - 1; j++) {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }
        addressBook->contactCount--;
        for (int k = i + 1; k < deleteCount; k++) {
            if (deleteIndexes[k] > idx) deleteIndexes[k]--;
        }
    }
    printf(" %d contact(s) deleted successfully!\n",deleteCount);

}


