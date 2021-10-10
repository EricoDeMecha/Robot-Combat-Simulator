#ifndef ROBOT_H
#define ROBOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum name length */
#define NAME_LENGTH 30


/* Structure for each robot data */
typedef struct s_robot {
    char Robot_name[NAME_LENGTH];
    int  Robot_number;
    int  Year_manufactured;
    float Top_speed;
    float  Mass;
    int Best_Score;
} t_robot;


/* Structure for all robot list */
typedef struct s_list {
    t_robot *data;  /* pointer to the robot data items */
    int capacity;        /* allocated size for items array */
    int size;            /* actual number of items at the list */
} t_list;



/* Function prototypes */

/* Initialization of the robot list */
/* Post: list is initializes to capacity 10, size 0 */
void init_robot_list(t_list * list);



/* Load robot list from the given file name
 * Pre: list should be previously initialized.
 * Post: all records from the file will be added at the end of the list.
 */
void load_robot_list(t_list * list, const char * fname);

/* Add one robot record to the end of the list */
/* Reallocates memory (increase capacity by 10) if list is full */
void add_robot(t_list * list, t_robot * rbt);

/* Searches for robot with given name at the list
 * Return index of proper record if proper name found, -1 otherwise */
int find_robot(const t_list * list, const char * name);

/* Reading one robot data from the user */
/* Post: t_robot rbt is filled with data entered by the user */
void read_robot(t_robot * rbt);

/* Printing one robot data to the screen */
void display_robot(const t_robot * rbt);

/* Printing robot list to the screen */
void display_robot_list(const t_list * list);

/* Free memory allocated by robot list data items (not the list record itself */
void clear_robot_list(t_list * list);

/* Save robot list to the given file name */
void save_robot_list(const t_list * list, const char * fname);

/* Delete robot record at given index from the list */
/* For valid index (>=0 and < list->size) shifts all ascending records, decreases list size*/
/* If index is invalid (< 0 or > list->size) do nothing  */
void delete_robot(t_list * list, int index);

/* Display main menu, get user entry, validate user entry, returns valid menu number */
int get_menu_choice();

#endif