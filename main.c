//DOCUMENTATION
/*Name: David.P
 * Description: To Implement an Address Book Management System for storing, searching, editing, and deleting contact information. 
 */

#include <stdio.h>
#include <string.h>

// Structure to hold contact details
struct address				
{
    char name[30];       // Store the name of the contact
    char mobile_no[12];  // Store the mobile number of the contact
    char gmail[30];      // Store the email ID of the contact
    char address[30];    // Store the address of the contact
};

// Function declarations
void copying(FILE *, FILE *);
void add_contacts();
void search_details();
void print_details();
void edit_details();
void delete_details();
int valid_mobile_num(char* );
int valid_mail_id(char* );

// Main function
int main() 
{
	char ch = 'y';			// Variable to control the menu loop
	int num;			// Variable to hold user menu choice
	// Display the menu and continue until the user decides to exit
	printf("\n-----------DISPLAY THE MENU---------------\n\n");
	while (ch == 'y' || ch == 'Y')
	{
		printf("1.Add Details\n2.Search Details\n3.Print Details\n4.Edit Details\n5.Delete Details\n6.Exit\nEnter the option : ");
		scanf("%d",&num);
		// Handle user input with a switch statement
		switch(num)
		{
			case 1:
				add_contacts();		//call function to add contacts
				break;
			case 2:
				search_details();	//call function to serach the details
				break;
			case 3:
				print_details();	//call function to print details
				break;
			case 4: edit_details();		//call function to edit details
				break;
			case 5: delete_details();	//call function to dellete details
				break;
			case 6: 
				return 0;		//exit the program
			default:
				printf("Invalid\n");
				break;
		}
		printf("Do you want to continue(Y/N) : ");	// Ask if the user wants to continue
		scanf(" %c",&ch);
	}
}
// Function defintion to add a new contact
void add_contacts()
{
	FILE *fptr = fopen("data.csv","r");		// Open the main data file for reading
	FILE *fptr1 = fopen("temp.csv","w");		// Open a temporary file for writing

	struct address details;				// Declare a variable of struct address to hold contact details

	int count;					// Variable to store the number of contacts
	fscanf(fptr,"%d\n",&count);			// Read the current count of contacts from the file
	count++;					// Increment the count for the new contact
	fprintf(fptr1,"%d\n",count);			// Write the updated count to the temp file
	// Copy existing contacts to the temp file
	for (int i=0;i<count-1;i++)
	{
		fscanf(fptr,"%[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile_no,details.gmail,details.address);
		fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile_no,details.gmail,details.address);
	}
	//Input name
	printf("Enter the name : ");
	scanf(" %[^\n]",details.name);
	
	// Mobile Number Validation
    	char mob[11];					// Temporary variable to hold mobile number input
	label:
    		printf("Enter the mobile number: ");
    		scanf(" %[^\n]", mob);			// Read mobile number input
    	if (valid_mobile_num(mob) == 0)
        	goto label;				// If invalid, prompt again
    	else
    	    strcpy(details.mobile_no, mob);		// If valid, copy to details

    	// Email Validation
    	char mail[50];					// Temporary variable to hold email input
	label1:
    		printf("Enter the email (Note: your email ID should end with @gmail.com): ");
    		scanf(" %[^\n]", mail);
    	if (valid_mail_id(mail) == 0)
       		goto label1;
    	else
        	strcpy(details.gmail, mail);

	//Input address
	printf("Enter the address : ");
        scanf(" %[^\n]",details.address);
	fprintf(fptr1,"%s,%s,%s,%s\n",details.name,details.mobile_no,details.gmail,details.address);
	fclose(fptr);					//close the main data file
	fclose(fptr1);					//close the temp file

	fptr = fopen("data.csv","w");			//reopen file for updating
	fptr1 = fopen("temp.csv","r");

	copying(fptr,fptr1);				//copy contents from temp file back to main file
	fclose(fptr);
	fclose(fptr1);
}

