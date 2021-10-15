#ifndef ADD_H
#define ADD_H

/*******************************************************
* add.h
* Declarations for the function in add.c
*
*  PM2.5 schedule project
*  Kullanart 		Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 	Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/
typedef struct
	{
	char name[32];           /*name of project */
	char description[128];   /*description of project*/
	char startDate[32];      /*start date of project */
	}PROJECT_T;

  /*
  *	Function to call function addVerttex and
  * print the answer if the task is added
  *	to the graph or not
  */
int addTask (char * key, char * data, int weight);

/*
 * Function use to ask for add dependency of two task
 * then print that it have been add dependency or not
 */
void getDependency ();

/*
 * Function use to ask user if want to add task or not then
 * get the information of each task. Also call function to print all task
 * and call function to add dependency
 */
void getTask ();

/*
 * function to add description of the project
 */
void addDescription (PROJECT_T * project);

/*
 * function to display the date
 */
void displayDate();

/*
 * function main of the add function use to open file
 * project name and file of the project to store the data of
 * the project
 */
void addProject ();

#endif
