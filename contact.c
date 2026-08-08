#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    printf("Select sort criteria:\n");
    printf("1. Sort by name\n");
    printf("2. Sort by phone\n");
    printf("3. Sort by email\n");
    printf("Enter your choice: ");
    int sortChoice;
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
        printf("%-25s %-25s %-25s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

int checkPhoneNum(AddressBook *addressBook, char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int getContactdetails(AddressBook *addressBook)
{
    int choice, flag, index;
    char name[50], phone[50], email[50];
    printf("Select the Contact to be edited:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email id\n");
    printf("Enter the Choice:");
    getchar();
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        do
        {
            printf("Enter the name: ");
            getchar();
            scanf("%[^\n]", name);
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
        break;
        case 2:
        {
            do
            {
                printf("Enter the phone number: ");
                getchar();
                scanf("%s", phone);
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
                scanf("%s", email);
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

void initialize(AddressBook *addressBook) {
    // addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    int len, invalid;
    char name[50], phone[50], email[50];
    getchar();
    printf("Enter the name: ");
    scanf("%[^\n]", name);
    while(getchar() != '\n');
    do
    {
        printf("Enter the phone number: ");
        scanf("%s", phone);
        len = strlen(phone);
        getchar();
        if (len != 10)
        {
            printf("Invalid phone number...Re-enter the phone number\n");
        }
        else
        {
            if (checkPhoneNum(addressBook, phone) == 0)
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
        scanf("%s", email);
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
        if (strchr(email, '@') == NULL || strstr(email,".com") == NULL) 
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
            while(getchar() != '\n'); // Clearing input buffer
        } while (choice < 1 || choice > 3);
        int flag = 0;
        switch (choice)
        {
            case 1:
            {
                char name[100];
                printf("Enter the name to be searched: ");
                scanf("%[^\n]", name);
                while(getchar() != '\n'); // Clearing input buffer
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(name, addressBook->contacts[i].name) == 0)
                    {
                        printf("%s      %s      %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    printf("Name not found");
                }
                break;
            }
            case 2:
            {
                char phoneNum[100];
                printf("Enter the phone number to be searched: ");
                scanf("%[^\n]", phoneNum);
                while(getchar() != '\n');
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(phoneNum, addressBook->contacts[i].phone) == 0)
                    {
                        printf("%s      %s      %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    printf("Phone Number not found");
                }
                break;
            }
            case 3:
            {
                char email[100];
                printf("Enter the email to be searched: ");
                scanf("%[^\n]", email);
                while(getchar() != '\n');
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(email, addressBook->contacts[i].email) == 0)
                    {
                        printf("%s      %s      %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        flag = 1;
                    }
                }
                if (flag == 0)
                {
                    printf("Email not found");
                }
                break;
            }
            default:
                break;
        }
        printf("Do you want to search again (Y/N): ");
        scanf("%c", &continuechoice);
        while(getchar() != '\n');
    } while (continuechoice == 'Y' || continuechoice == 'y');
}

void editContact(AddressBook *addressBook)
{  
	/* Define the logic for Editcontact */
    int index = getContactdetails(addressBook);
    int choice, flag;
    char name[50], phone[50], email[50];
    int len, invalid;
    printf("1. Edit the Name\n");
    printf("2. Edit the Phone Number\n");
    printf("3. Edit the Mail id\n");
    printf("4. Edit all the details\n");
    printf("Enter the choice: ");
    getchar();
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        {
            printf("Enter the New Name: ");
            getchar();
            scanf("%[^\n]", name);
            strcpy(addressBook->contacts[index].name, name);
        }
        break;
        case 2:
        {
            do
            {
                printf("Enter the New Phone number: ");
                getchar();
                scanf("%s", phone);
                len = strlen(phone);
                if (len != 10)
                {
                    printf("Invalid phone number...Re-enter the phone number\n");
                }
            } while (len != 10);
            strcpy(addressBook->contacts[index].phone, phone);
        }
        break;
        case 3:
        {
            do
            {
                printf("Enter the New Email id: ");
                getchar();
                scanf("%s", email);
                if (strchr(email, '@') == NULL || strstr(email,".com") == NULL)
                {
                    printf("Invalid Email id... Re-enter the Email id\n");
                    invalid = 1;
                }
                else
                {
                    invalid = 0;
                }
            } while (invalid);
            strcpy(addressBook->contacts[index].email, email);
        }
        break;
        case 4:
        {
            printf("Enter the New Name: ");
            getchar();
            scanf("%[^\n]", name);
            strcpy(addressBook->contacts[index].name, name);
            do
            {
                printf("Enter the New Phone number: ");
                getchar();
                scanf("%s", phone);
                len = strlen(phone);
                if (len != 10)
                {
                    printf("Invalid phone number...Re-enter the phone number\n");
                }
            } while (len != 10);
            strcpy(addressBook->contacts[index].phone, phone);
            do
            {
                printf("Enter the New Email id: ");
                getchar();
                scanf("%s", email);
                if (strchr(email, '@') == NULL || strstr(email,".com") == NULL)
                {
                    printf("Invalid Email id... Re-enter the Email id\n");
                    invalid = 1;
                }
                else
                {
                    invalid = 0;
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
    
    for (int i = index; i < addressBook->contactCount; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    (addressBook->contactCount)--;
}
