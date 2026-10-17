#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// Persists the entire address book to contact.txt.
// File format:
//   #<contactCount>#
//   name,phone,email        (one line per contact)
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "w");

    // fopen can fail (permissions, disk full, etc). Bail out rather than
    // dereferencing a NULL file pointer below.
    if (fptr == NULL)
    {
        printf("Error: could not open contact.txt for writing.\n");
        return;
    }

    int size = addressBook->contactCount;
    fprintf(fptr, "#%d#\n", size);
    for (int i = 0; i < size; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fptr);
}

// Loads contacts from contact.txt into addressBook.
// If the file doesn't exist, addressBook->contactCount is left as-is
// (the caller is expected to have already zero-initialized it).
void loadContactsFromFile(AddressBook *addressBook)
{
    // Line buffer for reading the header and each "name,phone,email" row.
    // All reads below use an explicit width limit (199 chars) matching
    // this buffer's size, so a long line can never overflow it.
    char str[200];
    FILE *fptr = fopen("contact.txt", "r");
    if (fptr == NULL)
    {
        printf("File is not present\n");
        return;
    }

    // Header line looks like "#16#" - strip the leading '#', then split
    // on '#' to get the contact count as a string, and convert to int.
    fscanf(fptr, "%199[^\n]", str);
    int size = atoi(strtok(&str[1], "#"));
    if (size < 0 || size > MAX_CONTACTS) 
    {
        printf("Error: Invalid contact count in file!\n");
        fclose(fptr);
        return;
    }

    addressBook->contactCount = size;

    // Each subsequent line is "name,phone,email" - split on commas.
    for (int i = 0; i < size; i++)
    {
        fscanf(fptr, " %199[^\n]", str);
        
        char *name = strtok(str, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        
        if (name == NULL || phone == NULL || email == NULL) 
        {
            printf("Error: Malformed line %d in file!\n", i+1);
            addressBook->contactCount = i;  // Keep what we loaded so far
            fclose(fptr);
            return;
        }
        
        strcpy(addressBook->contacts[i].name, name);
        strcpy(addressBook->contacts[i].phone, phone);
        strcpy(addressBook->contacts[i].email, email);
    }

    fclose(fptr);
}