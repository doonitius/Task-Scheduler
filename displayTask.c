/*******************************************************
*displayTask.c
*
* 555555
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"add.h"
#include"readData.h"
#include"abstractNetwork2.h"
#include"dueDate.h"
#include "display.h"
PROJECT_T * projects = NULL;
char startdate[128];

/*
 * Function that use to print task in order of start time with
 * all their data in the topological way.
 */
int displayTaskDate()
{
  projects = sendProject();
  strcpy(startdate,projects->startDate);
  VERTEX_T * pCurrent = listTopo();
  
  printf("\n>>>  Project start date: %s\n\n",projects->startDate );
  printf("TASK\tDescription\t\t\t\tStart\t\tEnd\n\n" );
  while(pCurrent != NULL)
  {
    if(strcmp(pCurrent->key,"end") == 0)
    {
      break;
    }
    if(strcmp(pCurrent->key,"start") == 0)
    {
      strcpy(pCurrent->startDate,projects->startDate);
      ADJACENT_T * pRef = pCurrent->adjacentHead;
      while(pRef!=NULL)
      {
        VERTEX_T * vtx = (VERTEX_T*) pRef->pVertex;
        strcpy(vtx->startDate,pCurrent->startDate);
        pRef = pRef->next;
      }
    }
    else
    {
      strcpy(pCurrent->endDate,dueDate(pCurrent->startDate,pCurrent->esTime*-1));
      ADJACENT_T * pRef2 = pCurrent->adjacentHead;
      while(pRef2 != NULL)
      {
        VERTEX_T * vtx2 = (VERTEX_T*) pRef2->pVertex;
        strcpy(vtx2->startDate,pCurrent->endDate);
        pRef2 = pRef2->next;
      }
      if(strlen(pCurrent->data) < 4)
      {
        changeUnder(pCurrent->data);
        printf("TASK%s\t%s\t\t\t\t\t\t%s\t%s\n",pCurrent->key,pCurrent->data,pCurrent->startDate,pCurrent->endDate );
      }
      else if(strlen(pCurrent->data) < 8)
      {
        changeUnder(pCurrent->data);
        printf("TASK%s\t%s\t\t\t\t\t%s\t%s\n",pCurrent->key,pCurrent->data,pCurrent->startDate,pCurrent->endDate );
      }
      else if(strlen(pCurrent->data) >= 19)
      {
        changeUnder(pCurrent->data);
        printf("TASK%s\t%s\t\t\t%s\t%s\n",pCurrent->key,pCurrent->data,pCurrent->startDate,pCurrent->endDate );
      }
      else if(strlen(pCurrent->data) >= 16)
      {
        changeUnder(pCurrent->data);
        printf("TASK%s\t%s\t\t\t%s\t%s\n",pCurrent->key,pCurrent->data,pCurrent->startDate,pCurrent->endDate );
      }
      else if(strlen(pCurrent->data) >= 12)
      {
        changeUnder(pCurrent->data);
        printf("TASK%s\t%s\t\t\t\t%s\t%s\n",pCurrent->key,pCurrent->data,pCurrent->startDate,pCurrent->endDate );
      }
      else if(strlen(pCurrent->data) >= 8)
      {
        changeUnder(pCurrent->data);
        printf("TASK%s\t%s\t\t\t\t%s\t%s\n",pCurrent->key,pCurrent->data,pCurrent->startDate,pCurrent->endDate );
      }
      
    }

    pCurrent = pCurrent->next;
  }
}

/*
 * Function to clear ,read ,draw and display graph by 
 * using topological. We add vertex at the start point and at the end point
 */
int sortTask(char * filename)
{
  char start[] = "start";  /*start vertex*/
  char end[] = "end";      /*end vertex*/
  int zero = 0; 
  char  dummy[] = "dummy"; /*description vertex*/
  int due = 0;             /* logestpath */
  clearGraph();
  goAddVertex(start,dummy,zero);
  ReadDataTxt(filename,1);
  goAddVertex(end,dummy,zero);
  startEnd();
  toposort();
  displayTaskDate();
  due = printLongestPath();
  char * enddate = dueDate(startdate,due); /*string to print due date*/
  clearGraph();
  printf("\n>>>  Project end date: %s\n\n",enddate );
  printf("===================================\n\n");
  freeData();
}

#ifdef DEBUG6
int main()
{
  char filename[] = "asdasd.txt";
  char input[128];
  sortTask(filename);

}
#endif
