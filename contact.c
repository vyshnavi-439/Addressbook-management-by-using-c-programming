#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available.\n");
        return;
    }

    // If sortCriteria = 0, ask user
    if (sortCriteria == 0)
    {
        printf("\nSort Contacts by:\n");
        printf("1. Name\n2. Phone\n3. Email\n");
        printf("Enter your choice: ");
        scanf("%d", &sortCriteria);
    }

    // ------------------ SORT CONTACTS FIRST ------------------
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            int compare = 0;

            if (sortCriteria == 1) // Sort by Name
            {
                compare = strcmp(addressBook->contacts[i].name,
                                 addressBook->contacts[j].name);

                // If names are same → sort by phone
                if (compare == 0)
                {
                    compare = strcmp(addressBook->contacts[i].phone,
                                     addressBook->contacts[j].phone);
                }
            }
            else if (sortCriteria == 2) // Sort by Phone
            {
                compare = strcmp(addressBook->contacts[i].phone,
                                 addressBook->contacts[j].phone);
            }
            else if (sortCriteria == 3) // Sort by Email
            {
                compare = strcmp(addressBook->contacts[i].email,
                                 addressBook->contacts[j].email);
            }

            // Swap if out of order
            if (compare > 0)
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    // ------------------ PRINT SORTED CONTACTS ------------------
    printf("\n---- Sorted Contact List ----\n");

    printf("\n+---+-----------------+--------------+----------------------------+\n");
    printf("| No| Name            | Mobile       | Email                      |\n");
    printf("+---+-----------------+--------------+----------------------------+\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("|%-2d | %-15s | %-12s | %-26s |\n",
            i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    printf("+---+-----------------+--------------+----------------------------+\n");
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

//1.to validate name
int validate_name(char *name)
    {
        int i=0;
        while(name[i]!='\0')
        {
            if(isalpha(name[i])||name[i]==' '|| name[i]=='.')
            i++;
            else
            return 1;
        }
        return 0;
    }

//2.to validate the phone number
int validate_phone(char *phone, AddressBook *addressBook,int currentIndex)
{
    // Check for valid length
    if (strlen(phone) != 10)
        return 1;

    // Check all digits
    for (int i = 0; phone[i] != '\0'; i++)
    {
        if (!isdigit(phone[i]))
            return 1;
    }

    // Check for uniqueness
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i!=currentIndex && strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
          printf("This number already exists! Please enter another number.\n");
            return 1; // duplicate found
        }
    }

    return 0; // valid and unique
}

//3.to validate email 
int validate_email(char *email, AddressBook *addressBook, int currentIndex)
{
    int len = strlen(email);

    // 1. Minimum length check (ex: a@b.com → 7 chars)
    if (len < 7)
        return 1;

    // 2. Must start with an alphabet
    if (!isalpha(email[0]))
        return 1;

    // 3. Must contain '@'
    char *at = strchr(email, '@');
    if (at == NULL)
        return 1;

    // 4. Must end with ".com"
    if (strcmp(email + len - 4, ".com") != 0)
        return 1;

    // 5. There must be something before '@'
    if (at == email)
        return 1;

    // 6. There must be something between '@' and ".com"
    if ((at + 1) >= (email + len - 4))
        return 1;

    // 7. Uniqueness check (skip current contact when editing)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i != currentIndex && strcasecmp(email, addressBook->contacts[i].email) == 0)
            return 1;
    }

    return 0;  // valid email
}


