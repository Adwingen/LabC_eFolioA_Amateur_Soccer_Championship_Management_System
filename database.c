/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 2  - amateur soccer championship management
* @author Carlos Romão
* @module database.c
* @date 28/03/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "database.h"

//////////////////////////////////////
//
//      Record TEAM Functions
// 
//////////////////////////////////////
// Function to record new team register
void RecordTeam(TEAM* newRecord)
{
    FILE* file = fopen(DATABASE_TEAM, "a"); // "a" mode appends data to the end of the file
    if (file == NULL)
    {
        printf("\nError: Unable to open file.\n");
        return;
    }
    else
    {
        fprintf(file, "%s,%s,%d\n", newRecord->name, newRecord->locality, newRecord->foundationYear);
        fclose(file);
    }
}

// input record data --> TEAM
void InputRecordTeam(TEAM* registrations, bool* isValid)
{

    *isValid = true;
    //getchar();

    printf("Team Name: ");
    fgets(registrations->name, MAXSTR, stdin);
    // Remove the newline character from the end of the name string
    registrations->name[strcspn(registrations->name, "\n")] = '\0';

    // validate if the team name already exists
    if (findTeamInFile(registrations->name, DATABASE_TEAM))
    {
        printf("Error: a team with the same %s name already exists.\n",registrations->name);
        *isValid = false;
        return;
    }
        
        printf("Team Locality: ");
        fgets(registrations->locality, MAXSTR, stdin);
        // Remove the newline character from the end of the name string
        registrations->locality[strcspn(registrations->locality, "\n")] = '\0';

     
        // Loop until a valid year is entered
        int yearFound;
        bool validateYearFound;
        char input[MAXSTR];
        do
        {
            printf("Year of foundation: ");
            validateYearFound = true;
            fgets(input, MAXSTR, stdin);
            if (sscanf(input, "%d", &yearFound) != 1)
            {
                printf("Error: Invalid input. Please enter a valid integer.\n");
                validateYearFound = false;
            }
            else
            {
                validateYearFound = validateDataYearFoundation(yearFound);
            }
        } while (!validateYearFound);

        registrations->foundationYear = yearFound;

        printf("\nTeam registration successfully completed\n");

    /*}*/
}

