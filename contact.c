#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void initialize(AddressBook *addressBook) 
{
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

int isDuplicatePhone(AddressBook *addressBook, char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int getContactdetails(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0) 
    {
        printf("Address book is empty!\n");
        return -1;
    }

    int choice = 0, flag = 0, index = 0;
    char name[50], phone[20], email[50];

    printf("Select the Contact to be edited:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email id\n");
    printf("Enter the Choice:");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
        case 1:
        {
            do
            {
                printf("Enter the name: ");
                scanf("%49[^\n]", name);
                getchar();
                flag = 0;
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(name, addressBook->contacts[i].name) == 0)
                    {
                        index = i;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("Name doesn't exist... Re-enter the name\n");
                }
            } while (flag == 0);
        }
        break;

        case 2:
        {
            do
            {
                printf("Enter the phone number: ");
                scanf("%19s", phone);
                getchar();
                flag = 0;
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(phone, addressBook->contacts[i].phone) == 0)
                    {
                        index = i;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("Phone number doesn't exist... Re-enter the Phone number");
                }
            } while (flag == 0);
        }
        break;

        case 3:
        {
            do
            {
                printf("Enter the Mail id: ");
                getchar();
                scanf("%49s", email);
                flag = 0;
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(email, addressBook->contacts[i].email) == 0)
                    {
                        index = i;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("Mail id doesn't exist... Re-enter the Mail id");
                }
            } while (flag == 0);
        }
        break;
    }
    return index;
}

void createContact(AddressBook *addressBook)
{
    int len = 0, invalid = 0;
    char name[50], phone[20], email[50];

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("AddressBook is Full\n");
        return;
    }

    printf("Enter the name: ");
    scanf("%49[^\n]", name);
    getchar();

    do
    {
        printf("Enter the phone number: ");
        scanf("%19s", phone);
        getchar();
        len = strlen(phone);
        if (len != 10)
        {
            printf("Invalid phone number...Re-enter the phone number\n");
        }
        else
        {
            if (isDuplicatePhone(addressBook, phone))
            {
                printf("Phone number already exists...Re-enter the phone number\n");
                len = 0;
            }
        }
    } while (len != 10);
    
    do
    {
        invalid = 0;
        printf("Enter the Email id: ");
        scanf("%49s", email);
        getchar();
        for (int i = 0; email[i] != '\0'; i++)
        {
            if (isupper(email[i]))
            {
                printf("Invalid Email id... Only lowercase to be entered\n");
                invalid = 1;
                break;
            }
        }

        char *at = strchr(email, '@');
        len = strlen(email);
        if (at == NULL || strchr(at + 1, '@') != NULL ||  len < 4 || strcmp(email + len - 4, ".com") != 0)
        {
            printf("Invalid Email id... Re-enter the Email id\n");
            invalid = 1;
        }
    } while (invalid);

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    (addressBook->contactCount)++;
    
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    char continuechoice;
    printf("1. Search by Name\n2. Search by phone\n3. Search by email\n");
    do
    {
        do // Accepting only valid inputs from user 
        {
            printf("Enter the choice for search: ");
            scanf("%d", &choice);
            getchar();
        } while (choice < 1 || choice > 3);

        int found = -1;
        switch (choice)
        {
            case 1:
            {
                char name[50];
                printf("Enter the name to be searched: ");
                scanf("%49[^\n]", name);
                getchar();
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(name, addressBook->contacts[i].name) == 0)
                    {
                        found = i;
                        break;
                    }
                }
                if (found == -1)
                {
                    printf("Name not found\n");
                }
                else
                {
                    printf("%-50s %-20s %-50s\n", addressBook->contacts[found].name, addressBook->contacts[found].phone, addressBook->contacts[found].email);
                }
                break;
            }
            case 2:
            {
                char phoneNum[20];
                printf("Enter the phone number to be searched: ");
                scanf("%19[^\n]", phoneNum);
                getchar();
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(phoneNum, addressBook->contacts[i].phone) == 0)
                    {
                        found = i;
                        break;
                    }
                }
                if (found == -1)
                {
                    printf("Phone Number not found\n");
                }
                else
                {
                    printf("%-50s %-20s %-50s\n", addressBook->contacts[found].name, addressBook->contacts[found].phone, addressBook->contacts[found].email);
                }
                break;
            }
            case 3:
            {
                char email[50];
                printf("Enter the email to be searched: ");
                scanf("%49[^\n]", email);
                getchar();
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(email, addressBook->contacts[i].email) == 0)
                    {
                        found = i;
                        break;
                    }
                }
                if (found == -1)
                {
                    printf("Email not found\n");
                }
                else
                {
                    printf("%-50s %-20s %-50s\n", addressBook->contacts[found].name, addressBook->contacts[found].phone, addressBook->contacts[found].email);
                }
                break;
            }
        }
        printf("Do you want to search again (Y/N): ");
        scanf("%c", &continuechoice);
        getchar();
    } while (continuechoice == 'Y' || continuechoice == 'y');
}

