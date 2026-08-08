#ifndef CONTACT_H
#define CONTACT_H

// Maximum number of contacts the address book can hold.
// The Contact array is statically sized to this at compile time.
#define MAX_CONTACTS 100

// A single contact record.
typedef struct {
    char name[50];
    char phone[20];   // Stored as exactly 10 digits + null terminator
    char email[50];
} Contact;

// The address book: a fixed-size array of contacts plus a count of how
// many slots are currently in use (contacts[0..contactCount-1] are valid).
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

// --- Core contact operations (contact.c) ---
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

// Returns 1 if the phone number is NOT already used (safe to add),
// 0 if a contact with that phone number already exists.
int checkPhoneNum(AddressBook *addressBook, char *phone);

// Prompts the user to search for a contact by name/phone/email and
// returns the index of the matching contact in addressBook->contacts[],
// or -1 if the address book is empty.
int getContactdetails(AddressBook *addressBook);

#endif