/*******************************************************
 *add.c
 *
 * Function add project use to add the information of
 * the project and save it in the file of that project name
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
#include "add.h"
#include "abstractNetwork2.h"
#include "abstractQueue.h"
#include "validate.h"
#include "displayTask.h"

/*
*	Function to call function addVertex and
* print the answer if the task is added
*	to the graph or not 
*/
int addTask (char * key, char * data, int weight)
	{
	int bOk = 0; /*check valid */
	int valid = 0; /*value to return valid */

	bOk = addVertex(key,data,weight);
	if (bOk == 1)
		{
		printf("\t\ttask |%s| added\n",key);
		valid = 1;
      	}
	else
		{
		if (bOk < 0)
	      {
	      printf("\t>>> task already exists\n\n");
	      }
	   else
	      {
	      printf("\t>>> Memory allocation error!\n\n");
	      }
		}
	return valid;
	}
/*
 * Function use to ask for add dependency of two task
 * then print that it have been add dependency or not
 */
void getDependency ()
	{
	char input[128];        /*get from user*/
	char keystring1[68];    /*keep key1*/
  char keystring2[68];    /*keep key2*/
	char * key1 = NULL;     /*key1 pointer*/
	char * key2 = NULL;     /*key2 pointer*/
	char response;
	int retval = 0, j = 0;
	int check = 1, bOk = 0;

	while (1)
		{
    memset(keystring1,0,sizeof(keystring1));
    memset(keystring2,0,sizeof(keystring2));
    printf("===================================\n");
		printf("Do you want to add dependency(Y or N)? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%c",&response);
    printf("===================================\n");
		if (strlen(input) != 2)
			{
			printf("\tPlease give only Y or N\n\n");
			continue;
			}
		else if ((response == 'Y') || (response == 'y'))
			{
			printf("\n[ Let's add dependency! ]\n");
			}
		else if ((response == 'N') || (response == 'n'))
			{
			break;
			}
		else
			{
			printf("\tPlease give only Y or N\n\n");
			continue;
			}
		while (1)
			{
			memset(input,0,sizeof(input));
			printf("\nEnter key value for 'From' task: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",keystring1);
			for (j = 0; j < strlen(input)-1; j++)
				{
				if (!isdigit(input[j]))
					{
					check = 0;
					}
				}
			if (check == 0)
				{
				check = 1;
				printf("\tPlease enter only number!\n\n");
				continue;
				}
			break;
			}
		key1 = strdup(keystring1);
		while (1)
			{
			memset(input,0,sizeof(input));
			printf("\nEnter key value for 'To' task: ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",keystring2);
			for (j = 0; j < strlen(input)-1; j++)
				{
				 if (!isdigit(input[j]))
					{
					check = 0;
					}
				}
			if (check == 0)
				{
				 check = 1;
				 printf("\tPlease enter only number!\n\n");
				 continue;
				}
			break;
			}
		key2 = strdup(keystring2);
		if (strcmp(keystring1,keystring2) == 0)
	   	{
	   		printf("\tInput error - 'From' must be different from 'To'!\n\n");
			  continue;
	   	}
		if ((strlen(key1) == 0) || (strlen(key2) == 0))
			{
		  printf("\tInput error - descriptions empty!\n");
			printf("\tPlease enter again!\n\n");
			continue;
		   	}
		else
	   		{
			retval = addEdge(keystring1,keystring2);
			if (retval == 1)
		   		{
		   		printf("\tAdded edge from |%s| to |%s|\n\n",keystring1,keystring2);
				keepEdge(keystring1,keystring2,retval);
		   		}
		   	else if (retval == 0)
		   		{
		   		printf("\t>>> Vertex doesn't exist or memory allocation error!\n");
		   		}
			else if (retval == -1)
				{
				printf("\t>>> Edge from |%s| to |%s| already exists!\n",keystring1,keystring2);
				}
			else
				{
				printf("\tThis dependency cause loop!, remove the dependency!\n");
				while (1)
					{
					bOk = removeEdge(keystring1,keystring2);
					if (bOk == 1)
						{
						printf("\t>>> Removed the dependency\n");
						break;
						}
					}
				}
	   		}   
    }
	free(key1);
  free(key2);
	}
/*
 * Function use to ask user if want to add task or not then
 * get the information of each task. Also call function to print all task
 * and call function to add dependency
 */
