/********************************************************
*search.h
* Declarations for the function in validate.c
*
*  PM2.5 schedule project
*  Kullanart 			Sukhongkarattanakul (Lin) 62070503406
*  Jatnipat 			Chanpaosang (Jade) 	      62070503409
*  Doonlayatis 		Kitsakulpaisan (Doon)     62070503421
*  Thanatip 			Lertboonchu (Preem)       62070503425
********************************************************/
/*
 * check day/month/year function
 */
int checkday(int dd, int mm, int yyyy);

/* 
 * date and time validating function 
 */    
int validateDateTime(char checkDateTime[]);
