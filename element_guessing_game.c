
/* This is a simple game. The concept is to build an array 
    and ask user to enter size and elements of the array.
    Then ask the user to guess the number which the program
    picked and see if they can guess it. If the user guesses 
    the wrong number, they are given chances to try again depending
    on the how many elements the array has. Finally, regardless of 
    the result, the user is given the option to play again or end the game
*/

#include<stdio.h>
#include<stdlib.h>

void game();

int main() {

    game();
    return 0;
}

void game() {
    int length, max = 0;
    int target, guess = 0;
    int i, chance = 0;
    int counter = 1;
    char choice;

    printf("#################################################\n");
    printf("############# GUESS THE ELEMENT GAME ############\n");
    printf("#################################################\n");
    start:printf("Enter size of array (size > 0): ");
    
    while(scanf("%d",&length)) break;
    int a[length];
    if (length > 0) {
        printf("Enter elements of the array : ");
        for (size_t i = 0; i < length; i++)
        {
            while (scanf("%d",&a[i])) {
                printf("array[%d] = %d\n",i,a[i]);
                break;
            } 
        }
        max = chance = length-1;
        // printf("max array index = %d\n",max);
        // printf("min array index = %d\n",i);
    }
    else {
        printf("Error, Invalid Entry!\n");
        printf("#################################################\n");
        printf("################### GAME OVER ###################\n");
        printf("#################################################\n");
        exit(-1);
    }

    guess:printf("-------------------------------------------------\n");
    printf("Guess what element I am thinking about?: ");    
    
    while(scanf("%d",&target)) break;
    while(counter <= max + 1) { 
        guess = (max+i)/counter;
        if(a[guess] == target) {
            printf("-------------------------------------------------\n");
            printf("Yes OMG, You are smart!\n");
            printf("-------------------------------------------------\n");
            break;
        }
        else {
            printf("Sorry, I was thinking about %d\n", a[guess]);
            if (counter != (max+1)) {
                ++counter;
                printf("Try again! you have %d more chance(s)\n", chance);
                --chance;
                goto guess;
            }
            else {
                printf("-------------------------------------------------\n");
                printf("You lost, You can play again!\n");
                printf("#################################################\n");
                printf("################### GAME OVER ###################\n");
                printf("#################################################\n");
                break;  
            }
        }
    }
     printf("Do you want to play again? (Y/n): ");
     scanf(" %c", &choice); // " %c" the space is to skip leading whitespace and the non-whitespace character will be read
     
     if (choice == 'Y' || choice == 'y') {
        printf("-------------------------------------------------\n");
        counter = 1;
        goto start;
     }
     else
     {
        printf("-------------------------------------------------\n");
        printf("It was fun, Thank you for playing!\n");
        printf("#################################################\n");
        printf("################## END OF GAME ##################\n");
        printf("#################################################\n");     
    }
}