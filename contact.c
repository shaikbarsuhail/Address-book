#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include<unistd.h>
int size, flag ;    //   Here position,size,flag is declared globally 
int position[MAX_CONTACTS];

/*............................................................................................................................................
Name of the function : listContacts 

Description          :
This function sorts and displays all contacts in the address book.
The user can sort contacts by name, phone number, or email address.
It uses Bubble Sort and strcmp() to arrange contacts in ascending order.
.................................................................................................................................................
*/
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria

    // Declare variables for menu choice and loop counters.
    int sortChoice;
    int i , j;
    if(addressBook->contactCount<1)
    {
        printf("No Contacts are avaliable.\n\n");// if no contacts is there it will show no contacts
        return ;
    }
    do
    {
        // Assume the input is valid at the beginning of each iteration.
        flag = 1;
        printf("\nSelect sort criteria\n");
        printf("1. Sort by name\n");
        printf("2. Sort by phone\n");
        printf("3. Sort by email\n");
        printf("4. Exit\n");


        // Display sorting options to the user.
        printf("Enter your choice: ");
        if (scanf("%d",&sortChoice) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid Option !\n\n");
            flag++;
            continue;
        }
        getchar();
        
        switch(sortChoice)
        {
            case 1:

            // Sort contacts alphabetically by name using bubble sort.
            for(i = 0; i < addressBook->contactCount -1; i++)
            {
                for(j = 0; j < addressBook->contactCount - i - 1;j++)
                {
                    // strcmp() returns a positive value when the first name
                    // should come after the second name alphabetically.

                    if( strcmp ( addressBook->contacts[j].name , addressBook->contacts[j+1].name ) > 0) 
                    {
                        // Swap the two contacts.
                        Contact temp = addressBook->contacts[ j ];
                        addressBook->contacts[ j ] = addressBook->contacts[ j + 1 ]; 
                        addressBook->contacts[ j + 1 ] = temp;
                    }
                }

            }
            // Display contacts sorted by name.
            printf("\nSorting contacts by the name :\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
            printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

            for(i = 0; i <addressBook->contactCount; i++)
            {
                printf("%-8d %-25s %-15s %-35s\n",i+1,
                addressBook->contacts[ i ].name,
                addressBook->contacts[ i ].phone,
                addressBook->contacts[ i ].email);
            }
            break;

            case 2:
            // Sort contacts by phone number using bubble sort.
            for(i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(j = 0; j < addressBook->contactCount - i - 1; j++)
                {
                    // Compare the phone numbers of adjacent contacts.
                    if( strcmp ( addressBook->contacts[ j ].phone,addressBook->contacts[ j + 1 ].phone) > 0) 

                    {
                        // Swap the contacts if their order is incorrect.
                        Contact temp = addressBook->contacts[ j ];
                        addressBook->contacts[ j ] = addressBook->contacts[ j + 1 ];  
                        addressBook->contacts[ j + 1 ] = temp;
                    }
                }

            }
            // Display contacts sorted by phone number.
            printf("\nSorting contacts by the phone number :\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
            printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
            for(i = 0 ; i < addressBook->contactCount ; i++)
            {
                printf("%-8d %-25s %-15s %-35s\n",i+1,
                addressBook->contacts[ i ].name,
                addressBook->contacts[ i ].phone,
                addressBook->contacts[ i ].email);
            }
            break;

            case 3:
            // Sort contacts by email address using bubble sort.
            for( i = 0 ; i < addressBook->contactCount - 1 ; i++)
            {
                for( j = 0 ; j < addressBook->contactCount - i - 1 ; j++)
                {
                    // Compare the email addresses of adjacent contacts.
                    if( strcmp ( addressBook->contacts[ j ].email,addressBook->contacts[ j+1 ].email) > 0 )
                    {
                        // Swap the contacts if their order is incorrect.
                        Contact temp = addressBook->contacts[ j ];
                        addressBook->contacts[ j ] = addressBook->contacts[ j + 1 ]; 
                        addressBook->contacts[ j + 1 ]=temp;
                    }
                }

            }

            // Display contacts sorted by email address.
            printf("\nSorting contacts by the Email :\n");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
            printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
            for( i = 0 ; i <addressBook->contactCount ; i++)
            {
                printf("%-8d %-25s %-15s %-35s\n",i+1,
                addressBook->contacts[ i ].name,
                addressBook->contacts[ i ].phone,
                addressBook->contacts[ i ].email);
            }
            break;
            case 4:
            // Exit from the listContacts function.
            return;

            default:
            // Display an error message for an invalid menu option.
            printf("Invalid option !\n\n");
            flag++;

        }

    }while(flag!=1);// Repeat only when an invalid choice is entered.
 
    
}
//..............................................................................................................................................................................................
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    for(int i=0;i*i<100;i=i+2)
    {
        printf("saving[");
        for(int dash=0;dash<i;dash++)
        {
            printf(".");
        }
        printf("]%d%%\r",i);
        sleep(1);
        fflush(stdout);
    }
    printf("Saved and Exit....\n");
    exit(EXIT_SUCCESS); // Exit the program
}

