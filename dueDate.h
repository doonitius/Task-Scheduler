#ifndef DUEDATE_H
#define DUEDATE_H

/*******************************************************
*dueDate.h
*
* Declarations for the function in duedate.c
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
*******************************************************/

/*
 * Function for count day in month
 */
void nextDay();

/*
 * Function for skip day
 */
void skipDays(int days);

/* schedule due date */
/* arg is date in form dd-mm-yyyy
 * and estimate time
 */
char * dueDate(char startdate[],int estimate);

#endif
