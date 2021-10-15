 /********************************************************
  *search.c
	*
	* Function that search the project then user choose the
	* option that we can do with that project.When you finish
	* editing the project it will write all the data to it file.
	*
	*  PM2.5 schedule project
	*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
	*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
	*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
	*  Thanatip 			Lertboonchu (Preem)       62070503425
	********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractNetwork2.h"
#include "add.h"
#include "validate.h"
#include "search.h"
#include "displayTask.h"
/*
 * Fuction to write the edited infomation to its file
 * and also write the project name to the file name
 */
void writeFile (PROJECTS_T * project, NAME_T  allProject[], int count)
	{
	int j = 0, i = 0; 			/*use for loop */
	FILE * projectN = NULL; /* file project name */
	FILE * pIn = NULL;			/* file of project we edit*/
	char name[68];					/* name of project */
	char txt[10] = ".txt";

	sscanf(project->name,"%s",name);
	strncat(name,txt,5);
	for (i = 0; i < count; i++)
		{
		for (j = 0; j < strlen(allProject[i].name);j++)
			{
			if (allProject[i].name[j] == ' ')
				{
				allProject[i].name[j] = '_';
				}
			}
		}
	pIn = fopen(name,"w");
	if (pIn == NULL)
		{
		printf("Error can't open file to add!\n");
		exit(6);
		}
	projectN = fopen("projectName.txt","w");
	if (projectN == NULL)
		{
		printf("Error can't open file project name!\n");
		exit(5);
		}
	for (j = 0; j < count ; j++)
		{
		namePro(allProject[j].name);
		}
  printName(projectN);  
	fprintf(pIn,"%s\n",project->name);
	fprintf(pIn,"%s\n",project->description);
  fprintf(pIn,"%s\n",project->startDate);
	printtasktofile(pIn);
	printE(pIn);
	fclose(projectN);
	fclose(pIn);
	}

/*
 * Function for get the number that user choose
 */
int checkChoice (int count)
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
 * Function for add the task and ask the user if them finish
 * add.
 */
