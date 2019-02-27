#include "date.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct date{ //the date structure which is just three integers
  int day, month, year;
}Date;

//date_create will return a pointer to a date structure
Date *date_create(char *datestr){
  Date *date = (Date *)malloc(sizeof(Date));
  if (date) {
    sscanf(datestr,"%d/%d/%d\n", &date->day, &date->month, &date->year);
  }
  return date;
}

//date_duplicate returns a pointer to a date structure with the same values (not the same object)
Date *date_duplicate(Date *d){
  Date *copy = (Date *)malloc(sizeof(Date));
  if (copy) {
    copy->day = d->day;
    copy->month = d->month;
    copy->year = d->year;
  }
  return copy;
}

int date_compare(Date *date1,Date *date2){ //assuming date1 is what we're finding out and date2 is the basis of comparison
  if (date1->year<date2->year) {
    return -1;
    /* code */
  }else if(date1->year>date2->year){
    return 1;
  }else{
    if(date1->month<date2->month){
      return -1;
    }else if(date1->month>date2->month){
      return 1;
    }else if(date1->day<date2->day){
      return -1;
    }else if(date1->day>date2->day){
      return 1;
    }else{
      return 0;
    }
  }
}

void date_destroy(Date *date){
    if(date) // if date is not NULL
      free(date);
}
