
/*******************************************************
*display.c
*
* This program stored information of each projects
* and user have to select whether display all or
* display one project and print the project information
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "display.h"
#include "add.h"
#include "displayTask.h"

/*
* Function that change underscore to spacebar
*/
char changeUnder(char string[])
{
	for (int i = 0; i < strlen(string)-1; i++)
		{
		if (string[i] == '_')
			{
			string[i] = ' ';
			}
		}
}

/*
 * Function that print project name ,description and start date
 */
void printProjectND(PROJECT_D* data)
{
  changeUnder(data->name);
	printf("Project name: %s\n",data->name);

	changeUnder(data->description);
	printf("Project Description: %s\n",data->description);

}

/*
 * Function for get the number that user choose
 */
int checkChoiceD(int count)
	{
	char input[128]; 			/*get this from user*/
	int choice = 0, k = 0, valid = 1;	/**/

	while (1)
		{
		valid = 1;
		printf("\nWhich one do you want (max %d)? ",count);
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&choice);
		for (k = 0; k < strlen(input)-1; k++)
			{
			if (!isdigit(input[k]))
				{
				printf("\tPlaese give a number!\n");
				valid = 0;
				break;
				}
			}
		if (valid == 0)
			{
			continue;
			}
		if ((choice == 0) || (choice > count))
			{
			printf("\tPlease give number greater than 0 and less or equal to %d\n",count);
			continue;
			}
		else
			{
			return choice;
			}
		}
	}

/*
 * Function that print all of the similar project name
 * use to choose the project that we want to edit
 */
void chooseN (char input[], int count, NAME_D project[])
	{
	char name[128];								/*project name*/
	int countName = 0, i = 0, choice = 0, j =0;
	int choose = 0, go = 1;
	EDIT_D * similar = NULL;			/*structure of similar project name*/
	char cName[128];							/*name to use another function*/
	char txt[10] = ".txt";

	similar = (EDIT_D*) calloc(count,sizeof(EDIT_D));
	sscanf(input,"%[^\n]",name);
	for (i = 0; i < count ; i++)
		{
		if (strncasecmp(name,project[i].name,strlen(name)) == 0)
			{
			printf("No%d:%s\n",countName+1,project[i].name);
			sscanf(project[i].name,"%[^\n]",similar[countName].name);
			countName++;
			}
		}
	printf("----------------There are %d of %s---------------------\n",countName,name);
	if	(countName == 0)
		{
		go = 0;
		}
	if (go == 1)
		{
		choice = checkChoiceD(countName);
		choice = choice - 1;
		for (j = 0; j < countName; j++)
			{
			if (choice == j)
				{
				sscanf(similar[j].name,"%[^\n]",cName);
				}
			}
		for (i = 0; i < strlen(cName)-1; i++)
			{
			if (isspace(cName[i]))
				{
				cName[i] = '_';
				}
			}
		free(similar);
		strncat(cName,txt,5);
		displayOne(cName);
		}
	}

/*
 * Function use to read the file project name and ask the
 * user for the project
 */
void searchP()
	{
	FILE* opFile = NULL;				/*file project name*/
	char line[28];							/*user input*/
	NAME_D * project = NULL;		/*structure project name*/
	int count = 0;							/*count of project*/
	int i = 0, j = 0;						/*for loop : i for count array of project
																					 j for count array of name   */
	char inputline[128]; /*user input*/

	while (1)
		{
    i = 0;
    count = 0;
		opFile = fopen("projectName.txt","r");
		if (opFile == NULL)
			{
			printf("\tError can't open file project name!\n\n");
			exit(0);
			}
		while (fgets(line,sizeof(line),opFile) != NULL)
			{
			count++;
			}
		project = (NAME_D*) calloc(count,sizeof(NAME_D));
		if (project == NULL)
			{
			printf("Error can't allocate\n");
			exit(10);
			}
		fclose(opFile);
		opFile = fopen("projectName.txt","r");
		if (opFile == NULL)
			{
			printf("\tError can't open file project name!\n\n");
			exit(1);
			}
		while ((fgets(line,sizeof(line),opFile) != NULL) || (i < count))
			{
			sscanf(line,"%s",project[i].name);
			i++;
			}
		for (i = 0; i < count; i++)
			{
			for (j = 0; j < strlen(project[i].name);j++)
				{
				if (project[i].name[j] == '_')
					{
					project[i].name[j] = ' ';
					}
				}
			}
		fclose(opFile);
		printf("\nWhat project do you want to search(Done to exit)? ");
		fgets(inputline,sizeof(inputline),stdin);
		if (strcasecmp(inputline,"done\n") == 0)
			{
			break;
			}
			chooseN(inputline,count,project);
		}
	}

