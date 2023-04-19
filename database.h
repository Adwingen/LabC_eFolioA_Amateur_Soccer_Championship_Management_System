/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 2  - amateur soccer championship management
* @author Carlos Romão
* @module database.h
* @date 28/03/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DATABASE_TEAM "database_team.csv"
#define DATABASE_GAME "database_game.csv"

#define MAXSTR 255

#define HASH_TABLE_SIZE 1000

//extern int num_teams;

// Structure for storing team information
typedef struct team
{
    char name[MAXSTR];
    char locality[MAXSTR];
    int foundationYear;
} TEAM;

// Structure for storing game information
typedef struct game
{
    int gameData;
    char homeTeam[MAXSTR];
    int numberGoalsHomeTeam;
    char awayTeam[MAXSTR];
    int numberGoalsAwayTeam;
} GAME;

// Structure for storing team status information for the leaderboard (hash table)
typedef struct teamBoard
{
    char* name;
    int matches_played;
    int wins;
    int ties;
    int defeats;
    int goals_scored;
    int goals_conceded;
    int goal_difference;
    int points;
    
} TEAMBOARD;

// Structure for storing game status information for the leaderboard (hash table)
typedef struct gameBoard
{
    char* home_team;
    int home_goals;
    char* away_team;
    int away_goals;
} GAMEBOARD;


// Function prototypes
//
/////////////////////////////////////////////////////
//
//                Record TEAM Functions
// 
////////////////////////////////////////////////////
//Funtion to record new team register
void RecordTeam(TEAM* newRecord);

// input record data --> TEAM
void InputRecordTeam(TEAM* registrations, bool* isValid);

// Funtion to validate if the team name already exists
bool findTeamInFile(const char* teamName, const char* fileName);

// Function to search for a team in a CSV file and edit its details if it exists
void EditTeam();

// Function to search for a team in a CSV file and deleted if it exists
void DeleteTeam();

//////////////////////////////////////
//
//      Record GAME Functions
// 
//////////////////////////////////////

// input record data --> GAME
void AddGame();

// Function to search for a game in a CSV file and edit its details if it exists
void EditGame();

// Function to search for a game in a CSV file and deleted if it exists
void DeleteGame();

//////////////////////////////////////
//
//      Leaderboard Functions
// 
//////////////////////////////////////

// Function to find a team in the array of teams
int find_team(TEAMBOARD* teams, int num_teams, char* name);

// Function to add a new team to the array of teams
int add_team(TEAMBOARD* teams, int* num_teams, char* name);

// Function to update the league table based on a game result
void update_table(TEAMBOARD* teams, int* num_teams, char* home_team, int home_goals, char* away_team, int away_goals);

// Function to swap two teams in the array of teams
void swap_teams(TEAMBOARD* teams, int i, int j);

// Quicksort algorithm to sort the league table
void quicksort(TEAMBOARD* teams, int num_teams, int low, int high);

// Function to read the game data in a hash table
TEAMBOARD* read_teams_data(char* filename, int* num_teams);

// funtion to reset a hash table after a consult
void reset_table(TEAMBOARD* teams, int num_teams);


//////////////////////////////////////
//
//      Global Validate Functions
// 
//////////////////////////////////////

// validate year of foundation
bool validateDataYearFoundation(int yearFound);

// validate game day
bool validateGameDay(int gameDay);
