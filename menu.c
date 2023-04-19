

/**
*
* LEI - UAB
*
* @classroom Laborat�rio de Programa��o (turma 3)
* @brief Atv 2  - amateur soccer championship management
* @author Carlos Rom�o
* @module menu.c
* @date 28/03/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "menu.h"


// Functions Menu
//
////////////////////////////////////////
//
// 
// 
// /////////////////////////////////////
// Function to print the menu options
void print_main_menu()
{
    printf("\n >>> Main Menu <<< \n");

    printf("\n1. team management menu\n");
    printf("2. game management\n");
    printf("3. leaderboard\n");
    printf("4. exit\n");
    printf("please enter your choice: ");
}

// Function to print the sub-menu team management
void print_teamManagement_menu()
{
    int choice;
    TEAM newRecord;
    bool isValid;

    printf("\n >>> Team Management Menu <<< \n");

    //clearKeyboardBuffer();

    do
    {
        printf("\n1. add team\n");
        printf("2. edit team\n");
        printf("3. delete team\n");
        printf("4. team list\n");
        printf("5. back to main menu\n");
        printf("please enter your choice: ");

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
            // register a team
            InputRecordTeam(&newRecord, &isValid);
            if (isValid)
                RecordTeam(&newRecord);
            break;
        case 2:
            // edit a team
            EditTeam();
           // RecordTeam(&newRecord);
            break;
        case 3:
            // delete
            DeleteTeam();
            break;
        case 4:
            // print team lists
            print_teamLists();
            break;
        case 5:
            printf("Going back to Main Menu.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 5);
}

// Function to print the sub-menu game management
void print_gameManagement_menu()
{
    int choice;
    TEAM newRecord;
    bool isValid;

    printf("\n >>> Game Management Menu <<< \n");

    
    do
    {
        //clearKeyboardBuffer();

        printf("\n1. add game\n");
        printf("2. edit game\n");
        printf("3. delete game\n");
        printf("4. game list\n");
        printf("5. back to main menu\n");
        printf("please enter your choice: ");
        
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
            // add a game
            AddGame();
            break;
        case 2:
            // edit a game
            EditGame();
           // RecordTeam(&newRecord);
            break;
        case 3:
            // delete a game
            DeleteGame();
            break;
        case 4:
            // print game lists
            print_gameLists();
            break;
        case 5:
            printf("Going back to Main Menu.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 5);
}

// Function to print the sub-menu leaderboard
void print_leaderBoard_menu()
{
    int choice;
   
    TEAMBOARD* teams = NULL;
    int num_teams = 0;
    printf("\n >>> Leaderboard Menu <<< \n");

    do
    {

        printf("\n1. leaderboard\n");
        printf("2. back to main menu\n");
        printf("please enter your choice: ");

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
            // add a game
            teams = read_teams_data(DATABASE_GAME, &num_teams);
            printLeaderboard(teams,num_teams);
            reset_table(teams,num_teams);
            break;
        case 2:
            printf("Going back to Main Menu.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 2);
}

////////////////////////////////////////
//
//  Print List
// 
// /////////////////////////////////////
// 
// Function to print the list of team
void print_teamLists()
{
    FILE* file = fopen(DATABASE_TEAM, "r");
    if (file == NULL) 
    {
        printf("Error: could not open file.\n");
        return;
    }

    // check if file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        printf("Error: file is empty.\n");
        fclose(file);
        return;
    }
    fseek(file, 0, SEEK_SET);

    printf("\nTeam List\n");
    printf("|     Name       |       City          |  Year Foundation|\n");
    printf("+----------------+---------------------+-----------------+\n");

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) 
    {
        // parse CSV line
       
            char* name = strtok(line, ",");
            char* locality = strtok(NULL, ",");
            char* yearStr = strtok(NULL, ",");
            int year = atoi(yearStr);

            // print team
            printf("| %14s | %19s | %15d |\n", name, locality, year);
        

       
    }

    printf("+----------------+---------------------+-----------------+\n");
    fclose(file);
}

// Function to print the list of games
void print_gameLists()
{
    FILE* file = fopen(DATABASE_GAME, "r");
    if (file == NULL)
    {
        printf("Error: could not open file.\n");
        return;
    }

    // check if file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        printf("Error: file is empty.\n");
        fclose(file);
        return;
    }

    fseek(file, 0, SEEK_SET);

    printf("\nGame List\n");
    printf("| Game Day  | Home Team | Goals | Away Team | Goals |\n");
    printf("+-----------+-----------+-------+-----------+-------+\n");

    char line[200];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // parse csv line
        char* gameData = strtok(line, ",");
        char* homeTeam = strtok(NULL, ",");
        char* homeGoals = strtok(NULL, ",");
        char* awayTeam = strtok(NULL, ",");
        char* awayGoals = strtok(NULL, ",");

        int gameDataInt = atoi(gameData);
        int homeGoalsInt = atoi(homeGoals);
        int awayGoalsInt = atoi(awayGoals);

        // print game list
        printf("| %9d | %9s | %5d | %9s | %5d |\n", gameDataInt, homeTeam, homeGoalsInt, awayTeam, awayGoalsInt);
    }

    printf("+-----------+-----------+-------+-----------+-------+\n");
    fclose(file);
}


////////////////////////////////////////
//
//  print Leaderboard
// 
// /////////////////////////////////////

// print learderboard
void printLeaderboard(TEAMBOARD *teams,int num_teams)
{
    
    // Sort the league table by points and goal difference using quicksort
    quicksort(teams,num_teams,0, num_teams - 1);

    // Print out the league table
    printf("+------+-----------------+----+----+----+----+----+----+----+-----+\n");
    printf("| Rank | Team            | GP |  W |  D |  L | GS | GC | GD | Pts |\n");
    printf("+------+-----------------+----+----+----+----+----+----+----+-----+\n");

    
    for (int i = 0; i < num_teams; i++)
    {
        printf("| %-4d | %-15s |%3d |%3d |%3d |%3d |%3d |%3d |%3d |%3d  |\n",
            i + 1,
            teams[i].name,
            teams[i].matches_played,
            teams[i].wins,
            teams[i].ties,
            teams[i].defeats,
            teams[i].goals_scored,
            teams[i].goals_conceded,
            teams[i].goal_difference,
            teams[i].points);
    }
    printf("+------+-----------------+----+----+----+----+----+----+----+-----+\n");
}



