//Daniel McDonough
//PA1 Calender 1/20/17
#include <stdio.h>
#include <stdlib.h>

int dayoweek; //counts the position of the day in the week (0-6) Sunday = 0
int date = 1; //counts the numerical date
int month=0; //counts the months (0-11) January = 0;
int year; //Counts any positive year

//converts numerical month into a sring
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
//checks if a given year is positive
int posyear(int anum){
	if(anum > 0){
		return 1;//true
	}
	else{
		return 0;//false
	}
}

//checks if a given year is a leap year
int isleap(int anum){
	if((anum % 4 == 0) && (anum % 100 == 0) && (anum % 400 == 0) ){
		return 1;//true
	}
	else if ((anum % 4 == 0) && (anum % 100 == 0) && (anum % 400 != 0) ){
		return 0;//false
	}
	else if ((anum % 4 == 0) && (anum % 100 != 0) && (anum % 400 != 0) ){
		return 1;//true
	}
	else{
		return 0;//false
	}
}

//determines the max date for each month and is leap year dependant
int maxdate(int amonth, int ayear){
	switch(amonth){
	case(0)://January
		return 31;
	break;
	case(1):
		if(amonth == 1  && isleap(ayear)){
			return 29;
		}
		else{
			return 28;
		}
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
//gets the difference of years between the given year and 2000
float getdiffofyears(int ayear){
	//January 1st 2000 is known to be a Saturday
	return 2000-ayear;
}
//Checks how many times 4 goes into a number
float whole4(int anum){
	int count=0;
	int i = anum;
	for(;i>=4;i=i-4){
		count++;
	}
	return count;
}
//checks how many times 100 goes into number
float whole100(int anum){
	int count=0;
	int i = anum;
	for(;i>=100;i=i-100){
		count++;
	}
	return count;
}
//checks how many times 400 goes into a number
float whole400(int anum){
	int i =anum;
	int count=0;
	for(;i>=400;i=i-400){
		count++;
	}
	return count;
}

//calculates the number of days between the the given year and jan 1st 2000
int numberofdaysbetweenyears(int ayear){
	//January 1st 2000 is known to be a Saturday
	if(getdiffofyears(ayear) == 0){
		return 0;
	}
	else if(posyear(getdiffofyears(ayear))){
		//I appologise for the longnames
		//2000 minus given year is positive if given year is less than 2000
		//if given is less than 2000 then the calender doesnt count for the leap year of 2000
		//get the difference number of years, multiply by 365,
		//count the number of years between the two, that are multiples of 4 and 400 and subtract the years
		//that are multiples of 100
		return abs(getdiffofyears(ayear)*365)+(whole4(abs(getdiffofyears(ayear)))-whole100(abs(getdiffofyears(ayear)))+whole400(abs(getdiffofyears(ayear))));
	}
	else{
		//one is added to count for the leap year of 2000
		//abs are added for safety
		return abs(getdiffofyears(ayear)*365)+1+(whole4(abs(getdiffofyears(ayear)))-whole100(abs(getdiffofyears(ayear)))+whole400(abs(getdiffofyears(ayear))));
	}
}

//checks the remainder of the difference of the given year and 2000 and 7 to determine the starting day of the week.
float getstartingday(int ayear){
	//Sunday = 0, Saturday = 6
	if(numberofdaysbetweenyears(ayear)%7 == 0){
		dayoweek = 6;
		return 6;
	}
	else{
		dayoweek = (numberofdaysbetweenyears(ayear)%7)-1;
		return (numberofdaysbetweenyears(ayear)%7)-1;
	}
}


//Prints the standard header for each month
int printmonthhead(int amonth){
	//print month name
	setmonthchar(amonth);
	//two \n for extra spacing
	//print year
	printf(" %d\n\n",year);
	//print day header
	printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
	return 0;
}
//Prints the days in the month up to maxdate posible for the month
int printmonth(int ayear){
	dayoweek = getstartingday(ayear);
	month = 0;
	for(;month<12;month++){
		printmonthhead(month);
		date = 1;
		for(;date<=maxdate(month, ayear);date++){
			//this is just for good looking spacing...
			//set 1st day to be under the corresponding dow
			if(date == 1){
				printf("% *d",(5*dayoweek)+3,date);
			}
			//spacing for numbers under 10
			else if(date<10 && dayoweek==0){
				printf("% *d",3,date);
			}
			else if(date<10){
				printf("% *d",5,date);
			}
			//spacing for numbers over 10
			else if(date>9 && dayoweek==0){
				printf("% *d",3,date);
			}
			else{
				printf("% *d",5,date);
			}
			dayoweek++;
			if(dayoweek>6){
				printf("\n");
				dayoweek=0;
			}
		}
		//two \n for extra spacing
		printf("\n\n");
	}
	return 0;
}
//main function
int main(){
	printf("Please enter year for calender:");
	scanf("%d", &year);
	//check if year is positive
	if(posyear(year)){
		printf("\n***  Calender for %d  ***\n",year);
		printmonth(year);
	}
	else{
		printf("Please enter a positive year");
		main();
	}
	return 0;
}
