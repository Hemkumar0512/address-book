#ifndef POPULATE_H
#define POPULATE_H

#include "contact.h"

// Fills addressBook with a small set of built-in dummy contacts.
// Useful for testing before contact.txt exists / has real data.
void populateAddressBook(AddressBook* addressBook);

#endif