// VALIDATION FUNCTION FOR MOBILE NO AND EMAIL ID
int valid_mobile_num(char* mobile_input)
{
    struct address details;				// Declare a variable to store contact details
    int len = strlen(mobile_input);			// Get the length of the mobile input
    //printf("%d\n",len);
    if (len == 10)					// Check if length is exactly 10
    {
	int i=0;
	while(mobile_input[i] != '\0')			// Loop through each character
	{
		// Check if each character is a digit
        	if (!(mobile_input[i] >= '0' && mobile_input[i] <= '9'))
        	{
            		printf("\nInvalid mobile number! Please enter digits only (0-9).\n");
            		return 0;
        	}
		i++;					// Move to the next character
	}

    FILE *fptr = fopen("data.csv", "r");		// Open the data file for reading
    if (fptr == NULL)
    {
        printf("Error opening file.\n");		// Return if the file couldn't be opened
        return 0;
    }

    int count;						// Variable to hold the count of contacts
    fscanf(fptr, "%d\n", &count);			// Read the count of contacts
    // Check for duplicates
    for (int i = 0; i < count; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
        if (strcmp(details.mobile_no, mobile_input) == 0)	// Compare with existing numbers
        {
            printf("This mobile number already exists in the file. Please try another number.\n");
            return 0;					// Return invalid if duplicate is found
        }
    }
    fclose(fptr);				//close the data file
    }
    else
    {
    	printf("Invalid!! ..Enter 10 digit valid number.\n");	//return invalid if length is not 10
	return 0;
    }
    return 1;
}

// FUNCTION TO VALIDATE EMAIL ID
int valid_mail_id(char* email_input)
{
    struct address details;				// Declare a variable to hold contact details
    char required_suffix[] = "@gmail.com";		// Required email suffix
    int input_len = strlen(email_input);		// Length of user input
    int suffix_len = strlen(required_suffix);		// Length of suffix
	
    // Validate the email format
    if (input_len < suffix_len || strstr(email_input, required_suffix) == NULL || strcmp(email_input + input_len - suffix_len, required_suffix) != 0)
    {
        printf("Invalid email ID! Please enter a valid Gmail address ending with @gmail.com.\n");
        return 0;
    }

    FILE *fptr = fopen("data.csv", "r");		// Open the data file for reading
    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    int count;						// Variable to hold the count of contacts
    fscanf(fptr, "%d\n", &count);			// Read the count of contacts
    for (int i = 0; i < count; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
        if (strcmp(details.gmail, email_input) == 0)	// Compare with existing emails
        {
            printf("This email ID already exists in the file. Please try another email.\n");
            fclose(fptr);				// Close the data file
            return 0;
        }
    }

    fclose(fptr);
    return 1;
}
// FUNCTION TO COPY CONTENTS FROM ONE FILE TO ANOTHER
void copying(FILE *fptr, FILE *fptr1)
{
	char ch;					// Variable to hold characters during copying
	while ((ch = fgetc(fptr1))!= EOF)		// Read from fptr1 until EOF
	{
		fputc(ch,fptr);				// Write each character to fptr
	}
}
// FUNCTION TO SEARCH FOR CONTACT DETAILS
void search_details()
{
        FILE *fptr = fopen("data.csv", "r");		// Open the data file for reading
        if (fptr == NULL)
        {
                printf("Error opening file!\n");
                return;
        }

        char search_name[30];
        printf("Enter the name to get the details : ");
        scanf(" %[^\n]", search_name);

        struct address details;				// Declare a variable to hold contact details
        int count;					// Variable to hold count of contacts
        fscanf(fptr, "%d\n", &count);			// Read the count of contacts

        int found_count = 0;
        
        // First pass: Count matches for the entered name
        for (int i = 0; i < count; i++)
        {
                fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
                if (strcmp(search_name, details.name) == 0)	// Compare names and display contact if found
                {
                        found_count++;
                }
        }
        fclose(fptr);

        // Case: No match found
        if (found_count == 0)
        {
                printf("No details were found with the name %s!\n", search_name);
        }
        // Case: Single match found
        else if (found_count == 1)
        {
                fptr = fopen("data.csv", "r");
                fscanf(fptr, "%d\n", &count);
                for (int i = 0; i < count; i++)
                {
                        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
                        if (strcmp(search_name, details.name) == 0)
                        {
                                printf("Name: %s\nMobile_no: %s\nEmail_id: %s\nAddress: %s\n", details.name, details.mobile_no, details.gmail, details.address);
                                printf("\n========== Contact Found ==========\n\n");
                                break;
                        }
                }
                fclose(fptr);
        }
        // Case: Multiple matches found
        else
        {
                char search_detail[100];
                printf("Multiple contacts found with that name. Please enter the mobile number or email ID for more precise search: ");
                scanf(" %[^\n]", search_detail);

                int exact_match_found = 0;
                fptr = fopen("data.csv", "r");
                fscanf(fptr, "%d\n", &count);
                for (int i = 0; i < count; i++)
                {
                        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
                        if (strcmp(search_name, details.name) == 0 && (strcmp(details.mobile_no, search_detail) == 0 || strcmp(details.gmail, search_detail) == 0))
                        {
                                printf("Name: %s\nMobile_no: %s\nEmail_id: %s\nAddress: %s\n", details.name, details.mobile_no, details.gmail, details.address);
                                printf("\n========== Contact Found ==========\n\n");
                                exact_match_found = 1;
                                break;
                        }
                }
                fclose(fptr);

                if (!exact_match_found)
                {
                        printf("No exact match found for the name and additional detail provided.\n");
                }
        }
}

