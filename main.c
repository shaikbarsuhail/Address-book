#include <stdio.h>
#include "contact.h"
#include<string.h>
#include<unistd.h>


/*
Name: SHAIK BAR SUHAIL 
Batch Number: 26012B
Roll Number: 26012B_119
Starting Date:09-07-2026
Ending Date:29-07-2026

Sample Input: Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

smaple input:

Enter your choice:1
Enter Name: shaik bar suhail
Enter phone number: 6302052597
Enter Email ID: suhail@gmail.com

sample output:
succussfully created.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
sample input for search :

Sample Input: Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice:2

1.Search by name
2.Search by Number
3.Search by Email
4.Exit

sample input search by name : s
sample output :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Index    Name                      phone number    Email                              
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1        Shivani                   9632580147      shivani@gmail.com                  
2        lipstick prathap          6325652565      prathap@gamil.com                  
3        power track shivani       6325214587      powertrackshiv@gmail.com           
4        sohail                    6523578459      sohail@gmail.com                   
5        suhail                    6325254578      shaikbarsuhail@gmail.com  
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
sample input for edit :
1.Name
2.phone number
3.Email
4.Exit

Enter Your option: 1
1.Name
2.phone number
3.Email
4.Exit
Enter Your option:1
search the name:s
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Index    Name                      phone number    Email                              
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1        Shivani                   9632580147      shivani@gmail.com                  
2        lipstick prathap          6325652565      prathap@gamil.com                  
3        power track shivani       6325214587      powertrackshiv@gmail.com           
4        sohail                    6523578459      sohail@gmail.com                   
5        suhail                    6325254578      shaikbarsuhail@gmail.com           

Select the index Number to Edit :2

Enter the name to Edit :sai

Sample Output:

successfully Edited
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
sample input for delete contact :
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 4

1.Name
2.Mobile Number
3.Email
4.Exit
Enter Your option:1
search the name: s
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Index    Name                      phone number    Email                              
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1        Shivani                   9632580147      shivani@gmail.com                  
2        sai                       6325652565      prathap@gamil.com                  
3        power track shivani       6325214587      powertrackshiv@gmail.com           
4        sohail                    6523578459      sohail@gmail.com                   
5        suhail                    6325254578      shaikbarsuhail@gmail.com           

Select the index number:2
Are you sure to delete this number
press 1------->1.YES
press 2------->2.NO 
Select your option:1
sample output :

successfully Deleted.
//------------------------------------------------------------------------------------------------------------------------------------------------------------
sample input for list contacts:


Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit
Enter your choice: 5      

Select sort criteria
1. Sort by name
2. Sort by phone
3. Sort by email
4. Exit
Enter your choice: 2

smaple output for list contacts:

Sorting contacts by the phone number :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Index    Name                      phone number    Email                              
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1        power track shivani       6325214587      powertrackshiv@gmail.com           
2        suhail                    6325254578      shaikbarsuhail@gmail.com           
3        divya                     6325987458      divya@gmail.com                    
4        sohail                    6523578459      sohail@gmail.com                   
5        Yoga                      7896541230      yoga@gmail.com                     
6        Shivani                   9632580147      shivani@gmail.com                  
7        Yogamalini                9632587402      yogamalini@gmail.com 
//-----------------------------------------------------------------------------------------------------------------------------------------------------
*/


int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice)!=1)
        {
            while(getchar()!='\n');
            
            
        }
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                saveAndExit(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
    } while (choice != 6);
    
       return 0;
}