void addT ()
	{
	int check = 1, bOk = 0;			/**/
	int j = 0; 									/* for loop*/
	char input[128]; 						/*get from user*/
	char  keystring[68];				/*value of key*/
	char * key = NULL; 					/*pointer of key*/
	char * des = NULL; 					/*pointer of description*/
	char response; 							/**/
	int count = 0, weight = 0;	/**/
	int first = 0; 							/*first time*/

	count = checkTask();
	printf("\n\n\t---------Please add task!--------\n");
	while(1)
		{
		if (first != 0)
			{
			printf("Do you want to add more task(Y or N)? ");
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%c",&response);
      printf("==========================\n");
			if (strlen(input) != 2)
				{
				printf("\tPlease give only Y or N\n\n");
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
		printf("\nEnter description for task%d: ",count);
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
		   	printf("\tInput error - descriptions empty!\n\n");
			printf("\tPlease enter again!\n\n");
		   	free(key);
		   	free(des);
			count--;
			continue;
		   	}
		while (1)
				{
				printf("\nEnter the estimated time for task%d: ",count);
		   		fgets(input,sizeof(input),stdin);
		   		sscanf(input,"%d",&weight);
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
		bOk = addTask(key,des,weight);
		if (bOk == 0)
			{
			printf("\tPlease add task %d again!\n\n",count);
			count--;
			continue;
			}
		first = 1;
		}
	free(key);
   	free(des);
	printTask();
	}

/*
 * Function use to ask user for project name that you want to
 * change.
 */
void editName (PROJECTS_T * project, NAME_T  allProject[], int count)
	{
	char input[128]; 	/*get from user */
	int  j = 0, choose = -1;	/**/

	for (j = 0; j < count ; j++)
		{
		if (strncasecmp(project->name,allProject[j].name,strlen(project->name)) == 0)
			{
			choose = j;
			}
		}
	printf("\nEnter project name to edit: ");
	fgets(input,sizeof(input),stdin);
	for (j = 0; j < strlen(input)-1; j++)
		{
		if (isspace(input[j]))
			{
			input[j] = '_';
			}
		}
	sscanf(input,"%s",allProject[choose].name);
	sscanf(input,"%s",project->name);
	}

/*
 * Function to get for the decription of the project
 * that we want to edit.
 */
void editDes (PROJECTS_T * project)
	{
	char input[128];		/**/
	int  j = 0;					/**/

	printf("\nEnter project description to edit: ");
	fgets(input,sizeof(input),stdin);
	for (j = 0; j < strlen(input)-1; j++)
		{
		if (isspace(input[j]))
			{
			input[j] = '_';
			}
		}
	sscanf(input,"%s",project->description);
	}

/*
 * Function ask user for start date of the project.
 */
void editDate (PROJECTS_T * project)
  {
  char input[128]; 					/* get from user*/
	int  j = 0, choose = -1;	/**/
  char startDate[128]; 			/* store start date*/

  while(1)
    {
    printf("\nplease add start date(dd-mm-yyyy) :");
    fgets(input,sizeof(input),stdin);
    sscanf(input,"%[^\n]",startDate);
    if(validateDateTime(startDate) == 0)
        {
        printf("\tstart date is %s\n",startDate);
        sscanf(startDate,"%[^\n]",project->startDate);
        break;
        }
    }
  }

/*
 * Function for edit the description of task that we choose
 * and print info of that task when we finish.
 */
void eTaskDes (VERTEX_T * choose)
	{
	char input[128];		/*get for user*/
	int  j = 0;					/*for loop*/

	printf("\nEnter task description to edit: ");
	fgets(input,sizeof(input),stdin);
	for (j = 0; j < strlen(input)-1; j++)
		{
		if (isspace(input[j]))
			{
			input[j] = '_';
			}
		}
	sscanf(input,"%s",choose->data);
	printf("\tTask key |%s| - description |%s| - estimatedtime |%d|\n",choose->key,choose->data,choose->esTime);
	}
/*
 * Function to edit estimate time of the task that we
 * choose then print all data when we finish.
 */
void eTaskTime (VERTEX_T * choose)
	{
	char input[128]; /*get from user*/
	int  j = 0;  		 /*use for loop*/
	int weight = -1, check = 1;
	ADJACENT_T * current = choose->adjacentHead;

	while (1)
		{
		printf("\nEnter the estimated time to edit: ");
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
		if (check == 0)
			{
			check = 1;
			printf("\tPlease enter only number!\n\n");
			continue;
			}
		break;
		}
	choose->esTime = weight;
	while (current != NULL)
		{
		current->duration = weight;
		current = current->next;
		}
	printf("Task key |%s| - description |%s| - estimatedtime |%d|\n",choose->key,choose->data,choose->esTime);
	}

/*
 * Function display the option that we can do with
 * task taht we choose.
 */
void editTask (VERTEX_T * choose)
	{
	int choice = 0;

	while (1)
		{
		printf("\nList you can edit\n");
		printf("\t1. - edit description task\n");
		printf("\t2. - edit estimate time\n");
		printf("\t3. - delete task\n");
		printf("\t4. - done\n");
		choice = checkChoice(4);
		if (choice == 1)
			{
			eTaskDes(choose);
			}
		else if (choice == 2)
			{
			eTaskTime(choose);
			}
		else if (choice == 3)
			{
			removeVertex(choose->key);
			changeKey();
      printf("\tdelete success!!!\n");
			break;
			}
		else
			{
			break;
			}
		}
	}

/*
 * Function use to find the task that we choose then call
 * edit task function.
 */
void chooseTask (PROJECTS_T * project)
	{
	char input[128];						/*fet from user*/
	int choose = 0, k = 0;
	int valid = 1;							/*check valid number*/
	VERTEX_T * chooseTask = NULL;		/*choose task*/
	VERTEX_T * pDummy = NULL;		/*dummy task*/
	char keystring[68];					/*value of key*/

	while(1)
		{
		printf("\n");
		printTask();
	  printf("\nWhich task do you want? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&choose);
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
		sprintf(keystring,"%d",choose);
		chooseTask = findVertexByKey(keystring,&pDummy);
		if (chooseTask == NULL)
			{
			printf(">>>Does not have this task input again!\n");
			continue;
			}
		else
			{
			editTask(chooseTask);
			break;
			}
		}

  	}

/*
 * Function to delete the dependency of the project then print
 * the result if success or not
 */
void delDepen ()
	{
	char input[128];				/*user input*/
	char keystring1[68];		/*value task1*/
  char keystring2[68];		/*value task2*/
	char * key1 = NULL;			/*pointer task1*/
	char * key2 = NULL;			/*pointer task2*/
	char response;
	int retval = 0, j = 0;
	int check = 1, bOk = 0;

	while (1)
		{
		printf("Do you want to delete dependency(Y or N)? ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%c",&response);
		if (strlen(input) != 2)
			{
			printf("\tPlease give only Y or N\n\n");
			continue;
			}
		else if ((response == 'Y') || (response == 'y'))
			{
			printf("\n[ Let's delete dependency! ]\n");
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
			retval = removeEdge(keystring1,keystring2);
			if (retval == 1)
		   		{
		   		printf("remove dependency from |%s| to |%s|\n",keystring1,keystring2);
		   		}
		   	else if (retval == 0)
		   		{
		   		printf("\t>>> Vertex doesn't exist or dependency does not exist!\n");
		   		}
	   		}
		}
	free(key1);
  free(key2);
	}

/*
 * Function that delete the project and write the project
 * name to the file
 */
void deletePro (PROJECTS_T * project, NAME_T  allProject[], int count)
	{
	int i = 0, j = 0;				/*for loop chance ' ' to '_' */
	char name[68];					/*name of project*/
	char txt[10] = ".txt";
	FILE * pName = NULL;		/*file project name*/

	pName = fopen("projectName.txt","w");
	if (pName == NULL)
		{
		printf("\tError can't open file to write!\n\n");
		exit(4);
		}
	for (i = 0; i < count; i++)
		{
		for (j = 0; j < strlen(allProject[i].name);j++)
			{
			if (allProject[i].name[j] == ' ')
				{
				allProject[i].name[j] = '_';
				}
			}
		}
	for (j = 0; j < count ; j++)
		{
		if (strncasecmp(project->name,allProject[j].name,strlen(project->name)) != 0)
			{
			namePro(allProject[j].name);
			}
		}
	sscanf(project->name,"%s",name);
	strncat(name,txt,5);
	printName(pName);
	remove(name);
	free(allProject);
	fclose(pName);
  clearGraph();
	free(project);
	}

/*
 * Function print the option that we can edit and call the function
 * that use to edit what we choose
 */
void editWhat (PROJECTS_T * project, NAME_T  allProject[], int count)
	{
	int choice = 0;
  char name[128];
  char txt[10] = ".txt";

	while (1)
		{
		printf("\nList you can do\n");
    printf("\tNo1: edit project Name\n");
		printf("\tNo2: edit project description\n");
		printf("\tNo3: edit start date\n");
		printf("\tNo4: delete project\n");
		printf("\tNo5: add task\n");
		printf("\tNo6: edit task\n");
		printf("\tNo7: add dependency\n");
		printf("\tNo8: delete dependency\n");
		printf("\tNo9: done\n");
		choice = checkChoice(9);
		if (choice == 1)
			{
			editName(project,allProject,count);
			}
		else if (choice == 2)
			{
			editDes(project);
			}
    	else if (choice == 3)
			{
			editDate(project);
			}
    	else if (choice == 4)
			{
			deletePro(project,allProject,count);
			break;
			}
		else if (choice == 5)
			{
			addT();
			}
    	else if (choice == 6)
		  	{
			chooseTask(project);
			}
		else if (choice == 7)
			{
			getDependency();
			eDepen();
			}
		else if (choice == 8)
			{
			delDepen();
			eDepen();
			}
		else
			{
			writeFile(project,allProject,count);
			clearGraph();
      sscanf(project->name,"%s",name);
	  	free(allProject);
			free(project);
      strcat(name,txt);
      sortTask(name);
			break;
			}
		}
	}

/*
 * Function that use to get the task and dependency then use
 * to create agraph.
 */
void command(char * input)
	{
	char keystring[64] = "";		/*value of task1*/
	char keystring2[64] = "";		/*value of task2*/
	char descrip[128] = "";			/*description of task*/
	int esTime = 0;							/*estimatetime of task*/
	char * key = NULL;					/*pointer of task*/
	char * des = NULL;					/*pointer of description*/
	int retval = 0;							/*check valid*/
	int bOk = 0, check = 0;

	memset(keystring,0,sizeof(keystring));
  memset(descrip,0,sizeof(descrip));
	if (strncmp(input,"TASK",strlen("TASK")) == 0)
   		{
			sscanf(input,"TASK %s %s %d",keystring,descrip,&esTime);
	 		if (strlen(keystring) == 0)
			{
			printf("\tError: Missing key - |%s|\n\n",input);
			}
	else
	 		{
      key = strdup(keystring);
      des = strdup(descrip);
			retval = addVertex(key,des,esTime);
			if (retval == 1)
				{
				printf("Task key |%s| - description |%s| - estimatedtime |%d|\n",key,des,esTime);
			  }
			else if (retval < 0)
	      		{
	      		printf("\t>>> task already exists\n\n");
	      		}
	   		else
	      		{
	      		printf("\t>>> Memory allocation error!\n\n");
	      		}
			free(key);
	    free(des);
			}
		}
	else if (strncmp(input,"EDGE",strlen("EDGE")) == 0)
		{
		sscanf(input,"EDGE %s %s",keystring,keystring2);
		if ((strlen(keystring) == 0) || (strlen(keystring2) == 0))
			{
			printf("\tError: At least one key missing in edge command - |%s|\n\n",input);
			}
		else if (strcmp(keystring,keystring2) == 0)
			{
			printf("\tError: 'From' and 'To' vertices are the same - |%s|\n\n",input);
			}
		else
			{
			retval = addEdge(keystring,keystring2);
			if (retval == -1)
				{
			 	printf("\tError: Edge from |%s| to |%s| already exists - |%s|\n\n",keystring,keystring2,input);
			 	}
			else if (retval == 0)
			 	{
			 	printf("\tError: At least one vertex doesn't exist or memory allocation error - |%s|\n\n", input);
			 	}
			else if (retval == 2)
				{
				printf("\tThis dependency cause loop!, remove the dependency!\n\n");
				while (1)
					{
					bOk = removeEdge(keystring,keystring2);
					if (bOk == 1)
						{
						printf("\t>>> Removed the dependency\n");
						break;
						}
					}
				}
			}
		}
	else
		{
       	fprintf(stderr,"\tIncorrect command found in file - ignoring -");
       	fprintf(stderr," |%s|\n\n",input);
       	}
	}

/*
 * Function open file that we want to get information
 * and stored it to variable
 */
void getData (char * name, NAME_T allProject[], int count)
	{
	char input[128];				/*input of each line in file*/
	FILE * pEdit = NULL;		/*file of edit project*/
	PROJECTS_T * project = NULL;	/**/
	int i = 0;							/*for loop read each line in file*/

	pEdit = fopen(name,"r");
	if (pEdit == NULL)
		{
		printf("\tError can't open file project name!\n\n");
		exit(2);
		}
	project = (PROJECTS_T*) calloc(1,sizeof(PROJECTS_T));
	if (project == NULL)
		{
		printf("\tError can not allocate project\n\n");
		exit(3);
		}
	while (fgets(input,sizeof(input),pEdit) != NULL)
		{
		if (i == 0)
			{
			sscanf(input,"%s",project->name);
			printf("Name: %s\n",project->name);
			}
		else if (i == 1)
			{
			sscanf(input,"%s",project->description);
			printf("Description: %s\n",project->description);
			}
    else if (i == 2)
      {
      sscanf(input,"%s",project->startDate);
			printf("Start date: %s\n",project->startDate);
      }
		else
			{
			command(input);
			}
		i++;
		}
	fclose(pEdit);
	remove(name);
	editWhat(project,allProject,count);
	}

/*
 * Function that print all of the similar project name
 * use to choose the project that we want to edit
 */
void chooseName (char input[], int count, NAME_T project[])
	{
	char name[128];								/*project name*/
	int countName = 0, i = 0, choice = 0, j =0;
	int choose = 0, go = 1;
	EDIT_T * similar = NULL;			/*structure of similar project name*/
	char cName[128];							/*name to use another function*/
	char txt[10] = ".txt";

	similar = (EDIT_T*) calloc(count,sizeof(EDIT_T));
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
		choice = checkChoice(countName);
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
		getData(cName,project,count);
		}
	}

/*
 * Function use to read the file project name and ask the
 * user for the project
 */
void searchProject ()
	{
	FILE* opFile = NULL;				/*file project name*/
	char line[28];							/*user input*/
	NAME_T * project = NULL;		/*structure project name*/
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
		project = (NAME_T*) calloc(count,sizeof(NAME_T));
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
			chooseName(inputline,count,project);
		}
	}