//************************************---Create contact----***********************************************************

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    //get input data from the user
    char name[50], mobile_no[20], email[50];
    int valid;

    do
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", name);
        valid = validate_name(name);
        if (valid == 1)
            printf("ERROR: Invalid name. Please try again.\n");
    } while (valid == 1);

    do
    {
        printf("Enter mobile number: ");
        scanf(" %[^\n]", mobile_no);
        valid = validate_phone(mobile_no,addressBook,-1);
        if (valid == 1)
            printf("ERROR: Invalid number. Please try again.\n");
    } while (valid != 0);

    do
    {
        printf("Enter email: ");
        scanf(" %[^\n]", email);
        valid = validate_email(email,addressBook,-1);
        if (valid == 1)
            printf("ERROR: Invalid email. Please try again.\n");
    } while (valid != 0);

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile_no);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    (addressBook->contactCount)++;

    printf("\nContact saved successfully..!\n");
}

    
//----------------search a contact by using name-------------------
int searchbyname(AddressBook *addressBook)
{
    char search[50];
    int found = 0;

    printf("Enter the name to search: ");
    scanf(" %[^\n]", search);  // read full name including spaces

    // Searching for the contact by name
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, search) == 0)
        {
            printf("\nContact found:\n");
            printf("Name : %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    return found;
}


//to search a contact by using phone number
int searchbyphone(AddressBook *addressBook)
{
    char search[15];
    int found = 0;

    printf("\nEnter the phone number to search: ");
    scanf("%s", search);

    while (1)
    {
        int valid = 1;

        for (int i = 0; search[i] != '\0'; i++)
        {
            if (!isdigit(search[i]))
            {
                valid = 0;
                break;
            }
        }

        if (valid)
            break;
        else
        {
            printf("Please enter a numeric phone number: ");
            scanf("%s", search);   //again ask user to enter a valid phone number
        }
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, search) == 0)
        {
            printf("\nContact found:\n");
            printf("Name: %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");

    return found;     
}


//to serch a contact by using email
int searchbyemail(AddressBook *addressBook)
{

    char search[50];
    int found=0;
    printf("Enter the email to search: ");
    scanf("%s", search);
    // if valid input entered,then displaying the details
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if ((strcmp(addressBook->contacts[i].email, search) == 0))
        {
            printf("\nContact found:\n");
            printf("Name : %s\tPhone : %s\tEmail : %s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            found = 1;
            break;
        }
    }

    if (!found)
    printf("Contact not found!\n");
    return found;
}

//--------------search contact-------------------
int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to search.\n");
        return 0;
    }

    int choice;
    while(1)
    {
       printf("\nEnter by which you want to search:\n");
       printf("1.Name\n2.Phone\n3.Email\n4.Exit search menu ");
       scanf("%d",&choice);
       switch(choice)
       {
        case 1:
        searchbyname(addressBook);
        break;
        case 2:
        searchbyphone(addressBook);
        break;
        case 3:
        searchbyemail(addressBook);
        break;
        case 4:
        printf("Exiting search..\n");
        return 0;
        default:
        printf("Invalid search option entered..! please try again\n");
        
       }
    }
}

//---------------------Edit contact-------------------