/*....................................................................................................................................................................................................

Function Name: createContact

Description:
This function creates a new contact in the address book. It accepts the
contact name, phone number, and email address from the user. After all
details pass validation, it saves the contact in the address book and
updates the contact count.

.....................................................................................................................................................................................................
*/
void createContact(AddressBook *addressBook)
{
	
    
    // Check whether the address book has reached its maximum capacity.
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Contact list is full\n\n");
        return;             // Do not continue creating a contact.
    }

    int num ;
    num = addressBook->contactCount;
    printf("%s:%d\n\n","Contact count",num);

    char name[50];
    int i;
    int len;  // Declaring variables 
    /*
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    Name Validation:
    1. Name must contain at least 3 characters.
    2. Name can contain only uppercase letters, lowercase letters, and spaces.
    3. Duplicate names are not allowed.
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    */
    do
    {   
        flag = 1;  // Assume valid input until a validation check fails.
        printf("Enter the Name: ");
        scanf(" %49[^\n]", name);  // Read a name including spaces.

        // Find the number of characters in the name.
        len = strlen(name);
        // A name must contain at least three characters.
        if (len > 2)
        {

            // Check that every character is a letter or a space.
            for (i = 0; name[i] != '\0'; i++)
            {
                if ((name[i] >= 'A' && name[i] <= 'Z') ||
                    (name[i] >= 'a' && name[i] <= 'z') ||
                    name[i] == ' ')
                {
                    continue;
                }
                else 
                {
                    printf("Name should contain only alphabets.\n\n");
                    flag++;
                    break;
                }
            }
        }
        else
        {
            printf("Name should contain at least 3 characters.\n\n");
            flag++;
        }

        // Check whether the entered name already exists.
        for (i = 0; flag == 1 && i < addressBook->contactCount; i++)
        {
            if (strcmp(name, addressBook->contacts[i].name) == 0)
            {
                printf("Name must be unique.\n\n");
                flag++;
                break;
            }
        }

    } while (flag != 1);


    char phone[20];

    /* 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Phone Number Validation:
    1. Phone number must contain exactly 10 digits.
    2. The first digit must be between 6 and 9.
    3. Only numeric digits are allowed.
    4. Duplicate phone numbers are not allowed. 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    */
    do
    {
        flag = 1;

        printf("Enter the phone number: ");
        scanf(" %19[^\n]", phone);

        // A valid phone number must have exactly ten digits.
        len = strlen(phone);

        if (len == 10)
        {
            // Indian mobile numbers must start with a digit from 6 to 9.
            if (phone[0] >= '6' && phone[0] <= '9')
            {
                // Check that all characters are digits.
                for (i = 0; phone[i] != '\0'; i++)
                {
                    if ((phone[i]>='A' && phone[i]<='Z') || (phone[i]>='a' && phone[i]<='z')) 
                    {
                        printf("Phone number should not have alphabets.\n\n");
                        flag++;
                        break;
                    }
                    else if(flag==1 && phone[i]==' ')
                    {
                        printf("phone number should not contain spaces.\n\n");
                        flag++;
                        break;

                    }
                    else if(phone[i]>='0' && phone[i]<='9')
                    {
                        continue;
                    }
                    else
                    {
                        printf("phone number contain Invalid %c symbol.\n\n",phone[i]);
                        flag++;
                        break;
                    }
                }
            }
            else
            {
                printf("First digit must be between 6 and 9.\n\n");
                flag++;
            }
        }
        else
        {
            printf("Phone number must contain exactly 10 digits.\n\n");
            flag++;
        }

        // Check whether the phone number is already saved.
        for (i = 0; flag == 1 && i < addressBook->contactCount; i++)
        {
            if (strcmp(phone, addressBook->contacts[i].phone) == 0)
            {
                printf("Number must be unique.\n\n");
                flag++;
                break;
            }
        }

    } while (flag != 1);


    char email[50];

    /* 
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Email Validation:
    1. Email must end with ".com".
    2. Email must contain exactly one '@' symbol.
    3. Email must contain exactly one '.' symbol.
    4. The '.' symbol must appear after '@'.
    5. Email can contain only lowercase letters, digits, '@', and '.'.
    6. Spaces are not allowed in an email address.
    7. Duplicate email addresses are not allowed.
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    */
    do
    {
        flag = 1;
        int dot = 0;
        int atdot = 0;
        int dotPosition = -1;
        int atPosition = -1;

        printf("Enter the Email: ");
        scanf(" %49[^\n]", email);

        // Verify that the email ends with ".com".
        char *res ;
        res = strstr(email,".com");//strstr case in build function is used 

        if (flag==1 && res == NULL)
        {
            printf("Invalid domain !\n\n");
            flag++;
        }
        else if (flag==1 && strcmp(res, ".com") != 0)
        {
            printf("Extra character after ' .com ' in Email ID\n\n");
            flag++;
        }
        
        // Validate each character and count '@' and '.' characters.
        for (i = 0; flag == 1 && email[i] != '\0'; i++)
        {
            if (email[i] == '@')
            {
                atdot++;
                atPosition = i;
                if(email[i+1]=='.' )
                {
                    printf("Email ID must be at least one character between ' @ ' and ' . ' .\n\n" );
                    flag++;
                    break;
                }
            }
            else if (email[i] == '.')
            {
                dot++;
                dotPosition = i;
            }
            else if ((email[i] >= 'a' && email[i] <= 'z') ||
                    (email[i] >= '0' && email[i] <= '9'))
            {
                continue;
            }
            else if (flag==1  && (email[i] >= 'A' && email[i] <= 'Z'))
            {
                printf("Email must contain only lowercase letters and digits.\n\n");
                flag++;
                break;
            }
            else if (flag==1 && email[i] == ' ')
            {
                printf("Spaces are not allowed in email.\n\n");
                flag++;
                break;
            }
            else
            {
                printf("Invalid symbol %c .\n\n", email[i]);
                flag++;
                break;
            }
        }

        // Validate the position and number of '@' and '.' characters.
        if (flag == 1 && atdot == 0)
        {
            printf("Missing '@' in Email ID \n\n");
            flag++;
        }
        else if (flag == 1 && atdot != 1)
        {
            printf("Multiple '@' symbols are not allowed.\n\n");
            flag++;
        }
        else if (flag == 1 && dot == 0)
        {
            printf("Missing '.' in Email ID\n\n");
            flag++;
        }
        else if (flag == 1 && dot != 1)
        {
            printf("Multiple '.' symbols are not allowed.\n\n");
            flag++;
        }
        else if (flag == 1 && (atPosition == 0 || dotPosition == 0))
        {
            printf("Username cannot be empty.\n\n");
            flag++;
        }
        else if (flag == 1 && dotPosition < atPosition)
        {
            printf("In Email ID '.' must appear after ' @ '\n\n");
            flag++;
        }

        
        

        // Check whether the email address already exists.
        for (i = 0; flag == 1 && i < addressBook->contactCount; i++)
        {
            if (strcmp(email, addressBook->contacts[i].email) == 0)
            {
                printf("\nEmail must be unique.\n\n");
                flag++;
                break;
            }
        }

    } while (flag != 1);


    // Copy validated details into the next available contact structure.
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    // Increase the total number of contacts.
    addressBook->contactCount++;
    for(int i=0;i*i<100;i=i+2)
    {
        printf("Loading[");
        for(int dash=0;dash<i;dash++)
        {
            printf(".");
        }
        printf("]%d%%\r",i);
        sleep(1);
        fflush(stdout);
    }

    // Save the newly created contact to the file.
    saveContactsToFile(addressBook);

    printf("Successfully created\n");
}
/*.....................................................................................................................................................................................
Function Name: searchContact

Description:
This function searches for contacts in the address book. The user can search
contacts by name, phone number, or email address. It displays all contacts
that partially match the entered search value.

Validations:
1. The menu option must be a valid numeric value.
2. The menu option must be between 1 and 4.
3. Search text is limited to 29 characters.
4. Previous search results are cleared before every new search.
5. A message is displayed when no matching contact is found.
6. The search is case-insensitive and supports partial matching.
....................................................................................................................................................................................
*/
void searchContact(AddressBook *addressBook) 
{
    char needle[30];
    int i;
    int option;
    int found;
    if(addressBook->contactCount<1)
    {
        printf("No Contacts are avaliable.\n\n");// if no contacts is there it will show no contacts
        return ;
    }

    do
    {

        found=0;
        size=0;    
        // Display the available search options.
        printf("\n1.Search by name\n2.Search by Number\n3.Search by Email\n4.Exit\n");
        printf("select your option:");
        if (scanf("%d", &option) != 1)
        {
            while (getchar() != '\n');// Remove newline from the input buffer.
            printf("Invalid Option!\n\n");
            continue;
        }

        switch(option)
        {
            case 1:
            do
            {
                // Reset previous results before a new name search.
                flag=1;
                found=0;
                size=0;

                // Read the name search text safely.
                printf("search the name:");
                scanf(" %29[^\n]",needle);
                getchar();

                // Check every contact for a partial, case-insensitive name match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch;
                    ch=strcasestr(addressBook->contacts[i].name,needle); 
                    // Store the index of each matching contact.
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;

                    }
                }
                if(found==0)
                {
                    printf("%45s\n\n","Name is not found");
                    flag++;
                }


            }while(flag!=1);

            // Display all contacts matching the name search.
            if(found)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);    
                }
                printf("\n");
            }

            break;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            
            case 2:
            do{
                // Reset previous results before a new phone-number search.
                flag=1;
                found=0;
                size=0;

                // Read the phone-number search text safely.
                printf("search by phone Number:");
                scanf(" %29[^\n]",needle);
                getchar();

                // Check every contact for a partial phone-number match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch;
                    ch=strcasestr(addressBook->contacts[i].phone,needle);
                    // Store the index of each matching contact.
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;

                    }
                }
                // Display a message when no matching phone number is found.
                if(found==0)
                {
                    printf("%45s\n\n","Number is not found");
                    flag++;
                
                }



            }while(flag!=1);


            // Display all contacts matching the phone-number search.
            if(found)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);    
                }
                printf("\n");
            }


            break;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            case 3:
            do{ 

                // Reset previous results before a new email search
                flag=1;
                found=0;
                size=0;  
                // Read the email search text safely.
                printf("search the Email:");
                scanf(" %29[^\n]",needle);
                getchar();


                // Check every contact for a partial, case-insensitive email match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch;
                    ch=strcasestr(addressBook->contacts[i].email,needle);
                    // Store the index of each matching contact.
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;

                    }
                }
                // Display a message when no matching email is found.
                if(found==0)
                {
                
                    printf("%45s\n\n","Email is not found");
                    flag++;
                
                }


            }while(flag!=1);

            // Display all contacts matching the email search.
            if(found)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);    
                }
                printf("\n");
            }

            break;

            case 4:
            // Exit from the searchContact function.
            return ;

            default:
            // Display an error for an invalid menu option.
            printf("Invalid Option !\n\n");

        }
    }while(option!=4);

}
/*...................................................................................................................................................................
Function Name: editContact

Description:
This function allows the user to edit an existing contact in the address
book. The user can search for a contact by name, phone number, or email
address, select a matching contact, and update the selected field.

Validations:
1. The menu option must be a numeric value between 1 and 4.
2. A search result must exist before editing.
3. The selected contact index must be valid.
4. Edited name must contain at least 3 characters and only alphabets/spaces.
5. Edited phone number must contain exactly 10 digits and start from 6 to 9.
6. Edited email must end with ".com" and contain one '@' and one '.'.
7. Duplicate names, phone numbers, and email addresses are not allowed.
8. Edited details are saved to file using saveContactsToFile().
....................................................................................................................................................................
*/
void editContact(AddressBook *addressBook)
{
	// Declare variables for searching, editing, and validation.
    int i;
    int option;
    int index;
    int found;
    int len;
    char needle[30];
    char edit[30];
    if(addressBook->contactCount<1)
    {
        printf("No Contacts are avaliable.\n\n");// if no contacts is there it will show no contacts
        return ;
    }

    do{

        
        // Display fields available for editing.
        printf("\n1.Name\n2.phone number\n3.Email\n4.Exit\n");
        printf("Enter Your option:");
        // Validate that the user enters a numeric option.
        if (scanf("%d", &option) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid Option!\n\n");
            flag++;
            continue;
        }


    
        switch(option)
        {
            case 1:
            do{
                flag=1;
                found=0,size=0;
                printf("search the name:");
                scanf(" %29[^\n]",needle);

                // Search contacts using a partial, case-insensitive name match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch=strcasestr(addressBook->contacts[i].name,needle);
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;
                    }
                }
                // Display an error when no name matches.
                if(found==0)
                {
                    printf("%45s\n\n","Name is not found");
                    flag++;
                }


            }while(flag!=1);


            // Display contacts matching the name search.
            if (found)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",
                    i+1,addressBook->contacts[position[i]].name,
                    addressBook->contacts[position[i]].phone,
                    addressBook->contacts[position[i]].email);
                }
                printf("\n");
            }

            do
            {
                flag=1;
                printf("Select the index Number to Edit :");
                // Validate that the entered index is numeric.
                if(scanf("%d",&index)!=1)
                {
                    while(getchar()!='\n');
                    printf("Invalid Index.\n\n");
                    flag++;
                    continue;

                }
                getchar();
                if(index>size || index<1)
                {
                    printf("Invalid Index.\n\n");
                    flag++;
                }


            }while(flag!=1);

            
            // Convert displayed index into the actual contact index
            index=index-1;
            do{ 

                flag=1; 
                //Check that the name contains only letters and spaces. 
                printf("Enter the name to Edit :");
                scanf(" %29[^\n]",edit);

                len=strlen(edit);
                if(len>2)
                {
                    for(i=0;flag==1 && edit[i]!='\0';i++)
                    {
                        if((edit[i]>='A' && edit[i]<='Z') ||(edit[i]>='a' && edit[i]<='z') || (edit[i]==' '))
                        {
                            continue;
                        }
                        else  
                        {  
                            printf("Name should contain only alphabets.\n\n");
                            flag++;
                            break;
                        }
                    }  
                }
                else 
                {
                    printf("Name should contain at least 3 characters.\n\n");
                    flag++;   
                }



                
                for(i=0;flag==1 && i<addressBook->contactCount;++i)
                {
                    if(strcmp(edit,addressBook->contacts[i].name)==0)
                    {
                        printf("Name must be unique.\n\n");
                        flag++;
                        break;

                    }
                }



            }while(flag!=1);


            strcpy(addressBook->contacts[position[index]].name,edit);


            for(int i=0;i*i<100;i=i+2)
            {
                printf("Loading[");
                for(int dash=0;dash<i;dash++)
                {
                    printf(".");
                }
                printf("]%d%%\r",i);
                sleep(1);
                fflush(stdout);
            }
            saveContactsToFile(addressBook);
            printf("successfully Edited\n");


            break;

            case 2:

            do{


                flag=1;
                found=0;
                size=0;
                printf("search the Mobile Number:");
                scanf(" %29[^\n]",needle);

                // Search contacts using a partial phone-number match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch=strcasestr(addressBook->contacts[i].phone,needle);//strcasestr is used to search the needle
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;
                    }
                }
                // Display an error when no phone number matches.
                if(found==0)
                {
                    printf("%45s\n\n","Number is not found");
                    flag++;
                }



            }while(flag!=1);


            // Display contacts matching the phone-number search.
            if(found)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);
                }
                printf("\n");
            }



            do{


                flag=1;
                printf("Select the index Number :");
                // Validate that the user enters a numeric option.
                if (scanf("%d", &index) != 1)
                {
                    while (getchar() != '\n');
                    printf("Invalid Option !\n\n");
                    flag++;
                }


                if(index>size || index < 1)
                {
                    printf("Invalid Index.\n\n");
                    flag++;
                }


            }while(flag!=1);

            index=index-1;

            do
            {


                flag=1;
                printf("Enter the Mobile Number to Edit :"); 
                scanf(" %29[^\n]",edit);
                getchar();

                // Check that the phone number contains exactly 10 digits.
                len=strlen(edit);
                if(len==10)
                {
                    // Check that the first digit is between 6 and 9.
                    if(edit[0]>='6' && edit[0]<='9')
                    {
                        for(i=0;edit[i]!='\0';i++)
                        {
                        
                            if ((edit[i]>='A' && edit[i]<='Z') || (edit[i]>='a' && edit[i]<='z')) 
                            {
                                printf("Phone number should not have alphabets.\n\n");
                                flag++;
                                break;
                            }
                            else if(flag==1 && edit[i]==' ')
                            {
                                printf("phone number should not contain spaces.\n\n");

                            }
                            else if(edit[i]>='0' && edit[i]<='9')
                            {
                                continue;
                            }
                            else
                            {
                                printf("phone number contain Invalid %c symbol.\n\n",edit[i]);
                                flag++;
                                break;
                            }
                        } 
                    }
                    else
                    {
                        printf("first digit must be between 6 and 9.\n\n");
                        flag++;
                    }
                }
                else
                {
                    printf("phone number must contain exctly 10 digts.\n\n");
                    flag++;   
                }

                                                        
                
                // Check whether another contact already uses this phone number.
                for(i=0;flag==1 && i<addressBook->contactCount;++i)
                {
                    if(strcmp(edit,addressBook->contacts[i].phone)==0) 
                    {               
                        printf("phone Number must be unique.\n");
                        flag++;
                        break;

                    }
                }



            }while(flag!=1);

            // Store the validated edited phone number.
            strcpy(addressBook->contacts[position[index]].phone,edit);
            
            for(int i=0;i*i<100;i=i+2)
            {
                printf("Loading[");
                for(int dash=0;dash<i;dash++)
                {
                    printf(".");
                }
                printf("]%d%%\r",i);
                sleep(1);
                fflush(stdout);
            }
            // Save edited contact details.
            saveContactsToFile(addressBook);
            printf("successfully Edited\n");



            break;


            case 3:
            
            
            do{
                // Reset search results before searching by email.
                flag=1;
                found=0;
                size=0;

                printf("search the Email:");
                scanf(" %29[^\n]",needle);
                getchar();

                // Search contacts using a partial, case-insensitive email match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch=strcasestr(addressBook->contacts[i].email,needle);
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;
                    }
                }
                // Display an error when no email matches.
                if(found==0)
                {
                    printf("%45s\n\n","Email is not found");
                    flag++;
                }

            }while(flag!=1);


            // Display contacts matching the email search.
            if(found)
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);
                }
                printf("\n");
            }

            do{


                flag=1;
                printf("Select the index Number :");
                // Validate that the entered index is numeric.
                if (scanf("%d", &index) != 1)
                {
                    while (getchar() != '\n');
                    printf("Invalid Index.\n\n");
                    flag++;
                    continue;
                    
                }
                getchar();

                // Validate the selected result index.
                if(index>size || index < 1)
                {
                    printf("Invalid Index.\n\n");
                    flag++;
                }



            }while(flag!=1);


            index=index-1;    
            
            int i,dot=0,atdot=0;
            int dotpostion,atpostion;
            do{


                flag=1;
                printf("Enter the Email to Edit :");
                scanf(" %29[^\n]",edit);
                getchar();

                // Check whether the email address ends with ".com".
                char *res=strstr(edit,".com"); 
                if(flag==1 && res==NULL )
                {
                    printf("Invalid domain.\n\n");
                    flag++;
                }
                else if (flag==1 && strcmp (res,".com")!=0)

                {
                    printf("Extra character after '.com'.\n\n");
                    flag++;
                }



                // Validate every character in the email address.
                for(i=0;flag==1 && edit[i]!='\0';i++) 
                {   
                    if(edit[i]=='@')
                    {
                        atdot++;
                        atpostion=i;
                        if((edit[i+1]=='.')) 
                        {
                            printf("Email ID must contain some character between ' @ ' and '.' .\n\n");
                            flag++;
                            break;
                        }
                    } 
                    else if(flag==1 && edit[i]=='.')
                    {
                        dot++;
                        dotpostion=i;
                    }
                    else if((edit[i]>='a' && edit[i]<='z')||(edit[i]>='0' && edit[i]<='9'))
                    {
                        continue;
                    }
                    else if (flag==1 && (edit[i]>='A' && edit[i]<='Z'))
                    {
                        printf("Email contain only lower letters and digits.\n\n");
                        flag++;
                        break;
                    }
                    else
                    {
                        printf("Invalid '%c' Symbol.\n\n",edit[i]);
                        flag++;
                        break;
                    }
                }



                // Validate the number and position of '@' and '.' symbols.
                if(flag==1 && atdot==0)
                {
                    printf("Missing '@' in Email ID.\n\n");
                    flag++;
                }
                else if(flag==1 && atdot!=1)
                {
                    printf("Multiple '@' not allowed in Email ID.\n\n");
                    flag++;
                }
                else if(flag==1 && dot==0)
                {
                    printf("Missing '.' in Email ID.\n\n");
                    flag++;
                }
                else if(flag==1 && dot!=1)
                {
                    printf("Multiple '.' not allowed in Email ID.\n\n");
                    flag++;

                }
                else if(flag==1 && (dotpostion==0 || atpostion==0))
                {
                    printf("Username cannot be empty.\n\n");
                    flag++;
                }
                else if(flag==1 && (dotpostion<atpostion))
                {
                    printf("Dot '.'must appear after the symbol '@'\n\n");
                    flag++;
                }




                // Check whether another contact already uses this email.     
                for(i=0;flag==1 && i<addressBook->contactCount;i++); 
                {
                    if(strcmp(edit,addressBook->contacts[i].email)==0)
                    {
                        printf("Email must be unique.\n\n");
                        flag++;
                        break;

                    }
                }




            }while(flag!=1);




            for(int i=0;i*i<100;i=i+2)
            {
                printf("Loading[");
                for(int dash=0;dash<i;dash++)
                {
                    printf(".");
                }
                printf("]%d%%\r",i);
                sleep(1);
                fflush(stdout);
            }


            // Store the validated edited email address.
            strcpy(addressBook->contacts[position[index]].email,edit);

            // Save edited contact details.
            saveContactsToFile(addressBook);
            printf("successfully Edited\n");

            break;

            case 4:
            // Exit from the editContact function.
            return ;

            default:
            // Display an error for menu choices other than 1 to 4.
            printf("Invalid Option.\n\n");
            
        }

    }while(option!=4);
    
}

