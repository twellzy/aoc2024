#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
    char temp[1];
    int charcount = 18000;
    int elem = 0;
    FILE *fptr = fopen("input.txt", "r");

    /*
    while (!feof(fptr) && fgets(temp, 1, fptr) != NULL){
        charcount++;
    }
    fclose(fptr);

    */
    char buffer[charcount];
    fread(buffer, sizeof(char), charcount, fptr);

    int num[8];
    int j = 4;
    int num1;
    int num2;
    int numsplace = 0;
    int count = 0;
    bool secondnum;
    bool failed;
    int total = 0;
    bool enabled = true;
    for (int i = 0; i < charcount; i++){
        failed = true;
        num1 = 0;
        num2 = 0;

        if (buffer[i] == 'd' && buffer[i+1] == 'o' && buffer[i+2] == 'n' && buffer[i+3] == '\'' && buffer[i+4] == 't' && buffer[i+5] == '(' && buffer[i+6] == ')'){
            enabled = false;
        }

        else if (buffer[i] == 'd' && buffer[i+1] == 'o' && buffer[i+2] == '(' && buffer[i+3] == ')'){
            enabled = true;
        }

        
        if (buffer[i] == 'm' && buffer[i+1] == 'u' && buffer[i+2] == 'l' && buffer[i+3] == '(' && enabled){
            while (buffer[i+j] != ')'){
                if (buffer[i+j] >= 0x30 && buffer[i+j] <= 0x39){
                    num[numsplace++] = buffer[i+j];
                }

                else if (buffer[i+j] == ','){
                    while (numsplace > 0){
                        num1 += (num[count++]-48)*pow(10, numsplace-1);
                        numsplace--;
                    }
                    secondnum = true;
                }

                else if (numsplace > 0){
                    numsplace = 0;
                    failed = true;
                    break;
                }
                else{
                    failed = true;
                    break;
                }

                if (buffer[i+j+1] == ')' && secondnum){
                    while (numsplace > 0){
                        num2 += (num[count++] - 48)*pow(10, numsplace-1);
                        numsplace--;
                    }
                    failed = false;
                }
                count = 0;

                j++;
            }

            j = 4;
        }
        if (!failed){
            total += num1*num2;
            printf("num1 = %d\n", num1);
            printf("num2 = %d\n", num2);
            printf("total = %d\n", total);
            printf("\n");
            num1 = 0;
            num2 = 0;
        }
        

    }

    printf("Your total is %d \n", total);


    


}