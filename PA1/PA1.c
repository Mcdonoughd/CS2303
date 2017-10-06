//PA1.c Calendar by Daniel McDough 8/28/17

#include <stdio.h>
#include <stdlib.h>

int year; //the year
int month; //the month 0 = january
int dow; //day of the week
int date; //the date
int dpy; //days per year
int diff; //difference

/**
 *check if given year is a leap year
 * @param anum
 * @return
 */

int isleap(int anum){
	//if divisible by 4 then true
	if(anum%4 == 0 && anum%100 !=0 && anum% 400!=0){
		return 1;
	}
	//if divisible by 4 and 100 then false
	else if (anum%4 == 0 && anum%100 ==0 && anum%400!=0){
		return 0;
	}
	//if divisible by 4, 100, and 400 then true
	else if (anum%4 == 0 && anum%100 ==0 && anum% 400==0){
		return 1;
	}
	//else = false
	else{
		return 0;
	}
}

/**
 * set month values 0 = January
 * @param amonth
 */
void setmonthchar(int amonth){
	switch(amonth){
	case(0)://January
						printf("January");
	break;
	case(1):
						printf("February");
	break;
	case(2):
						printf("March");
	break;
	case(3):
						printf("April");
	break;
	case(4):
						printf("May");
	break;
	case(5):
						printf("June");
	break;
	case(6):
						printf("July");
	break;
	case(7):
						printf("August");
	break;
	case(8):
						printf("September");
	break;
	case(9):
						printf("October");
	break;
	case(10):
						printf("November");
	break;
	case(11):
						printf("December");
	break;
	default:
		break;
	}
}

/**
 * set maximum date for corresponding month
 * @param amonth
 * @param ayear
 * @return
 */
int maxdate(int amonth, int ayear){
	switch(amonth){
	case(0)://January
						return 31;
	break;
	case(1):
						return 28+isleap(ayear);
	break;
	case(2):
						return 31;
	break;
	case(3):
						return 30;
	break;
	case(4):
						return 31;
	break;
	case(5):
						return 30;
	break;
	case(6):
	case(7):
	return 31;
	break;
	case(8):
						return 30;
	break;
	case(9):
						return 31;
	break;
	case(10):
						return 30;
	break;
	case(11):
						return 31;
	break;
	default:
		return 0;
		break;
	}
}

//
/**
 * check if given number is positive
 * @param anum
 * @return
 */
int checkpos(int anum){
	if(anum > 0){
		return 1;
	}
	else if(anum==0){
		return 0;
	}
	else return 0;
}


/**
 * get the starting day of the year
 */
void getstartday(){
	//if days per year is divisible by 7 then the year starts on a Saturday
	if(dpy%7 == 0){
		dow = 6;
	}
	else{
		//if year is less than 2000 add 3 from dpy then mod 7 and subract 1
		if(checkpos(diff)){
			dow = (dpy+3)%7-1;
		}
		//if year is greater than 2000 subrtact 3 from dpy then mod 7 and subtract 1
		else{
			dow = (dpy-3)%7-1;
		}
	}
}



/**
 * to get days per year
 * @param anum
 * @return
 */
int getdpy(int anum){
	//get the difference of input year and 2000
	diff = 2000 - anum;
	//get absolute value of it
	int k = abs(diff);
	//add leap year for 2000 + # of days per year * number of leap days mod 4 -  number of leap days mod 100 + number of leap days mod 400
	dpy = checkpos(diff)+(k*365)+(k%4)-(k%100)+(k%400);
	//calc starting day
	getstartday();
	return 0;
}

/**
 * print the standard month head
 * @param amonth
 * @return
 */
int printmonthhead(int amonth){
	//print month name
	setmonthchar(amonth);
	//print year
	printf(" %d\n\n",year);
	//print day header
	printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
	return 0;
}

//
/**
 * print the days
 * @param ayear
 * @return
 */
int printmonth(int ayear){
	//calendar has not been printed yet
	for(month=0;month<12;month++){
		//print the header of the current month in loop
		printmonthhead(month);
		//dates have not been printed yet for current month
		for(date=1;date<=maxdate(month, ayear);date++){

			//reset days of week if last dow was Saturday
			if(dow > 6){
				printf("\n");
				dow=0;
			}
			//this is just for good looking spacing...
			//set 1st day to be under the corresponding dow
			if(date == 1){
				printf("% *d",(5*dow)+3,date);
			}
			//spacing for numbers under 10
			else if(date<10 && dow==0){
				printf("% *d",3,date);
			}
			else if(date<10){
				printf("% *d",5,date);
			}
			//spacing for numbers over 10
			else if(date>9 && dow==0){
				printf("% *d",3,date);
			}
			else{
				printf("% *d",5,date);
			}
			//set to next day of week
			dow++;
		}
		//two \n for extra spacing
		printf("\n\n");
	}
	//finish printing calendar
	return 0;
}
/**
 * Run program
 * @return
 */
int main(void){
	printf("Please give a year for the calendar:");
	scanf("%d",&year);
	//check if input is a positive year (or a year at all)
	if (checkpos(year)){
		printf("***\tCalendar for Year %d\t*** \n\n", year);
		//calc days per year
		getdpy(year);
		//print the month out
		printmonth(year);
		return 0;
	}
	//if non valid year is given
	else{
		printf("Please give valid year. \n");

		return 1;
	}
}
