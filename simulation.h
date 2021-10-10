#ifndef SIMULATION_H
#define SIMULATION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Simulation result  structure*/
typedef struct  s_sim{
    int Test_ID;
    int Robot_number;
    int finish_line_distance;
    int finish_line_time;
    int Strength;
    int Test_score;
}t_sim;


/*Structure for robot simulation list */
typedef struct sim_list{
    t_sim *data;/*Simulation data items*/
    int capacity;/*allocacted size*/
    int size;
}l_sim;

/* Initialization of the robot simulation list */
/* Post: list is initializes to capacity 10, size 0 */
void init_sim_list(l_sim * list);

/* Add one simulation record to the end of the list */
/* Reallocates memory (increase capacity by 10) if list is full */
void add_sim(l_sim * list, t_sim * sim);

/* Printing one simulation data to the screen */
void display_sim(const t_sim * sim);

/* Printing simulation list to the screen */
void display_sim_list(const l_sim * list);

/* Free memory allocated by simulation list data items (not the list record itself */
void clear_sim_list(l_sim * list);

/* Searches for simulation with given name at the list
 * Return index of proper record if proper name found, -1 otherwise */
int find_sim(const l_sim * list, int number);

/* Save simulation list to the given file name */
void save_sim_list(const l_sim * list, const char * fname);

/* Load simulation data from the given file name
 * Pre: list should be previously initialized.
 * Post: all records from the file will be added at the end of the list.
 */
void load_sim_list(l_sim * list, const char * fname);

/* Rank simulation data
 * Based on the  Test score */
void rank_sim(const l_sim * list, t_sim * sim);
#endif