/*
...................................................................................................................................................................
Function Name: deleteContact

Description:
This function deletes an existing contact from the address book. The user can
search for a contact by name, mobile number, or email address, select a
matching contact, confirm the deletion, and save the updated contact list.

Validations:
1. The menu option must be a numeric value between 1 and 4.
2. Search results are reset before every new search.
3. A message is shown when no matching contact is found.
4. The selected index must be valid.
5. The user must confirm the deletion.
6. Invalid confirmation options are rejected.
....................................................................................................................................................................
*/

void deleteContact(AddressBook *addressBook)
{
	// Stores the selected menu option, search status, and contact indexes.
    int i,option;
    int found;
    int index;
    int deleteindex;
    char needle[50];
    int choose;
    if(addressBook->contactCount<1)
    {
        printf("No Contacts are avaliable.\n\n");// if no contacts is there it will show no contacts
        return ;
    }

    do
    {

        // Display options for searching the contact to delete.
        printf("\n1.Name\n2.Mobile Number\n3.Email\n4.Exit\n");
        printf("Enter Your option:");

        // Validate that the user enters a numeric menu option.
        if (scanf("%d", &option) != 1)
        {
            while (getchar() != '\n');
            printf("Invalid Option.\n\n");
            flag++;
            continue;
        }
        getchar();

        switch(option)
        {
            case 1:
            do
            {


                flag=1;

                // Reset previous search results before a new search.
                found=0;
                size=0;
                printf("search the name: ");
                scanf(" %49[^\n]",needle);
                getchar();

                // Search every contact for a partial name match. 
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch;
                    ch=strcasestr(addressBook->contacts[i].name,needle);
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;

                    }
                }

                // Display an error when no matching name is found.
                if(found==0)
                {
                
                    printf("%45s\n\n","Name is not found");
                    flag++;
                
                }



            }while(flag!=1);
            

            if(found)
            {
                // Display all contacts matching the name search.
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);    
                }
                printf("\n");
            }



            do
            {

                flag=1;
                printf("Select the index number:");
                // Validate that the selected index is numeric.
                if(scanf("%d",&index)!=1)
                {
                    while(getchar()!='\n');
                    printf("Invalid Options.\n\n");
                    flag++;
                    continue;
                }
                getchar();


                // Check whether the selected index is valid.
                if(index > size || index < 1)
                {
                    printf("Invalid Index.\n\n");
                    flag++;
                }



            }while(flag!=1);

            // Convert the displayed index into the actual contact index
            deleteindex=position[index-1];

            do
            {
                
                printf("Are you sure to delete this number\n");
                printf("press 1------->1.YES\n");
                printf("press 2------->2.NO \n");
                printf("Select your option:");
                if(scanf("%d",&choose)!=1)
                {
                    while(getchar()!='\n');
                    printf("Invalid option.\n\n");
                    flag++;
                    continue;
                }
                switch(choose)
                {
                    case 1:
                    // Shift all later contacts one position to the left.
                    for(i=deleteindex;i<addressBook->contactCount-1;i++)// here deleting the contact by using for loop
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }


                    // Reduce the total number of contacts.
                    addressBook->contactCount--;
                    for(int i=0;i*i<100;i=i+2)
                    {
                        printf("Loading[");
                        for(int dash=0;dash<i;dash++)
                        {
                            printf(".");
                        }
                        printf("]%d%%\r",i);
                        sleep(1);
                        fflush(stdout);
                    }
                    saveContactsToFile(addressBook);
                    printf("successfully Deleted.\n");
                    return;

                    break;

                    case 2:
    
                    // Cancel deletion and exit the function.
                    for(int i=0;i*i<100;i=i+2)
                    {
                        printf("Loading[");
                        for(int dash=0;dash<i;dash++)
                        {
                            printf(".");
                        }
                        printf("]%d%%\r",i);
                        sleep(1);
                        fflush(stdout);
                    }

                    // Save the newly created contact to the file.
                    printf("Deletion cancelled.\n\n");
                    return;

                    default:
                    // Reject invalid confirmation input.
                    printf("Invalid option\n\n");
                    flag++;
                }

            }while(choose!=2);



            
            break;
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            case 2:
            do
            {

                // Reset previous results before searching by mobile number.
                flag=1;
                found=0;
                size=0;
                printf("search the Mobile Number: ");
                scanf(" %[^\n]",needle);
                getchar();

                // Search every contact for a partial phone-number match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch;
                    ch=strcasestr(addressBook->contacts[i].phone,needle);// strcasestr is used to search the details
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;

                    }

                }
                // Display an error when no matching phone number is found.
                if(found==0)
                {
                
                    printf("%45s\n\n","Number is not found");
                    flag++;
                
                }




            }while(flag!=1);

            if(found)
            {
                // Display all contacts matching the phone-number search.
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);    
                }
                printf("\n");
            }



            do
            {
                flag=1;
                printf("Select the index number:");
                // Validate that the selected index is numeric.
                if (scanf("%d", &index) != 1)
                {
                    while (getchar() != '\n');
                    printf("Invalid Index.\n\n");
                    flag++;
                    continue;
                }
                getchar();
                if(index>size || index<1)
                {
                    printf("Invalid Index.\n\n");
                    flag++;
                }


            }while(flag!=1);

            // Convert the displayed index into the actual contact index.
            deleteindex=position[index-1];
            do
            {
                
                // Ask the user to confirm the deletion.
                printf("Are you sure to delete this number\n");
                printf("press 1------->1.YES\n");
                printf("press 2------->2.NO \n");
                printf("Select your option:");
                if(scanf("%d",&choose)!=1)
                {
                    while(getchar()!='\n');
                    printf("Invalid option.\n\n");
                    flag++;
                    continue;
                }
    
                switch(choose)
                {
                    case 1:
                    
                    // Shift all later contacts one position to the left.
                    for(i=deleteindex;i<addressBook->contactCount-1;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }

                    // Reduce the total number of contacts.
                    addressBook->contactCount--;
                    for(int i=0;i*i<100;i=i+2)
                    {
                        printf("Loading[");
                        for(int dash=0;dash<i;dash++)
                        {
                            printf(".");
                        }
                        printf("]%d%%\r",i);
                        sleep(1);
                        fflush(stdout);
                    }

                    saveContactsToFile(addressBook);
                    printf("successfully Deleted\n");
                    return;
                    break;


                    case 2:
                   
                    // Cancel deletion and exit the function.
                    for(int i=0;i*i<100;i=i+2)
                    {
                        printf("Loading[");
                        for(int dash=0;dash<i;dash++)
                        {
                            printf(".");
                        }
                        printf("]%d%%\r",i);
                        sleep(1);
                        fflush(stdout);
                    }

                    // Save the newly created contact to the file.
                    printf("Deletion cancelled.\n\n");
                    return;


                    default:
                    printf("Invalid option.\n\n");
                    

                }
            }while(choose!=2);


            break;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            case 3:
            do
            {


                flag=1;
                found=0;
                size=0;
                printf("search the Email: ");
                scanf(" %49[^\n]",needle);

                // Search every contact for a partial email match.
                for(i=0;i<addressBook->contactCount;i++)
                {
                    char * ch;
                    ch=strcasestr(addressBook->contacts[i].email,needle);
                    if(ch!=NULL)
                    {
                        position[size++]=i;
                        found=1;

                    }
                }
                if(found==0)
                {
                
                    printf("%45s\n\n","Email is not found");
                    flag++;
                
                }


            }while(flag!=1);

            
            if(found)
            {
                // Display all contacts matching the email search.
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); 
                printf("%-8s %-25s %-15s %-35s\n","Index","Name","phone number","Email");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                for(i=0;i<size;i++)
                {
                    printf("%-8d %-25s %-15s %-35s\n",i+1,addressBook->contacts[position[i]].name,addressBook->contacts[position[i]].phone,addressBook->contacts[position[i]].email);    
                }
                printf("\n");
            }




            do
            {


                flag=1;
                printf("Select the index number:");
                // Validate that the selected index is numeric.
                if (scanf("%d", &index) != 1)
                {
                    while (getchar() != '\n');
                    printf("%s\n\n","Invalid Index.");
                    flag++;
                    continue;
                }
                getchar();


                // Check whether the selected index is valid.
                if(index>size || index<1)
                {
                    printf("Invalid Index.\n\n");
                }


            }while(flag!=1);


            // Convert the displayed index into the actual contact index.
            deleteindex=position[index-1];
            do
            {    
                // Ask the user to confirm the deletion.
                printf("Are you sure to delete this number\n");
                printf("press 1------->1.YES\n");
                printf("press 2------->2.NO \n");
                printf("Select your option:");
                if(scanf("%d",&choose)!=1)
                {
                    while(getchar()!='\n');
                    printf("Invalid option.\n\n");
                    flag++;
                    continue;
                }
                

                switch(choose)
                {
                    case 1:
                    
                    // Shift all later contacts one position to the left.
                    for(i=deleteindex;i<addressBook->contactCount-1;i++)
                    {
                        addressBook->contacts[i]=addressBook->contacts[i+1];
                    }
                    
                    addressBook->contactCount--;
                    // here decrementing the conctact count

                    for(int i=0;i*i<100;i=i+2)
                    {
                        printf("Loading[");
                        for(int dash=0;dash<i;dash++)
                        {
                            printf(".");
                        }
                        printf("]%d%%\r",i);
                        sleep(1);
                        fflush(stdout);
                    }
                    saveContactsToFile(addressBook);
                    printf("successfully Deleted\n");
                    return;
                    break;

                    case 2:
                    
                    // Cancel deletion and exit the function.
                    for(int i=0;i*i<100;i=i+2)
                    {
                        printf("Loading[");
                        for(int dash=0;dash<i;dash++)
                        {
                            printf(".");
                        }
                        printf("]%d%%\r",i);
                        sleep(1);
                        fflush(stdout);
                    }

                    // Save the newly created contact to the file.
                    printf("Deletion cancelled.\n");
                    return;

                    default:
                    printf("Invalid option.\n\n");
                    flag++;

                }

            }while(choose!=2);

            break;

            case 4:
            return;

            default :
            printf("Invalid option.\n\n");
            flag++;

            
        }
    }while(option!=4);

}
//.......................................................................................................................................................................................................................................................................
