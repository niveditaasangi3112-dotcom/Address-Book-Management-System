#ifndef CONTACT_H
#define CONTACT_H


#include<stdio.h>
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void editMenu(AddressBook *addressBook,int matchedIndices);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBooksortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