void getTask ()
	{
	int check = 1, bOk = 0;
	int j = 0; /* for loop */
	char input[128]; /*get from user*/
	char  keystring[68]; /*keep key of task*/
	char * key = NULL; /*pointer of key */
	char * des = NULL; /* pointer of description*/
	char response;
	int count = 0, weight = -1;

	printf("\n--------Please add task-------\n");
	while(1)
		{
		if (count != 0)
			{
			printf("Do you want to add more task(Y or N)? ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%c",&response);
      printf("===================================\n");    
			if (strlen(input) != 2)
				{
				printf("\tPlease give only Y or N\n");
				continue;
				}
			else if ((response == 'Y') || (response == 'y'))
				{
				printf("\n[ Let's add task! ]\n");
				}
			else if ((response == 'N') || (response == 'n'))
				{
				break;
				}
			else
				{
				printf("\tPlease give only Y or N\n\n");
				continue;
				}
			}
		count++;
		sprintf(keystring,"%d",count);
		key = strdup(keystring);
        memset(input,0,sizeof(input));
		printf("\tEnter description for task%d: ",count);
		fgets(input,sizeof(input),stdin);
		for (j = 0; j < strlen(input)-1; j++)
			{
			if (isspace(input[j]))
				{
				input[j] = '_';
				}
			}
		input[strlen(input) - 1] = '\0';
		des = strdup(input);
        if ((strlen(key) == 0) || (strlen(des) == 0))
			{
		   	printf("\nInput error - descriptions empty!\n");
			printf("\tPlease enter again!\n");
		   	free(key);
		   	free(des);
			count--;
			continue;
		   	}
		while (1)
				{
				printf("\tEnter the estimated time for task%d: ",count);
		   		fgets(input,sizeof(input),stdin);
           if (strcmp(input,"\n") == 0)
            {
            printf("\tPlease input number!\n");
            continue;
            }
				for (j = 0; j < strlen(input)-1; j++)
					{
					if (!isdigit(input[j]))
						{
						check = 0;
            break;
						}
					}
        sscanf(input,"%d",&weight);
        if (weight == 0)
          {
            check = 1;
            break;
          }
				if (check == 0)
					{
					check = 1;
					printf("\t\tPlease enter only number!\n\n");
					continue;
					}
				break;
				}
		bOk = addTask(key,des,weight);
		if (bOk == 0)
			{
			printf("\tPlease add task %d again!\n\n",count);
			count--;
			continue;
			}
     printf("\n===================================\n");    
		}
	free(key);
  free(des);
	printTask();
	getDependency();
	}
/*
 * Function to add description of the project
 */
void addDescription (PROJECT_T * project)
	{
	char input[128]; /*get from user*/
	int i = 0; /*for loop*/

	printf("\nPlease add description: ");
	fgets(input,sizeof(input),stdin);
	for (i = 0; i < strlen(input)-1; i++)
		{
		if (isspace(input[i]))
			{
			input[i] = '_';
			}
		}
	sscanf(input,"%s",project->description);
	}
/*
 * Function main of the add function use to open file
 * project name and file of the project to store the data of
 * the project
 */
void addProject ()
	{
	FILE *pIn = NULL; /* file of project */
	FILE *projectN = NULL; /* file project name*/
	PROJECT_T * project = NULL; /* structure of project */
	char input[128]; /*get from user */
	char startdate[128]; /*store start date of project */
	char projectName[32];
	int i = 0, j = 0; /* for loop */
	int taskCount = 0, count = 0;
	char txt[10] = ".txt"; /* to open  the file name */
	char lineCheck[128]; /* check of project name */

	projectN = fopen("projectName.txt","a+");
	if (projectN == NULL)
		{
		printf("\tError - can't open file project name!\n\n");
		exit(0);
		}
	printf("[ Welcome to add project section ]\n");
	while (1)
		{
		int valid = 1;
		printf("\nPlease add  project name: ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%[^\n]",projectName);
		while (fgets(input,sizeof(input),projectN) != NULL)
			{
			sscanf(input,"%s",lineCheck);
			if (strcasecmp(lineCheck,projectName) == 0)
				{
				printf("\tAlready has this project, please add again!\n\n");
				valid = 0;
				}
			}
		if (valid == 1)
			{
			for (i = 0; i < strlen(projectName)-1; i++)
				{
				if (isspace(projectName[i]))
					{
					projectName[i] = '_';
					}
				}
			sscanf(projectName,"%s",lineCheck);
			break;
			}
		}
	strncat(projectName,txt,5);
	pIn = fopen(projectName,"a");
	if (pIn == NULL)
		{
		printf("\tError - can't open file to add!\n\n");
		exit(1);
		}
	project = (PROJECT_T*) calloc(1,sizeof(PROJECT_T));
	if (project == NULL)
		{
		printf("\tError - can not allocate project\n\n");
		exit(2);
		}
	sscanf(lineCheck,"%s",project->name);
	addDescription(project);
	while(1)
		{
		printf("\nPlease add start date(dd-mm-yyyy): ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%[^\n]",startdate);
		if(validateDateTime(startdate) == 0)
      {
			printf("\tstart date is %s\n",startdate);
			sscanf(startdate,"%[^\n]",project->startDate);
      break;
   	 	}
		}
	getTask();
	fprintf(projectN,"%s\n",project->name);
	fprintf(pIn,"%s\n",project->name);
	fprintf(pIn,"%s\n",project->description);
	fprintf(pIn,"%s\n",project->startDate);
	printtasktofile(pIn);
	printedgetofile(pIn);
	clearGraph();
	free(project);
	fclose(projectN);
	fclose(pIn);
  sortTask(projectName);
	}
