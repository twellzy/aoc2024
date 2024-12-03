#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

int main(){
    char buffer[256];
    int data[256];

    FILE *fptr = fopen("data.txt", "r");
    int elem = 0;
    int j = 0;
    int count = 0;
    int prevnum = 0;
    int numsafe = 0;
    bool increasing;
    int problems = 0;
    while (fgets(buffer, 256, fptr) != NULL){
        for (int i = 0; i < strlen(buffer); i++){
            while (buffer[i+j] != 0x20 && buffer[i+j] != 0x0a){
                j++;
            }
            while (j > 0){
                j--;
                elem += (buffer[i++]-48)*pow(10, j);
            }
            data[count] = elem;
            count++;
            elem = 0;
            j = 0;
        }

        increasing = data[0] < data[1];
        prevnum = data[0];

        for (int i = 1; i < count; i++){

            if (abs(data[i]-prevnum) > 3 && prevnum != 0){
                problems++;
                prevnum = 0;
            }

            if (data[i] == prevnum && prevnum != 0){
                problems++;
                prevnum = 0;
            }

            if (data[i] < prevnum && increasing && prevnum != 0){
                problems++;
                prevnum = 0;
            }

            if (data[i] > prevnum && !increasing && prevnum != 0){
                problems++;
                prevnum = 0;
            }

            if (problems >= 2){
                break;
            }

            if (i+1 == count){
                numsafe += 1;
            }

            prevnum = data[i];


        }
        count = 0;
        problems = 0;
    }
    printf("%d were safe", numsafe);



}