// FUNCTION TO PRINT ALL CONTACT DETAILS
void print_details()
{
	FILE *fptr = fopen("data.csv","r");
	struct address details;				// Declare a variable to hold contact details
	int count;					// Variable to hold count of contacts
	fscanf(fptr,"%d\n",&count);			// Read the count of contacts
	for (int i=0;i<count;i++)
	{
		fscanf(fptr,"%[^,],%[^,],%[^,],%[^\n]\n",details.name,details.mobile_no,details.gmail,details.address);
		printf("\nContact : %d\n\n",i+1);
		printf("Name: %s\nMobile_no: %s\nEmail_id: %s\nAddress: %s\n",details.name,details.mobile_no,details.gmail,details.address);
	}
	printf("\n==========Details printed sucessfully=========\n\n");
	fclose(fptr);
}

// FUNCTION TO EDIT CONTACT DETAILS
void edit_details()
{
        FILE *fptr = fopen("data.csv","r");
        FILE *fptr1 = fopen("temp.csv","w");
        
        struct address details;				// Declare a variable to hold contact details
        char edit_name[30];
        int found=0, repeat=1, edit_det=0;
        printf("Enter the name to edit details: ");
        scanf(" %[^\n]", edit_name);
        
        int count;
        fscanf(fptr, "%d\n", &count);
        fprintf(fptr1, "%d\n", count);  // Write count to temp file
        
        for (int i = 0; i < count; i++)
        {
                fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
                
                if (strcmp(edit_name, details.name) == 0)			//to check whether it is similar or not.
                {
                        found = 1;
                        printf("%s, %s, %s, %s\n", details.name, details.mobile_no, details.gmail, details.address);
                        
                        char ch;						//temporary varaible to decide which detail you want to edit
                        printf("Do you want to edit this details (Yes(y)/No(n)) : ");
                        scanf(" %c", &ch);
                        if (ch == 'Y' || ch == 'y')
                        {
                                while (repeat)
                                {
                                        int opt;
                                        printf("What do you want to edit? Choose an option:\n");
                                        printf("1. Edit Name\n2. Edit Mobile_no\n3. Edit E-mail\n4. Edit Address\n");
                                        printf("Choose an option: ");
                                        scanf("%d", &opt);
                                        
                                        switch (opt)
                                        {
                                                case 1:
                                                        printf("Enter the Name: ");			//to edit name
                                                        scanf(" %[^\n]", details.name);
                                                        printf("Name edited successfully.\n");
                                                        edit_det = 1;
                                                        break;
                                                case 2:
                                                        printf("Enter the Mobile Number: ");		//to edit mobile number
                                                        scanf(" %[^\n]", details.mobile_no);
                                                        printf("Mobile number edited successfully.\n");
                                                        edit_det = 1;
                                                        break;
                                                case 3:
                                                        printf("Enter the Email id: ");			//to edit email id
                                                        scanf(" %[^\n]", details.gmail);
                                                        printf("Email edited successfully.\n");
                                                        edit_det = 1;
                                                        break;
                                                case 4:
                                                        printf("Enter the Address: ");			//to edit address
                                                        scanf(" %[^\n]", details.address);
                                                        printf("Address edited successfully.\n");
                                                        edit_det = 1;
                                                        break;
                                                default:
                                                        printf("Invalid choice! Please choose a valid option.\n");
                                                        break;
                                        }
                                        
                                        printf("Do you want to edit other details? (Yes(y)/No(n)): ");
                                        scanf(" %c", &ch);
                                        repeat = (ch == 'Y' || ch == 'y') ? 1 : 0;
                                }
                        }
                }
                
                fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile_no, details.gmail, details.address);
        }
        
        fclose(fptr);							//close the fptr and fptr1
        fclose(fptr1);

        if (found == 0)
        {
                printf("Name not found in the main file.\n");
        }
        else if (edit_det == 1)						//if details found, copy them into data file as it is updated
        {
                fptr1 = fopen("temp.csv", "r");
                fptr = fopen("data.csv", "w");
                copying(fptr, fptr1);
                printf("Details edited successfully.\n");
                fclose(fptr1);
                fclose(fptr);
        }
}

