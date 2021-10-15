/*******************************************************
*display.h
*
* Declarations for the function in display.c
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/
typedef struct
	{
	char name[32];
	} NAME_D;

typedef struct
	{
	char name[32];
	} EDIT_D;

typedef struct
	{
	char name[32];           /*name of project */
	char description[128];   /*description of project*/
	char startDate[32];      /*start date of project */
	}PROJECT_D;

/*
* Function that change underscore to spacebar
*/
char changeUnder(char string[]);

/*
* Function that print project name ,description and start date
*/
void printProjectND(PROJECT_D* data);

/*
 * Function that check the choice of user input in search
 */
int checkChoiceD(int count);

/*
 * Function that print all of the similar project name
 * and choose the project that we want 
 */
void chooseN(char input[], int count, NAME_D project[]);

/*
 * Function that read the text file  of project name 
 * and ask the user for the project
 */
void searchP();

/*
* Function that ask user what project to display
* then print that project information
*/
void displayOne();

/*
* Function that display all the project
*/
void displayAll();

/*
* Display menu user will choose whether display all
* or display only one project
*/
void displayMenu();
