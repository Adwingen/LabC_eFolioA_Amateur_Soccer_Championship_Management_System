/**
*
* LEI - UAB
*
* @classroom Laboratório de Programação (turma 3)
* @brief Atv 2  - amateur soccer championship management
* @author Carlos Romão
* @module menu.h
* @date 28/03/2023
*
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "database.h"

// Function prototypes
//
////////////////////////////////////////
////////////////////////////////////////
//
// 
// 
// /////////////////////////////////////
// Function to print the main menu
void print_main_menu();

// Function to print the sub-menu team management
void print_teamManagement_menu();

// Function to print the sub-menu game management
void print_gameManagement_menu();

// Function to print the sub-menu leaderboard
void print_leaderBoard_menu();


////////////////////////////////////////
//
//  Print List
// 
// /////////////////////////////////////
// 
// Function to print the list of team
void print_teamLists();

// Function to print the list of games
void print_gameLists();

////////////////////////////////////////
//
//  print Leaderboard
// 
// /////////////////////////////////////


// print learderboard
void printLeaderboard(TEAMBOARD* teams, int num_teams);




