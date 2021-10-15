/*******************************************************
 *main.c
 *
 *	This functionuse to add project, task and dependency
 *	of the project and calculate the shortest way to finish
 *  the project and save the project. Display the project and serach
 *	for project to edit or delete
 *
 *  PM2.5 schedule project
 *  Kullanart 		Sukhongkarattanakul (Lin) 62070503406
 *  Jatnipat 			Chanpaosang (Jade) 	      62070503409
 *  Doonlayatis 	Kitsakulpaisan (Doon)     62070503421
 *  Thanatip 			Lertboonchu (Preem)       62070503425
 *******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractNetwork2.h"
#include "add.h"
#include "display.h"
#include "search.h"
/*
 * Function ask user for the option that he choose
 */
int getMenuOption ()
	{
	char input[32]; 				/*get from user*/
  int option = -1;

	while (option < 0)
		{
		memset(input,0,sizeof(char));
		printf("\nProject schedule options:\n");
       	printf("\t1 - Add project\n");
       	printf("\t2 - Search and edit project\n");
       	printf("\t3 - View project\n");
       	printf("\t4 - Exit\n");
       	printf("Which option? ");
       	fgets(input,sizeof(input),stdin);
       	sscanf(input,"%d",&option);
       	if ((option > 4) || (option < 1))
			{
	   		printf("Invalid selection - choose 1 to 4\n");
	   		option = -1;
	   		}
		else if (strlen(input) != 2)
			{
			printf("Invalid selection - input only number\n");
	   		option = -1;
			}
		}
    printf("\n");
    return option;
	}
/*
 * main function of the schedule project use to call function
 * to add, search and view the project.
 */
int main ()
	{
	char input[128];			 /*get from user */
	int choice = -1;

	printf("\n|||||\tWELCOME TO SCHEDULE PROJECT\t|||||\n");
	choice = getMenuOption();
 	while (choice != 4)
    	{
		switch (choice)
			{
			case 1:
			    {
				addProject();
				break;
			    }
			case 2:
			    {
				searchProject();
				break;
			    }
			case 3:
		    	{
			  displayMenu();
				break;
				}
			default:
				{
				printf("Invalid option - we should never get here!\n");
				}
			}
		choice = getMenuOption();
		}
	}
