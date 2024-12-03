#include <stdio.h>
#include <stdlib.h>

int main(){
    char buffer[14];
    int lines = 0;
    FILE *fptr = fopen("numlist.txt", "r");

    while (fgets(buffer, 256, fptr) != NULL){
        lines++;
    }

    fclose(fptr);
    fptr = fopen("numlist.txt", "r");

    int leftlist[lines];
    int rightlist[lines];
    int elem = 0;
    int counter = 0;

    while (fgets(buffer, 15, fptr) != NULL){
        for (int i = 0; i < 15; i++){
            if (buffer[i] == 0x20){
                elem += ((buffer[i-1]-48)*1);
                elem += ((buffer[i-2]-48)*10);
                elem += ((buffer[i-3]-48)*100);
                elem += ((buffer[i-4]-48)*1000);
                elem += ((buffer[i-5]-48)*10000);
                leftlist[counter++] = elem;
                elem = 0;
                break;
            }
        }
    }
    fclose(fptr);
    fptr = fopen("numlist.txt", "r");
    counter = 0;
    while (fgets(buffer, 15, fptr) != NULL){
        for (int i = 7; i < 15; i++){
            if (buffer[i] == 0x20){
                elem += ((buffer[i+1]-48)*10000);
                elem += ((buffer[i+2]-48)*1000);
                elem += ((buffer[i+3]-48)*100);
                elem += ((buffer[i+4]-48)*10);
                elem += ((buffer[i+5]-48)*1);
                rightlist[counter++] = elem;
                elem = 0;
                break;
            }
        }
    }
    fclose(fptr);

    int leftsorted[lines];
    int rightsorted[lines];
    int min = 1000000;
    int index = 0;
    for (int i = 0; i < 1000; i++){
        leftsorted[i] = leftlist[i];
        for (int j = 0; j < 1000; j++){
            if (leftlist[j] <= leftsorted[i]){
                index = j;
                leftsorted[i] = leftlist[j];
            }
        }
        leftlist[index] = 1000000;
    }


    for (int i = 0; i < 1000; i++){
        rightsorted[i] = rightlist[i];
        for (int j = 0; j < 1000; j++){
            if (rightlist[j] <= rightsorted[i]){
                index = j;
                rightsorted[i] = rightlist[j];
            }
        }
        rightlist[index] = 1000000;
    }

    int diff = 0;
    for (int i = 0; i < 1000; i++){
        diff += abs(leftsorted[i]-rightsorted[i]);
    }
    printf("the difference is %d ", diff);


    int rocurrences = 0;
    int sim_score = 0;
    for (int i = 0; i < 1000; i++){
        for (int j = 0; j < 1000; j++){
            if (leftsorted[i] == rightsorted[j]){
                rocurrences++;
            }
            if (leftsorted[i] < rightsorted[j]){
                break;
            }
        }
        sim_score += leftsorted[i]*rocurrences;
        rocurrences = 0;
    }
    

    printf("the similirity score was %d ", sim_score);
}

