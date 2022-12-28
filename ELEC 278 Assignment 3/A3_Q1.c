// Robb, Ashley 20203465
// ELEC 278 Assignment 3 Question 1

#include <stdio.h>

struct date
{
    // creating structure for date
    int dd; // day
    int mm; // month
    int yyyy; // year
};

// function for printing all the dates
void print_arr(int size, struct date date_arr[]) {
    for (int i = 0; i < size-1; ++i) {
        printf("{%d,%d,%d},  ", date_arr[i].dd, date_arr[i].mm, date_arr[i].yyyy);
    }
    printf("{%d,%d,%d}}  ", date_arr[size-1].dd, date_arr[size-1].mm, date_arr[size-1].yyyy);
}

// function to pivot elements
void pivot(struct date* date1, struct date* date2) {
    struct date temp = *date1;
    *date1 = *date2;
    *date2 = temp;
}

// finding position of partition
int partition_pos(struct date date_arr[], int big, int small) {
    struct date a = date_arr[big]; // assigning element to pivot
    int point = (small - 1);

    for (int i = small; i < big; i++) { // traverse the array comparing to pivot
        if (date_arr[i].yyyy< a.yyyy){
            // swap when year smaller than pivot year
            point = point +1;
            pivot(&date_arr[point], &date_arr[i]);
        }
        else if (date_arr[i].mm < a.mm && date_arr[i].yyyy == a.yyyy) {
            //if year is same, swap when month smaller than pivot month
            point = point +1;
            pivot(&date_arr[point], &date_arr[i]);
        }
        else if (date_arr[i].dd < a.dd && date_arr[i].mm == a.mm && date_arr[i].yyyy == a.yyyy) {
            // if month and year same, swap when day smaller than pivot day
            point = point +1;
            pivot(&date_arr[point], &date_arr[i]);
        }
    }
    // final pivot
    point = point +1;
    pivot(&date_arr[point], &date_arr[big]);
    return (point);
}

// defining the date sort recursive function
void DateSort(struct date* date_arr[], int small, int big) {
    if (small < big) {
        int pos = partition_pos(date_arr, big, small);// finding data with small data on left and big on right
        DateSort(date_arr, small, pos - 1);// big data recursion
        DateSort(date_arr, pos + 1, big); // small data recursion
    }
}

// main function
int main() {
    printf("ROBB ASHLEY\nELEC 278 FALL 22\nASSIGNMENT 3: QUESTION 2\n\n");
    struct date inputs[] = { // defining array for inputted dates
            // inout dates
            {20, 1, 2014},
            {25, 3, 2010},
            {3, 12, 1676},
            {18, 11, 1982},
            {19, 4, 2015},
            {9, 7, 2015},
            {12, 8, 2010},
            {30, 8, 2010},
            {21, 1, 2014},
            {20, 7, 2014},
            {18, 11, 2020}
    };

    int input_size = sizeof(inputs) / sizeof(inputs[0]);
    printf("Input:\nDate arr[] = {");
    print_arr(input_size, inputs); // print input array
    DateSort(inputs, 0, input_size - 1); // call the date sort function
    printf("\n\nOutput:\nDate arr[] = {");
    print_arr(input_size, inputs);// print sorted array
}