/*
* Function that ask user what project to display
* then print that project information
*/
void displayOne(char projectN[])
{
	FILE* opFile = NULL;						/*Pointer that use for open file*/
	PROJECT_D * projectInfo = NULL;	/*Variable that stored project information*/
	char txt[5] = ".txt";						/*Stored '.txt'*/
	char line[128];									/*Stored line*/

		opFile = fopen(projectN,"r");
		if(opFile == NULL)
		{
			printf("\tError can't open file project name!\n");
			exit(0);
		}

		projectInfo = (PROJECT_D*) calloc(1,sizeof(PROJECT_D));

		fgets(line,sizeof(line),opFile);
		sscanf(line,"%s",projectInfo->name);

		fgets(line,sizeof(line),opFile);
		sscanf(line,"%s",projectInfo->description);

     fgets(line,sizeof(line),opFile);
    sscanf(line,"%s",projectInfo->startDate);

		printf("\n");
		printProjectND(projectInfo);
      
		sortTask(projectN);

		printf("\n");
		free(projectInfo);
		fclose(opFile);
	
}

/*
 * Function that display all the project
 */
void displayAll()
{
	FILE* projectFile = NULL;		/*Open project name testfile*/
	FILE* indiFile = NULL;			/*Open individual project information*/
	PROJECT_D *projectData = NULL;		/*Stored information*/
	char lineName[128];					/*Stored name to open file*/
	char lineInfo[1280];				/*Stored line*/
	char pName[128];						/*Stored project name with .txt*/
	char txt[5]  = ".txt";			/*Stoed '.txt'*/
	char edge[25];							/*Stored 'edge'*/
	int taskCount = 0;					/*Stored count of task*/
	int projectCount = 0;				/*Stored count of project*/

	projectFile = fopen("projectName.txt","r");
	if(projectFile == NULL)
	{
		printf("\tError can't open file project name!\n");
		exit(0);
	}

	while(fgets(lineName,sizeof(lineName),projectFile) != NULL)
	{
		sscanf(lineName,"%s",pName);
		strncat(pName,txt,5);

		indiFile = fopen(pName,"r");
		if(indiFile == NULL)
		{
			printf("\tError can't open file project name!\n");
			exit(0);
		}
    printf("\n====================================\n");
		taskCount = 0;
		projectData = (PROJECT_D*) calloc(1,sizeof(PROJECT_D));

		projectCount++;
		printf("(%d.)\n",projectCount);

		/*Stored project name*/
		fgets(lineInfo,sizeof(lineInfo),indiFile);
		sscanf(lineInfo,"%s",projectData->name);

		/*Stored project description*/
		fgets(lineInfo,sizeof(lineInfo),indiFile);
		sscanf(lineInfo,"%s",projectData->description);

    fgets(lineInfo,sizeof(lineInfo),indiFile);
    sscanf(lineInfo,"%s",projectData->startDate);

		printProjectND(projectData);
		sortTask(pName);
		free(projectData);
	}
	fclose(indiFile);
	fclose(projectFile);
}

/*
* Display menu user will choose whether display all
* or display only one project
*/
void displayMenu()
{
	char userInput[128];		/*User input*/
	int userChoice = -1;		/*Stored user choice*/

	printf("[ Welcome to display section ]\n");

	while(1)
	{
		memset(userInput,0,sizeof(char));
		printf("Display option:\n");
		printf("\t1 - Display all project\n");
		printf("\t2 - Display one project\n");
    printf("\t3 - Done\n");
		printf("Which option? ");
		fgets(userInput,sizeof(userInput),stdin);
		sscanf(userInput,"%d",&userChoice);

		if ((userChoice > 3) || (userChoice < 1))
		{
			printf("Invalid selection - choose 1 or 3\n");
	    	//userChoice = -1;
		}
		else if (strlen(userInput) != 2)
		{
			printf("Invalid selection - input only number\n");
			//userChoice = -1;
		}

    if(userChoice == 1)
  	{
	  	printf("Display all project:\n\n");
	  	displayAll();
  	}
	  else if(userChoice == 2)
	  {
		  searchP();
  	}
    else if(userChoice == 3)
    {
      break;
    }
	}
}