// Funtion to validate if the team name already exists
bool findTeamInFile(const char* teamName, const char* fileName) 
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL) 
    {
        return false;
    }

    char line[1024];
    while (fgets(line, 1024, file)) 
    {
        char* token = strtok(line, ",");
        if (strcmp(token, teamName) == 0) 
        {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Function to search for a team in a CSV file and edit its details if it exists
void EditTeam()
{
    
    FILE* file = fopen(DATABASE_TEAM, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }
    // create a temporary file 
    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        //create a temp file
        tempFile = fopen("temp.csv", "r");
    }

    char line[MAXSTR];
    bool found = false;
    char teamName[MAXSTR];
    printf("Enter the team name to edit: ");
    scanf("%s", teamName);

    getchar();

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* name = strtok(line, ",");
        char* locality = strtok(NULL, ",");
        char* yearStr = strtok(NULL, ",");
        int year = atoi(yearStr);

        if (strcmp(name, teamName) == 0)
        {
            found = true;

            TEAM updatedTeam;

            printf("Enter new team name (current: %s): ", name);
            fgets(updatedTeam.name, MAXSTR, stdin);
            // remove the enter
            updatedTeam.name[strcspn(updatedTeam.name, "\n")] = '\0';

            printf("Enter new team city (current: %s): ", locality);
            fgets(updatedTeam.locality, MAXSTR, stdin);
            // remove the enter
            updatedTeam.locality[strcspn(updatedTeam.locality, "\n")] = '\0';

            // Loop until a valid year is entered
            int yearFound;
            bool validateYearFound;
            char input[MAXSTR];
            do
            {
                printf("Enter new foundation year (current: %d): ", year);
                validateYearFound = true;
                fgets(input, MAXSTR, stdin);
                if (sscanf(input, "%d", &yearFound) != 1)
                {
                    printf("Error: Invalid input. Please enter a valid integer.\n");
                    validateYearFound = false;
                }
                else
                {
                    validateYearFound = validateDataYearFoundation(yearFound);
                }
            } while (!validateYearFound);

            updatedTeam.foundationYear = yearFound;
           
            fprintf(tempFile, "%s,%s,%d\n", updatedTeam.name, updatedTeam.locality, updatedTeam.foundationYear);
        }
        else
        {
            fprintf(tempFile, "%s,%s,%d\n", name, locality, year);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        // Replace the original file with the temporary file
        if (remove(DATABASE_TEAM) == 0 && rename("temp.csv", DATABASE_TEAM) == 0)
        {
            printf("Team information updated successfully.\n");
        }
        else
        {
            printf("Error: Unable to update team information.\n");
        }
    }
    else
    {
        printf("Error: Team not found.\n");
        remove("temp.csv");
    }
}

// Function to search for a team in a CSV file and deleted if it exists
void DeleteTeam()
{
    FILE* file = fopen(DATABASE_TEAM, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        //create a file
        tempFile = fopen("temp.csv", "r");
    }

    char line[MAXSTR];
    bool found = false;
    char teamName[MAXSTR];
    printf("Enter the team name to delete: ");
    scanf("%s", teamName);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* name = strtok(line, ",");
        char* locality = strtok(NULL, ",");
        char* yearStr = strtok(NULL, ",");
        int year = atoi(yearStr);

        if (strcmp(name, teamName) == 0)
        {
            found = true;
        }
        else
        {
            fprintf(tempFile, "%s,%s,%d\n", name, locality, year);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        // Replace the original file with the temporary file
        if (remove(DATABASE_TEAM) == 0 && rename("temp.csv", DATABASE_TEAM) == 0)
        {
            printf("Team information deleted successfully.\n");
        }
        else
        {
            printf("Error: Unable to delete team information.\n");
        }
    }
    else
    {
        printf("Error: Team not found.\n");
        remove("temp.csv");
    }
}


//////////////////////////////////////
//
//      Record GAME Functions
// 
//////////////////////////////////////

// input record data --> GAME
void AddGame()
{
    
    GAME addTeam;
    // Open the team database file for validation
    FILE* teamFile = fopen(DATABASE_TEAM, "r");
    if (teamFile == NULL)
    {
        printf("Error: Unable to open team database file.\n");
        return;
    }

    // Open the game database file for appending
    FILE* gameFile = fopen(DATABASE_GAME, "a");
    if (gameFile == NULL)
    {
        // create the file
        gameFile = fopen(DATABASE_GAME, "r");
    }

    // Read the game date from the user
    // Loop until a valid year is entered
    int gameFound;
    bool validateGameFound;
    char input[MAXSTR];
    do
    {
        printf("Enter the game date in format ddmmyyyy: ");
        validateGameFound = true;
        fgets(input, MAXSTR, stdin);
        if (sscanf(input, "%d", &gameFound) != 1)
        {
            printf("Error: Invalid input. Please enter a valid integer.\n");
            validateGameFound = false;
        }
        else
        {
            validateGameFound = validateGameDay(gameFound);
        }
    } while (!validateGameFound);


    addTeam.gameData = gameFound;


    // Read the home team name from the user
    printf("Enter the home team name: ");
    fgets(input, MAXSTR, stdin);
    input[strcspn(input, "\n")] = 0; // remove the newline character
    strcpy(addTeam.homeTeam, input);

    // Validate that the home team exists in the team database
    bool homeTeamExists = false;
    char teamLine[MAXSTR];
    while (fgets(teamLine, sizeof(teamLine), teamFile) != NULL)
    {
        char* name = strtok(teamLine, ",");
        if (strcmp(name, addTeam.homeTeam) == 0)
        {
            homeTeamExists = true;
            break;
        }
    }
    if (!homeTeamExists)
    {
        printf("Error: Home team '%s' not found in team database.\n", addTeam.homeTeam);
        fclose(teamFile);
        fclose(gameFile);
        getchar();
        return;
    }

    // Read the away team name from the user
    printf("Enter the away team name: ");
    fgets(input, MAXSTR, stdin);
    input[strcspn(input, "\n")] = 0; // remove the newline character
    strcpy(addTeam.awayTeam, input);

    // Validate that the away team exists in the team database
    bool awayTeamExists = false;
    rewind(teamFile); // rewind to the beginning of the file
    while (fgets(teamLine, sizeof(teamLine), teamFile) != NULL)
    {
        char* name = strtok(teamLine, ",");
        if (strcmp(name, addTeam.awayTeam) == 0)
        {
            awayTeamExists = true;
            break;
        }
    }
    if (!awayTeamExists)
    {
        printf("Error: Away team '%s' not found in team database.\n", addTeam.awayTeam);
        fclose(teamFile);
        fclose(gameFile);
        getchar();
        return;
    }

    // Read the number of goals scored by the home team from the user
    printf("Enter the number of goals scored by the home team: ");
    scanf("%d", &addTeam.numberGoalsHomeTeam);

    // Read the number of goals scored by the away team from the user
    printf("Enter the number of goals scored by the away team: ");
    scanf("%d", &addTeam.numberGoalsAwayTeam);


    // Write the game information to the game database file
    fprintf(gameFile, "%d,%s,%d,%s,%d\n", addTeam.gameData, addTeam.homeTeam, addTeam.numberGoalsHomeTeam
        , addTeam.awayTeam, addTeam.numberGoalsAwayTeam);
    fclose(teamFile);
    fclose(gameFile);

    printf("Game added successfully.\n");

    getchar();

   
}

// Function to search for a game in a CSV file and edit its details if it exists
void EditGame()
{
    // Open the game database file for reading
    FILE* file = fopen(DATABASE_GAME, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Create a temporary file for writing
    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    // Read the search criteria from the user
    GAME editGame;
    printf("Enter the departure date of the game to edit (in format ddmmyyyy): ");
    scanf("%d", &editGame.gameData);

    printf("Enter the name of the home team: ");
    scanf(" %[^\n]", editGame.homeTeam);
    printf("Enter the name of the away team: ");
    scanf(" %[^\n]", editGame.awayTeam);

    // Loop over each line in the file and edit the matching game if found
    char line[MAXSTR];
    bool found = false;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* dateStr = strtok(line, ",");
        char* homeTeam = strtok(NULL, ",");
        char* homeGoalsStr = strtok(NULL, ",");
        char* awayTeam = strtok(NULL, ",");
        char* awayGoalsStr = strtok(NULL, ",");

        int date = atoi(dateStr);
        int homeGoals = atoi(homeGoalsStr);
        int awayGoals = atoi(awayGoalsStr);

        // If this is the game we're looking for, prompt the user for new data and write it to the temp file
        if (date == editGame.gameData && strcmp(homeTeam, editGame.homeTeam) == 0 && strcmp(awayTeam, editGame.awayTeam) == 0)
        {
            found = true;

            // Prompt the user for new data
            printf("Enter new number of goals scored by the home team (current: %d): ", homeGoals);
            scanf("%d", &editGame.numberGoalsHomeTeam);
            printf("Enter new number of goals scored by the away team (current: %d): ", awayGoals);
            scanf("%d", &editGame.numberGoalsAwayTeam);

            // Write the edited game data to the temp file
            fprintf(tempFile, "%d,%s,%d,%s,%d\n", date, homeTeam, editGame.numberGoalsHomeTeam, awayTeam, editGame.numberGoalsAwayTeam);
        }
        else
        {
            // Write the unchanged game data to the temp file
            fprintf(tempFile, "%d,%s,%d,%s,%d\n", date, homeTeam, homeGoals, awayTeam, awayGoals);
        }
    }

    // Close the file handles
    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temp file if a matching game was found
    if (found)
    {
        if (remove(DATABASE_GAME) == 0 && rename("temp.csv", DATABASE_GAME) == 0)
        {
            printf("Game information updated successfully.\n");
        }
        else
        {
            printf("Error: Unable to update game information.\n");
        }
    }
    else
    {
        printf("Error: Game not found.\n");
        remove("temp.csv");
    }

    getchar();
}

// Function to search for a game in a CSV file and deleted if it exists
void DeleteGame()
{
    // Open the game database file for reading
    FILE* file = fopen(DATABASE_GAME, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    // Create a temporary file for writing
    FILE* tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL)
    {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    // Read the search criteria from the user
    GAME deleteGame;
    printf("Enter the departure date of the game to delete (in ddmmyyyy format): ");
    scanf("%d", &deleteGame.gameData);
    printf("Enter the name of the home team: ");
    scanf(" %[^\n]", deleteGame.homeTeam);
    printf("Enter the name of the away team: ");
    scanf(" %[^\n]", deleteGame.awayTeam);

    // Loop over each line in the file and copy it to the temp file if it doesn't match the search criteria
    char line[MAXSTR];
    bool found = false;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char* dateStr = strtok(line, ",");
        char* homeTeam = strtok(NULL, ",");
        char* homeGoalsStr = strtok(NULL, ",");
        char* awayTeam = strtok(NULL, ",");
        char* awayGoalsStr = strtok(NULL, ",");

        int date = atoi(dateStr);
        int homeGoals = atoi(homeGoalsStr);
        int awayGoals = atoi(awayGoalsStr);

        // If this is the game we're looking for, set the found flag to true
        if (date == deleteGame.gameData && strcmp(homeTeam, deleteGame.homeTeam) == 0 && strcmp(awayTeam, deleteGame.awayTeam) == 0)
        {
            found = true;
        }
        else
        {
            // Write the unchanged game data to the temp file
            fprintf(tempFile, "%d,%s,%d,%s,%d\n", date, homeTeam, homeGoals, awayTeam, awayGoals);
        }
    }

    // Close the file handles
    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temp file if a matching game was found
    if (found)
    {
        if (remove(DATABASE_GAME) == 0 && rename("temp.csv", DATABASE_GAME) == 0)
        {
            printf("Game deleted successfully.\n");
        }
        else
        {
            printf("Error: Unable to delete game.\n");
        }
    }
    else
    {
        printf("Error: Game not found.\n");
        remove("temp.csv");
    }

    getchar();
}

//////////////////////////////////////
//
//      Learderboard Functions
// 
//////////////////////////////////////

// Function to find a team in the array of teams
int find_team(TEAMBOARD *teams, int num_teams,char* name) 
{
 
    for (int i = 0; i < num_teams; i++) 
    {
        if (strcmp(teams[i].name, name) == 0) 
        {
            return i;
        }
    }
    return -1;
}


// Function to add a new team to the array of teams
int add_team(TEAMBOARD* teams, int *num_teams,char* name)
{
    if (*num_teams >= HASH_TABLE_SIZE) 
    {
        return -1;
    }
    teams[*num_teams].name = (char*)malloc(strlen(name) + 1);
    strcpy(teams[*num_teams].name, name);

    teams[*num_teams].matches_played = 0;
    teams[*num_teams].wins = 0;
    teams[*num_teams].ties = 0;
    teams[*num_teams].defeats = 0;
    teams[*num_teams].goals_scored = 0;
    teams[*num_teams].goals_conceded = 0;
    teams[*num_teams].goal_difference = 0;
    teams[*num_teams].points = 0;

    (*num_teams)++;
    return (*num_teams) - 1;
}


// Function to update the league table based on a game result
void update_table(TEAMBOARD* teams, int* num_teams,char* home_team, int home_goals, char* away_team, int away_goals)
{
    
    int home_index = find_team(teams, *num_teams, home_team);
    if (home_index == -1) 
    {
        home_index = add_team(teams, num_teams, home_team);
    }
    int away_index = find_team(teams, *num_teams, away_team);
    if (away_index == -1) 
    {
        away_index = add_team(teams, num_teams, away_team);
    }
    teams[home_index].matches_played++;
    teams[away_index].matches_played++;
    teams[home_index].goals_scored += home_goals;
    teams[away_index].goals_scored += away_goals;
    teams[home_index].goals_conceded += away_goals;
    teams[away_index].goals_conceded += home_goals;
    teams[home_index].goal_difference = teams[home_index].goals_scored - teams[home_index].goals_conceded;
    teams[away_index].goal_difference = teams[away_index].goals_scored - teams[away_index].goals_conceded;
    if (home_goals > away_goals) 
    {
        teams[home_index].wins++;
        teams[away_index].defeats++;
        teams[home_index].points += 3;
    }
    else if (home_goals == away_goals) 
    {
        teams[home_index].ties++;
        teams[away_index].ties++;
        teams[home_index].points += 1;
        teams[away_index].points += 1;
    }
    else 
    {
        teams[home_index].defeats++;
        teams[away_index].wins++;
        teams[away_index].points += 3;
    }
}

// Function to swap two teams in the array of teams
void swap_teams(TEAMBOARD* teams,int i, int j)
{
    
    TEAMBOARD temp = teams[i];
    teams[i] = teams[j];
    teams[j] = temp;
}

// Quicksort algorithm to sort the league table
void quicksort(TEAMBOARD* teams, int num_teams,int low, int high)
{

    int i = low;
    int j = high;
    int pivot = teams[(low + high) / 2].points;
    int pivot_diff = teams[(low + high) / 2].goal_difference;
    while (i <= j) {
        while (teams[i].points > pivot || (teams[i].points == pivot && teams[i].goal_difference > pivot_diff)) 
        {
            i++;
        }
        while (teams[j].points < pivot || (teams[j].points == pivot && teams[j].goal_difference < pivot_diff)) 
        {
            j--;
        }
        if (i <= j) 
        {
            swap_teams(teams, i, j);
            i++;
            j--;
        }
    }
    if (low < j) 
    {
        quicksort(teams, num_teams, low, j);
    }
    if (i < high) 
    {
        quicksort(teams, num_teams, i, high);
    }
}

// Function to read the game data in a hash table
TEAMBOARD* read_teams_data(char* filename, int* num_teams) 
{
    // Allocate memory for the teams array
    TEAMBOARD* teams = (TEAMBOARD*)malloc(HASH_TABLE_SIZE * sizeof(TEAMBOARD));
    if (teams == NULL) 
    {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    *num_teams = 0;

    // Open the CSV file and read the data
    FILE* file = fopen(filename, "r");
    if (file == NULL) 
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    char line[MAXSTR];
    while (fgets(line, sizeof(line), file)) 
    {
        char* date_str = strtok(line, ",");
        char* home_team = strtok(NULL, ",");
        char* home_goals_str = strtok(NULL, ",");
        char* away_team = strtok(NULL, ",");
        char* away_goals_str = strtok(NULL, ",\n");
        if (home_team != NULL && home_goals_str != NULL && away_team != NULL && away_goals_str != NULL) 
        {
            int home_goals = atoi(home_goals_str);
            int away_goals = atoi(away_goals_str);
            update_table(teams, num_teams, home_team, home_goals, away_team, away_goals);
        }
    }
    fclose(file);

    // Reallocate memory for the teams array to match the actual number of teams
    teams = (TEAMBOARD*)realloc(teams, (*num_teams) * sizeof(TEAMBOARD));
    if (teams == NULL) 
    {
        perror("Unable to reallocate memory");
        exit(EXIT_FAILURE);
    }

    return teams;
}

// funtion to reset a hash table after a consult
void reset_table(TEAMBOARD *teams, int num_teams) 
{
    
    for (int i = 0; i < num_teams; i++) 
    {
        teams[i].matches_played = 0;
        teams[i].wins = 0;
        teams[i].ties = 0;
        teams[i].defeats = 0;
        teams[i].goals_scored = 0;
        teams[i].goals_conceded = 0;
        teams[i].goal_difference = 0;
        teams[i].points = 0;
    }
}


//////////////////////////////////////
//
//      Global Validate Functions
// 
//////////////////////////////////////

// validate year of foundation
bool validateDataYearFoundation(int yearFound)
{
    if (yearFound >= 1800 && yearFound <= 2023)
        return true;
    else
    {
        printf("Error: Invalid foundation year! Enter a date between 1800 and 2023.\n");
        return false;
    }

}

// validate game day
bool validateGameDay(int gameDay)
{
    char arrayOfInt[9];
    sprintf(arrayOfInt, "%08d", gameDay);

    char day[3];
    strncpy(day, arrayOfInt, 2);
    day[2] = '\0';

    char month[3];
    strncpy(month, arrayOfInt + 2, 2);
    month[2] = '\0';

    int year = atoi(arrayOfInt + 4);

    if (atoi(day) < 1 || atoi(day) > 31)
    {
        printf("Error: %s is an invalid game day. Enter a game date between 01 and 31.\n", day);
        return false;
    }

    if (atoi(month) < 1 || atoi(month) > 12)
    {
        printf("Error: %s is an invalid game month. Enter a game date between 01 and 12.\n", month);
        return false;
    }

    if (year < 1800 || year > 2023)
    {
        printf("Error: %d is an invalid game year. Enter a game date between 1800 and 2023.\n", year);
        return false;
    }

    return true;
}