void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    
    //if no contacts exist,editing is immpossible
    if(addressBook->contactCount==0)
    {
        printf("No contacts available to edit.\n");
        return ;//exit the function
    }

    int searchCriteria;
    printf("\nSearch by:\n1.Name\n2.Phone\n3.Email\nEnter your choice: ");
    scanf("%d",&searchCriteria);

    char search[50];// Temporary buffer to store the value entered by the user 
    printf("Enter the value to search: ");
    // Read the value the user wants to search for (name/phone/email)
    scanf(" %[^\n]",search);

    int index=-1; // This will store which contact matched the search (-1 = not found)

    //--------------    SEARCH LOGIC   -------------------
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(searchCriteria==1 && strcmp(addressBook->contacts[i].name,search)==0)
        {
            index=i;//contact found by name
            break;
        }
        else if(searchCriteria==2 && strcmp(addressBook->contacts[i].phone,search)==0)
        {
            index=i;//contact found by phone
            break;
        }
        else if(searchCriteria ==3 && strcmp(addressBook->contacts[i].email,search)==0)
        {
            index=i;//contact found by email
            break;
        }
    }
    //if index is still -1 ,then it means not contact found 
    if(index==-1)
    {
        printf("Contact not found...!\n");
        return;
    }

    //-------------------------ONCE CONTACT FOUND---------------------
    printf("\nContact found:\n");
    printf("1.Name:  %s\n", addressBook->contacts[index].name);
    printf("2.Phone: %s\n", addressBook->contacts[index].phone);
    printf("3.Email: %s\n", addressBook->contacts[index].email);
 
    int editOption;
    printf("\nWhat do you want to edit?\n1.Name\n2.Phone\n3.Email\nEnter choice: ");
    scanf("%d", &editOption);

    char newValue[50];
    int valid;

    // ----------------------- EDIT NAME -----------------------
    if (editOption == 1)
    {
        do
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);

            // validate new name
            valid = validate_name(newValue);

            if (valid == 1)
                printf("ERROR: Invalid name. Try again.\n");

        } while (valid == 1);

        // If valid, update the name
        strcpy(addressBook->contacts[index].name, newValue);
        printf("\nName updated successfully!\n");
    }

    // ----------------------- EDIT PHONE -----------------------
    else if (editOption == 2)
    {
        do
        {
            printf("Enter new phone: ");
            scanf(" %[^\n]", newValue);

            // validate phone (-1 replaced with index to avoid duplicate with same contact)
            valid = validate_phone(newValue, addressBook, index);

            if (valid == 1)
                printf("ERROR: Invalid number. Try again.\n");

        } while (valid == 1);

        strcpy(addressBook->contacts[index].phone, newValue);
        printf("\nPhone number updated successfully!\n");
    }

    // ----------------------- EDIT EMAIL -----------------------
    else if (editOption == 3)
    {
        do
        {
            printf("Enter new email: ");
            scanf(" %[^\n]", newValue);

            // validate email
            valid = validate_email(newValue, addressBook, index);

            if (valid == 1)
                printf("ERROR: Invalid email. Try again.\n");

        } while (valid == 1);

        strcpy(addressBook->contacts[index].email, newValue);
        printf("\nEmail updated successfully!\n");
    }
    else
    {
        // Wrong option entered
        printf("Invalid option!\n");
    }
    
}

//-----------------------------Delete contact------------------------
void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */

    // If no contacts exist, nothing to delete
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to delete.\n");
        return;
    }

    int searchCriteria;
    char search[50];

    // Ask user how they want to search for the contact
    printf("\nDelete by:\n1.Name\n2.Phone\n3.Email\nEnter your choice: ");
    scanf("%d", &searchCriteria);

    // Ask user for the actual search string
    printf("Enter search value: ");
    scanf(" %[^\n]", search);

    int index = -1;  
    // Will store the index of the contact to delete (-1 = not found)

    // ----------------------- SEARCH LOGIC -----------------------
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (searchCriteria == 1 &&
            strcmp(addressBook->contacts[i].name, search) == 0)
        {
            index = i;   // found by name
            break;
        }
        else if (searchCriteria == 2 &&
                 strcmp(addressBook->contacts[i].phone, search) == 0)
        {
            index = i;   // found by phone
            break;
        }
        else if (searchCriteria == 3 &&
                 strcmp(addressBook->contacts[i].email, search) == 0)
        {
            index = i;   // found by email
            break;
        }
    }

    // If still -1, contact wasn't found
    if (index == -1)
    {
        printf("Contact not found!\n");
        return;
    }

    // ----------------------- CONTACT FOUND -----------------------
    printf("\nContact found:\n");
    printf("Name :  %s\n", addressBook->contacts[index].name);
    printf("Phone:  %s\n", addressBook->contacts[index].phone);
    printf("Email:  %s\n", addressBook->contacts[index].email);

    // Ask user confirmation before deleting
    char confirm;
    printf("\nAre you sure you want to delete this contact? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    // ----------------------- DELETE LOGIC -----------------------
    // Shift all contacts after index to one position left
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    // Reduce contact count after deletion
    (addressBook->contactCount)--;
    printf("\nContact deleted successfully.........!\n");
}