void editContact(AddressBook *addressBook)
{  
	/* Define the logic for Editcontact */
    int index = getContactdetails(addressBook);

    if (index == -1) 
    {
        printf("No contact to edit!\n");
        return;
    }

    int choice = 0, len = 0, invalid = 0;
    char name[50], phone[50], email[50];

    printf("1. Edit the Name\n");
    printf("2. Edit the Phone Number\n");
    printf("3. Edit the Mail id\n");
    printf("4. Edit all the details\n");
    printf("Enter the choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
        case 1:
        {
            printf("Enter the New Name: ");
            scanf("%49[^\n]", name);
            getchar();
            strcpy(addressBook->contacts[index].name, name);
        }
        break;

        case 2:
        {
            do
            {
                printf("Enter the phone number: ");
                scanf("%19s", phone);
                getchar();
                len = strlen(phone);
                if (len != 10)
                {
                    printf("Invalid phone number...Re-enter the phone number\n");
                }
                else
                {
                    if (isDuplicatePhone(addressBook, phone))
                    {
                        printf("Phone number already exists...Re-enter the phone number\n");
                        len = 0;
                    }
                }
            } while (len != 10);
            strcpy(addressBook->contacts[index].phone, phone);
        }
        break;

        case 3:
        {
            do
            {
                invalid = 0;
                printf("Enter the Email id: ");
                scanf("%49s", email);
                getchar();
                for (int i = 0; email[i] != '\0'; i++)
                {
                    if (isupper(email[i]))
                    {
                        printf("Invalid Email id... Only lowercase to be entered\n");
                        invalid = 1;
                        break;
                    }
                }

                char *at = strchr(email, '@');
                len = strlen(email);
                if (at == NULL || strchr(at + 1, '@') != NULL ||  len < 4 || strcmp(email + len - 4, ".com") != 0)
                {
                    printf("Invalid Email id... Re-enter the Email id\n");
                    invalid = 1;
                }
            } while (invalid);
            strcpy(addressBook->contacts[index].email, email);
        }
        break;
        
        case 4:
        {
            printf("Enter the New Name: ");
            scanf("%49[^\n]", name);
            getchar();
            strcpy(addressBook->contacts[index].name, name);

            do
            {
                printf("Enter the phone number: ");
                scanf("%19s", phone);
                getchar();
                len = strlen(phone);
                if (len != 10)
                {
                    printf("Invalid phone number...Re-enter the phone number\n");
                }
                else
                {
                    if (isDuplicatePhone(addressBook, phone))
                    {
                        printf("Phone number already exists...Re-enter the phone number\n");
                        len = 0;
                    }
                }
            } while (len != 10);
            strcpy(addressBook->contacts[index].phone, phone);

            do
            {
                invalid = 0;
                printf("Enter the Email id: ");
                scanf("%49s", email);
                getchar();
                for (int i = 0; email[i] != '\0'; i++)
                {
                    if (isupper(email[i]))
                    {
                        printf("Invalid Email id... Only lowercase to be entered\n");
                        invalid = 1;
                        break;
                    }
                }

                char *at = strchr(email, '@');
                len = strlen(email);
                if (at == NULL || strchr(at + 1, '@') != NULL ||  len < 4 || strcmp(email + len - 4, ".com") != 0)
                {
                    printf("Invalid Email id... Re-enter the Email id\n");
                    invalid = 1;
                }
            } while (invalid);
            strcpy(addressBook->contacts[index].email, email);
        }
        break;
    } 
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index = getContactdetails(addressBook);

    if (index == -1) 
    {
        printf("No contact to delete!\n");
        return;
    }
    
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    (addressBook->contactCount)--;
}

void listContacts(AddressBook *addressBook) 
{
    int sortChoice;
    printf("Select sort criteria:\n");
    printf("1. Sort by name\n");
    printf("2. Sort by phone\n");
    printf("3. Sort by email\n");
    printf("Enter your choice: ");
    scanf("%d", &sortChoice);
    getchar();

    int size = addressBook->contactCount;

    Contact temp;
    switch (sortChoice)
    {
        case 1:
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - i - 1; j++)
                {
                    if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0)
                    {
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
        }
        break;

        case 2:
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - i - 1; j++)
                {
                    if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0)
                    {
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
        }
        break;

        case 3:
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - i - 1; j++)
                {
                    if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0)
                    {
                        temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j+1];
                        addressBook->contacts[j+1] = temp;
                    }
                }
            }
        }
        break;
    }
    
    for (int i = 0; i < size; i++)
    {
        // Left aligning the string to be printed
        printf("%-50s %-20s %-50s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    return; // Exit the program
}
