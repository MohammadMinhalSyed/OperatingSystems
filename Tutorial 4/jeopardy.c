/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"
#include "questions.c"
#include "players.c"
// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    int i; //Used to cycle through players
    // Display the game introduction and initialize the questions
    questions.initialize_game();

    // Prompt for players names
    printf("Enter the number of player(from 1 to 4)\n");
    scanf_s("%d", &num_players,sizeof(int));
       
    // initialize each of the players in the array
    for (i=0; i < num_players; i++)
    {
        printf("Enter Name: ");
        scanf_s("%d", players[i].name, 20);
        getchar(); 
    }


    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        players.update_score();

        // Execute the game until all questions are answered
        for (i=0; i < questions.NUM_QUESTIONS; i++){
            questions.display_categories(); // Displays questions and categories that are unanswered
        }
        
        // Display the final results and exit
        show_results();
        exit();
        
    }
    return EXIT_SUCCESS;
}
void tokenize(char* input, char** tokens) {
    char* str;

    if ((str = strtok(input, "")) != NULL)
        if (strcmp(str, "who") != 0 && strcmp(str, "what") != 0)
            return;

    if ((str = strtok(NULL, "")) != NULL)
        if (strcmp(str, "is") != 0)
            return;

    *tokens = strtok(NULL, "\n");
}

void show_results(player* players, int num_players) {
    int name = 0;
    int score = 0;
    int winner = 0;

    for (int i = 0; i < num_players; i++) {
        if ((int)strlen(players[i].name) > name)
            name = strlen(players[i].name);

        if (players[i].score > score) {
            score = players[i].score;
            winner = i;
        }
    }

    printf("Scores: \n");
    for (int i = 0; i < num_players; i++)
        printf("%*s: %d\n", name + 1, players[i].name, players[i].score);

    printf("Winner: %s", players[winner].name);
}
