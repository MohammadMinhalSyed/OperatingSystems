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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    question questions[NUM_QUESTIONS]= {
        {"programming", "What is used as a logical OR operator sign", "||", 10, false},
        {"programming", "What keywork is used to deine macros which the compiler will substitute throughtout the code", "#define", 20, false},
        {"programming", "What placeholder is used for strings", "%s", 15, false},
        {"programming", "What function is similar to printf but only prints text and adds a newline to the end automatically", "puts", 50, false},
        {"algorithms", "What notation is also known as Reverse Polish notation", "postfix", 20, false},
        {"algorithms", "What is a linked list where every node stores address of next node in the list and last node has address as NULL", "singly", 15, false},
        {"algorithms", "What is a type of linear data structure that uses LIFO/FILO for accessing elements", "stack", 10, false},
        {"algorithms", "What is the number of nodes along the shortest path from the root node down to the nearest leaf node", "minimum depth", 50, false},
        {"databases", "What is a collection of application programs which allow the user to organize, restore and retrieve information", "DBMS", 50, false},
        {"databases", "What is called the process of removing redundant data from the database by splitting the table", "normalization", 20, false},
        {"databases", "What represents user views and their mapping to the conceptual schema", "VDL", 15, false},
        {"databases", "What data structure is in the form of a tree for external memory that reads and writes large blocks of data", "b tree", 10, false},
        
        };


}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    int index=0;
    // print categories and dollar values for each unanswered question in questions array
    printf("Below questions are available:\n");
    printf("============================================================================ \n");
    for (index=0; index<NUM_QUESTIONS; index++){
        if (questions[index].answered == false){
            printf("       Category: %s : \n", questions[index].category);
            printf("       Value: %d \n", questions[index].value);
            printf("============================================================================ \n");
        }

    }

}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    int index=0;
    int strcheck;
    for (index=0; index < NUM_QUESTIONS; index++){
        strcheck=strcmp(questions[index].category , category);
        if (questions[index].value == value && strcheck==0 ){
            printf("Question is: %s : \n", questions[index].question);
            printf("Question Value: %d \n", questions[index].value);
            printf("============================================================================ \n");
        }

    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    int index=0;
    int strcheck;
    for (index=0; index < NUM_QUESTIONS; index++){
        strcheck=strcmp(questions[index].category , category);
        if (questions[index].value == value && strcheck==0){
            strcheck = strcmp(questions[index].answer, answer);
            if (strcheck== 0){
                return true;
            }
            
        }

    }
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    int index=0;
    int strcheck;
    for (index=0; index < NUM_QUESTIONS; index++){
        strcheck=strcmp(questions[index].category , category);
        if (questions[index].value == value && strcheck==0 && questions[index].answered == true){
            
                return true;
                       
        }

    }
    // lookup the question and see if it's already been marked as answered
    return false;
}
