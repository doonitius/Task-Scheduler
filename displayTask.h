#ifndef DISPLAYTASK_H
#define DISPLAYTASK_H
/*******************************************************
*displayTask.h
*
* Declarations for the function in displayTask.c
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/


/*
 * Function that use to print task in order of start time with
 * all their data in the topological way.
 */
int displayTaskDate();

/*
 * Function to clear ,read ,draw and display graph by 
 * using topological. We add vertex at the start point and at the end point
 */
int sortTask(char * filename);

#endif