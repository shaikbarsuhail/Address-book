#include <stdio.h>
#include "file.h"
#include<unistd.h>
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
Function name:
saveContactsToFile

Description:
Saves every contact in an AddressBook to a file named contact.csv in CSV format.
Each row contains the contact’s name, phone number, and email address.
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void saveContactsToFile(AddressBook *addressBook) 
{
  FILE *fptr=fopen("contact.csv","w"); // Open/create CSV file for writing
  if(fptr==NULL)
  {
    fprintf(stderr,"file not found\n");// Report failure to open the file.
    return;// Avoid using an invalid file pointer.
  }
  for(int i=0;i<addressBook->contactCount;i++)
  {
    fprintf(fptr,"%s,%s,%s\n",// Write one contact as a CSV row.
    addressBook->contacts[i].name,
    addressBook->contacts[i].phone,
    addressBook->contacts[i].email);
  }
  fclose(fptr);// Close the file and flush pending output.
  
}
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Function name:
loadContactsFromFile

Description:
Reads contacts from contact.csv and stores them in the given AddressBook.
It also writes existing contacts to the file before reading them back.

fopen:
Opens contact.csv in append-and-read mode ("a+").

fprintf:
Appends each existing contact to the CSV file.

rewind:
Moves the file position back to the beginning before reading.

fscanf:
Reads one CSV row into a contact’s name, phone number, and email fields.

fclose:
Closes the file after processing.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void loadContactsFromFile(AddressBook *addressBook) 
{
  FILE *fptr=fopen("contact.csv","r");// Open file for appending and reading.
  if(fptr==NULL)
  {
    fprintf(stderr,"file not found\n");// Display an error if the file cannot open.
    return;// Stop to avoid using a null file pointer.
  }

 
  
  while((fscanf(fptr,"%[^,],%[^,],%[^\n]\n",
  addressBook->contacts[addressBook->contactCount].name,
  addressBook->contacts[addressBook->contactCount].phone,
  addressBook->contacts[addressBook->contactCount].email))==3)
  {
    addressBook->contactCount++;// Increase the count after loading a contact.
  }
  fclose(fptr); // Close the CSV file.
}
