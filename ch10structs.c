// entering a newline character is the error
//Chap 10 Structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 20
#define MAXEMPS 3

// Defining a structure //doesn't take up any memory, just declaring what the data type is. This is NOT  a global variable. this is a blueprint.
struct  employee{
	char firstName[NAME_SIZE];
	char lastName[NAME_SIZE];	
	unsigned int age;
	double hourlySalary;	
};

void enterEmployees(struct employee* employeeArr, int maxEmployees);
void displayEmployees(struct employee* employeeArr, int maxEmployees);


int main(void) 
{
	
	//PART 1 declare a struct
   	// declare	 	
	struct employee defaultEmployee;
	puts("\n\nPart 1 declare struct employee defaultEmployee");	
	
	puts("Print after declaration defaultEmployee\n");
	
	//What is stored?
	printf ("Employee's first name: %s\n", defaultEmployee.firstName);
	printf ("Employee's last name: %s\n", defaultEmployee.lastName);
	printf ("Employee's age = %d\n", defaultEmployee.age);
	printf ("Employee's hourly salary = %3.2f\n", defaultEmployee.hourlySalary);

	puts("\nInitialize to default values");
	//initialize
	strncpy (defaultEmployee.firstName, " ", NAME_SIZE);
	strncpy (defaultEmployee.lastName, " ", NAME_SIZE);
	defaultEmployee.age = 0;
	defaultEmployee.hourlySalary = 0;

    puts("\nPrint after intialization of defaultEmployee");

	printf ("Employee's first name: %s\n", defaultEmployee.firstName);
	printf ("Employee's last name: %s\n", defaultEmployee.lastName);
	printf ("Employee's age = %d\n", defaultEmployee.age);
	printf ("Employee's hourly salary = %3.2f\n", defaultEmployee.hourlySalary);
 

	//Part 2
	puts("\n\nPart 2 Declare and Initalize struct employee defaultEmployee = { Joe, Smith, 23, 15}");	
	
	// declare and initialize two employees
    // struct employee xEmployee = {}; //sets aside the bits/bytes for a char, char, unsigned, and double. just sets aside memory when declared
    // struct employee yEmployee = { "Stack ", "Terror", 37, 65.00, "adam" }; // compiler error
    struct employee aEmployee = { "Stack ", "Terror", 37, 65.00 };
    struct employee bEmployee = { "Binary ", "Beasts", 25, 50.00 };
	
	puts("\nPrint after intializing employeea ");
		
	puts("Print after declaration defaultEmployee");
	printf ("aEmployee's first name: %s\n", aEmployee.firstName);
	printf ("aEmployee's last name: %s\n", aEmployee.lastName);
	printf ("aEmployee's age = %d\n", aEmployee.age);
	printf ("aEmployee's hourly salary = %3.2f\n", aEmployee.hourlySalary);
	printf ("sizeof  aEmployee.age = %d\n", sizeof(aEmployee.age));
	
	//compare members
	if (aEmployee.age > bEmployee.age) 
	{
		puts ("aEmployee age is greater than bEmployee age");
	}
	else if (aEmployee.age < bEmployee.age)
	{
		puts ("aEmployee age is less than bEmployee age");	
	}
	else
	{
		puts ("aEmployee age is = bEmployee age");
	}
	
	// memeber assignments
	bEmployee.hourlySalary = aEmployee.hourlySalary;
	printf ("Now bEmployee's hourly salary = %3.2f\n", bEmployee.hourlySalary);
	printf ("&bEmployee.hourlySalary = %p", &bEmployee.hourlySalary);
	
	//Part 3 Pointer to employee struct
	puts("\n\nPart 3 Declare and Initalize employeePtr ");	

	// Intialize employee pointer to aEmployee 
	struct employee *employeePtr = &aEmployee; 	


    // Arrow operators for pointers to structures 
    printf ("EmployeePtr first name -> %s\n", employeePtr->firstName);
	printf ("EmployeePtr last name -> %s\n", employeePtr->lastName);
	printf ("EmployeePtr age -> %d\n", employeePtr->age);
	printf ("EmployeePtr hourly salary -> %3.2f\n", employeePtr->hourlySalary);

	// assign bEmployee address
	puts("\nAssigne employeePtr = &bEmployee and access with (*employeePtr). ");
	employeePtr = &bEmployee;
	// equivalent to arrow operators 
    printf ("(*employeePtr).firstName  %s\n", (*employeePtr).firstName);
	printf ("(*employeePtr).lastName %s\n", (*employeePtr).lastName);
	printf ("(*employeePtr).age %d\n", (*employeePtr).age);
	printf ("(*employeePtr).hourlySalary %3.2f\n", (*employeePtr).hourlySalary);


	//part 4 passing array of structures
	puts("\n\nPart 4 Array of struct employee ");	
	// Intialize array of employees 
	struct employee employees[MAXEMPS];
	enterEmployees(employees, MAXEMPS);

	// create function to display employees
	displayEmployees(employees, MAXEMPS);
	
	
	return 0;
}

void displayEmployees(struct employee  * employeeArr, int max) // can also do employeeArr[] with no *
{

    for (int i = 0; i < max; i++)
    {
        printf("\nEmployee's %d deails\n\n", i + 1);

        printf("%s", "First name\n");
        printf("%s\n", employeeArr[i].firstName);

        printf("%s", "Last name\n");
        printf("%s\n", employeeArr[i].lastName); //its a char array, so it's already an address

        printf("%s", "Enter age\n");
        printf("%u\n", &employeeArr[i].age); //primitive data type, so we need to give it the &

        printf("%s", "Enter Hourly Salary\n");
        printf("%.2lf\n", &employeeArr[i].hourlySalary);

    }

}

// structure overwrites what is there, it DOESN'T update the original copy like array
void enterEmployees(struct employee  * employeeArr, int max) // can also do employeeArr[] with no *
{

	for (int i = 0; i < max; i++)
	{
		printf("\nEnter details of employees %d\n\n", i + 1);

		printf("%s", "Enter first name: ");
		scanf("%s", employeeArr[i].firstName);

		printf("%s", "Enter last name: ");
		scanf("%s", employeeArr[i].lastName); //its a char array, so it's already an address

		printf("%s", "Enter age: ");
		scanf("%i", &employeeArr[i].age); //primitive data type, so we need to give it the &

		printf("%s", "Enter Hourly Salary: ");
		scanf("%lf", &employeeArr[i].hourlySalary);

	}

}



