#ifndef FILE_H
#define FILE_H

#include "contact.h"

// Writes all contacts in addressBook to contact.txt in the format:
//   #<count>#
//   name,phone,email
//   ...
void saveContactsToFile(AddressBook *addressBook);

// Reads contacts back from contact.txt into addressBook.
// If contact.txt does not exist, addressBook is left with 0 contacts.
void loadContactsFromFile(AddressBook *addressBook);

#endif
