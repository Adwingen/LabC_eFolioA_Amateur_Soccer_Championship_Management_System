/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 2  - amateur soccer championship management
* @author Carlos Romão
* @module main.c
* @date 28/03/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "menu.h"

// Main function
int main() 
{
    int choice;
   
    printf("Welcome to the Amateur Soccer Championship Management System\n");


    do 
    {
        print_main_menu();

        // Read input as string
        char input[MAXSTR];
        fgets(input, MAXSTR, stdin);

        // Parse integer from input string
        if (sscanf(input, "%d", &choice) != 1)
        {
            printf("Error: Invalid input. Please enter a valid integer.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            // go to team management
            print_teamManagement_menu();
            break;
        case 2:
            // go to game management
            print_gameManagement_menu();
            break;
        case 3:
            // leaderboard
            print_leaderBoard_menu();
            break;
        case 4:
            // exit
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 4);

    return 0;
}