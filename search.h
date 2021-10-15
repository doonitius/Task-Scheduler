#ifndef SEARCH_H
#define SEARCH_H
/********************************************************
*search.h
* Declarations for the function in search.c
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
********************************************************/
typedef struct
	{
	char name[32];
	} NAME_T;
  
typedef struct
	{
	char name[32];
	} EDIT_T;

typedef struct
	{
	char name[32];
	char description[128];
	char startDate[32];
	}PROJECTS_T;

/*
 * Fuction to write the edited infomation to its file
 * and also write the project name to the file name
 */
void writeFile (PROJECTS_T * project, NAME_T  allProject[], int count);

/*
 * Function for get the number that user choose
 */
int checkChoice (int count);

/*
 * Function for add the task and ask the user if them finish
 * add.
 */
void addT();

/*
 * Function use to ask user for project name that you want to
 * change.
 */
void editName (PROJECTS_T * project, NAME_T  allProject[], int count);

/*
 * Function to get for the decription of the project
 * that we want to edit.
 */
void editDes (PROJECTS_T * project);

/*
 * Function ask user for start date of the project.
 */
void editDate (PROJECTS_T * project);

/*
 * Function for edit the description of task that we choose
 * and print info of that task when we finish.
 */
void eTaskDes (VERTEX_T * choose);

/*
 * Function to edit estimate time of the task that we
 * choose then print all data when we finish.
 */
void eTaskTime (VERTEX_T * choose);

/*
 * Function display the option that we can do with
 * task taht we choose.
 */
void editTask (VERTEX_T * choose);

/*
 * Function use to find the task that we choose then call
 * edit task function.
 */
void chooseTask (PROJECTS_T * project);

/*
 * Function to delete the dependency of the project then print
 * the result of if success or not
 */
void delDepen ();

/*
 * Function that delete the project and write the project
 * name to the file
 */
void deletePro (PROJECTS_T * project, NAME_T  allProject[], int count);

/*
 * Function print the option that we can edit and call the function
 * that use to edit what we choose
 */
void editWhat (PROJECTS_T * project, NAME_T  allProject[], int count);

/*
 * Function that use to get the task and dependency then use
 * to create agraph.
 */
void command(char * input);

/*
 * Function open file that we want to get information
 * and stored it to variable
 */
void getData (char * name, NAME_T  allProject[], int count);

/*
 * Function that print all of the similar project name
 * use to choose the project that we want to edit
 */
void chooseName (char input[], int count, NAME_T project[]);

/*
 * Function use to read the file project name and ask the
 * user for the project
 */
void searchProject ();

#endif
