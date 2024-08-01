#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */

// int day_of_year(int year, int month, int day)
// {
//     int i, leap;
//     leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
//     for (i = 1; i < month; i++)
//         day += daytab[leap][i];
//     return day;
// }

int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    char* p = daytab[leap] + 1; // start from jan
    for(i = 1; i < month; i++, p++)
        day += *p;

    return day;
}

/* month_day: set month, day from day of year */
// void month_day(int year, int yearday, int *pmonth, int *pday)
// {
//     int i, leap;

//     leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
//     for (i = 1; yearday > daytab[leap][i]; i++)
//         yearday -= daytab[leap][i];
//     *pmonth = i;
//     *pday = yearday;
// }

void month_day(int year, int yearday, int *pmonth, int* pday) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    char* p = daytab[leap] + 1;
    // i = 1;
    // while((yearday -= daytab[leap][i++]) > daytab[leap][i])
    //     ;
    while((yearday -= *p++) > *p)
        ;
    
    *pmonth = p - daytab[leap];
    *pday = yearday;
}

int main() {
    int n = day_of_year(2024, 5, 3);
    printf("%d\n", n);
    
    int pm, pd;
    month_day(2024, 124, &pm, &pd);
    printf("%d/%d\n", pd, pm);
}