//FUNCTION TO DELETE THE DETAILS OF A CONTACT
void delete_details()
{
    FILE *fptr = fopen("data.csv", "r");			//openn the files
    FILE *fptr1 = fopen("temp.csv", "w");

    char del_name[30];						//temporary variable to store and compare the contact
    printf("Enter the name for which you want to delete the details: ");
    scanf(" %[^\n]", del_name);
    struct address details;
    int count;
    fscanf(fptr, "%d\n", &count);
    int found = 0, del = 0;

    // Count occurrences of the name
    for (int i = 0; i < count; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
        if (strcmp(details.name, del_name) == 0)
        {
            found++;
        }
    }
    fclose(fptr);

    if (found == 0)
    {
        printf("No details were found with the name %s.\n", del_name);
        printf("No data was deleted from the main file.\n");
    }
    else if (found == 1)
    {
        fptr = fopen("data.csv", "r");
        fscanf(fptr, "%d\n", &count);
        fprintf(fptr1, "%d\n", count - 1);  // Update count in temp file

        for (int i = 0; i < count; i++)
        {
            fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
            if (strcmp(del_name, details.name) == 0)
            {
                char ch;
                printf("Do you want to delete the details of %s? (yes(y)/No(n)): ", del_name);
                scanf(" %c", &ch);
                if (ch == 'Y' || ch == 'y')
                {
                    del = 1;
                    continue; // Skip writing this record to temp file
                }
            }
            fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile_no, details.gmail, details.address);
        }
        fclose(fptr);
    }
    else // Handle multiple entries with the same name
    {
        char o_name[100];
        printf("There are multiple entries for that name. You can search with other details.\n");
        printf("Search with Gmail / Mobile number: ");
        scanf(" %[^\n]", o_name);
        
        fptr = fopen("data.csv", "r");
        fscanf(fptr, "%d\n", &count);
        fprintf(fptr1, "%d\n", count - 1);  // Update count in temp file

        for (int i = 0; i < count; i++)
        {
            fscanf(fptr, "%[^,],%[^,],%[^,],%[^\n]\n", details.name, details.mobile_no, details.gmail, details.address);
            if (strcmp(details.gmail, o_name) == 0 || strcmp(details.mobile_no, o_name) == 0)
            {
                printf("%s, %s, %s, %s\n", details.name, details.mobile_no, details.gmail, details.address);
                char ch;
                printf("Do you want to delete these details? (yes(y)/No(n)): ");
                scanf(" %c", &ch);
                if (ch == 'Y' || ch == 'y')
                {
                    del = 1;
                    continue; // Skip writing this record to temp file
                }
            }
            fprintf(fptr1, "%s,%s,%s,%s\n", details.name, details.mobile_no, details.gmail, details.address);
        }
        fclose(fptr);
    }
    fclose(fptr1);

    // If any record was deleted, update the main file
    if (del == 1)
    {
        fptr1 = fopen("temp.csv", "r");
        fptr = fopen("data.csv", "w");
        copying(fptr, fptr1); // Copy the remaining records to main file
        printf("Data deleted successfully.\n");
        fclose(fptr1);
        fclose(fptr);
    }
}

