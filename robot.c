#include "robot.h"

/* Function implementations */

/* Initialization of the robot list */
/* Post: list is initializes to capacity 10, size 0 */
void init_robot_list(t_list * list) {
    /* do nothing if list is null */
    if (list == NULL) return;

    list->capacity = 1;
    list->size = 0;
    list->data = (t_robot*) malloc (sizeof(t_robot) * (list->capacity));
}

/* Load robot list from the given file name
 * Pre: list should be previously initialized.
 * Post: all records from the file will be added at the end of the list.
 */
void load_robot_list(t_list * list, const char * fname) {
    FILE * fp;
    t_robot rbt;
    char ch;

    /* do nothing if list pointer is null */
    if (list == NULL) return;

    /* Try to open file with given name for reading */
    fp = fopen(fname, "r");
    if (!fp) {
        printf("Can't open file %s for reading\n!", fname);
        return;
    }

    /* load robot data list: one record per line separated by commas */
    while (fscanf(fp, "%[^,]%*c", rbt.Robot_name) == 1 && !feof(fp)) {
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &rbt.Robot_number);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &rbt.Year_manufactured);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%f", &rbt.Top_speed);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%f", &rbt.Mass);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &rbt.Best_Score);

        /* skip '\n' */
        while (!feof(fp) && ((ch = fgetc(fp)) != '\n')) {}

        /* Add robot at the end of the list */
        add_robot(list, &rbt);
    }

    /* close source file */
    fclose(fp);
}

/* Add one robot record to the end of the list */
/* Reallocates memory (increase capacity by 10) if list is full */
void add_robot(t_list * list, t_robot * rbt) {
    t_robot * old_data;
    int i;

    /* do nothing if robot is null or list is null */
    if (rbt == NULL || list == NULL) return;

    /* If list is full */
    if (list->size == list->capacity) {
        /* save pointer of old data items */
        old_data = list->data;

        /* allocate new memory - increase capacity by 10 */
        list->capacity += 10;
        list->data = (t_robot*) malloc (sizeof(t_robot) * (list->capacity));

        /* copy all existing robot data records */
        for (i = 0; i < list->size; i++) {
            strcpy(list->data[i].Robot_name, old_data[i].Robot_name);
            list->data[i].Robot_number = old_data[i].Robot_number;
            list->data[i].Year_manufactured = old_data[i].Year_manufactured;
            list->data[i].Top_speed = old_data[i].Top_speed;
            list->data[i].Mass = old_data[i].Mass;
            list->data[i].Best_Score = old_data[i].Best_Score;
        }

        /* free memory allocated by old data items */
        free(old_data);
    }

    /* copy robot data at the end of the list */
    strcpy(list->data[list->size].Robot_name, rbt->Robot_name);
    list->data[list->size].Robot_number = rbt->Robot_number;
    list->data[list->size].Year_manufactured = rbt->Year_manufactured;
    list->data[list->size].Top_speed = rbt->Top_speed;
    list->data[list->size].Mass = rbt->Mass;
    list->data[list->size].Best_Score = rbt->Best_Score;

    /* increase list size */
    list->size++;
}

/* Searches for robot with given name at the list
 * Return index of proper record if proper name found, -1 otherwise */
int find_robot(const t_list * list, const char * name) {
    int i;

    if (list == NULL)
        return -1;

    for (i = 0; i < list->size; i++) {
        if (strcmp(list->data[i].Robot_name, name) == 0)
            return i;       /* robot name found */
    }
    return -1; /* name not found */
}

/* Reading one robot data from the user */
/* Post: t_robot rbt is filled with data entered by the user */
void read_robot(t_robot * rbt) {
    char ch;

    /* do nothing if rbt is null */
    if (rbt == NULL) return;

    printf("Please enter robot name: ");
    scanf("%[^\n]%*c", rbt->Robot_name);
    printf("Robot number  : ");
    scanf("%d", &(rbt->Robot_number));
    printf("Year of manufacture : ");
    scanf("%d", &(rbt->Year_manufactured));
    printf("Top speed  : ");
    scanf("%f", &(rbt->Top_speed));
    printf("Mass  : ");
    scanf("%f", &(rbt->Mass));
    printf("Robot's Best Score  : ");
    scanf("%d", &(rbt->Best_Score));
    /* skip rest of the line */
    while ((ch = getc(stdin)) && ch != '\n') {}
}

/* Printing one robot data to the screen */
void display_robot(const t_robot * rbt) {
    printf("Name          : %s\n", rbt->Robot_name);
    printf("Robot number : %d\n", rbt->Robot_number);
    printf("Year of Manufacture : %d\n", rbt->Year_manufactured);
    printf("Top_speed  : %.3f\n", rbt->Top_speed);
    printf("Mass  : %.3f\n", rbt->Top_speed);
    printf("Best Score  : %d\n", rbt->Best_Score);
}

/* Printing robot list to the screen */
void display_robot_list(const t_list * list) {
    int i;

    /* do nothing if list is null */
    if (list == NULL) return;

    /* print table header */
    printf("----------------------------------------------------------------------\n");
    printf("%-30s %15s %15s %15s %15s %s\n", "Robot Name", "Robot Number","Year of Manufacture", "Top Speed",
           "Mass","Robot Best Score");
    printf("----------------------------------------------------------------------\n");

    /* display list data */
    for (i = 0; i < list->size; i++) {
        printf("%-30s %15d %15d %15f %15f %15d", list->data[i].Robot_name, list->data[i].Robot_number, list->data[i].Year_manufactured,
               list->data[i].Top_speed,list->data[i].Mass,list->data[i].Best_Score);
    }
    printf("----------------------------------------------------------------------\n\n");
}

/* Free memory allocated by robot list data items (not the list record itself */
void clear_robot_list(t_list * list) {
    if (list == NULL) return;

    free(list->data);
    list->capacity = 0;
    list->size = 0;
}

/* Save robot list to the given file name */
void save_robot_list(const t_list * list, const char * fname) {
    FILE * fp;
    int i;

    /* do nothing if list is null */
    if (list == NULL) return;

    /* Try to open file with given name for writing */
    fp = fopen(fname, "w");
    if (!fp) {
        printf("Can't open file %s for writing\n!", fname);
        return;
    }

    /* save robot data list: one record per line separated by commas */
    for (i = 0; i < list->size; i++) {
        fprintf(fp,"%s,%d,%d,%f,%f,%d\n", list->data[i].Robot_name,list->data[i].Robot_number,
                list->data[i].Year_manufactured,list->data[i].Top_speed, list->data[i].Mass,list->data[i].Best_Score);
    }

    /* close resulting file */
    fclose(fp);
}

/* Delete robot record at given index from the list */
/* For valid index (>=0 and < list->size) shifts all ascending records, decreases list size*/
/* If index is invalid (< 0 or > list->size) do nothing  */
void delete_robot(t_list * list, int index) {
    int i;

    /* return if index is invalid or list is NULL */
    if (list == NULL || index < 0 || index >= list->size)
        return;

    /* shift all records after index by one position to the left */
    for (i = index; i < list->size - 1; i++) {
        strcpy(list->data[i].Robot_name, list->data[i + 1].Robot_name);
        list->data[i].Robot_number = list->data[i + 1].Robot_number;
        list->data[i].Year_manufactured = list->data[i + 1].Year_manufactured;
        list->data[i].Top_speed = list->data[i + 1].Top_speed;
        list->data[i].Mass = list->data[i + 1].Mass;
        list->data[i].Best_Score = list->data[i + 1].Best_Score;
    }

    /* update list size */
    list->size--;
}

/* Display main menu, get user entry, validate user entry, returns valid menu number */
int get_menu_choice() {
    int choice, ch;

    printf("\n\n-----------------\n");
    printf("ROBOT COMBAT SIM MENU\n");
    printf("1. Simulate a robot against human component\n");
    printf("2. Display Simulation results\n");
    printf("3. Display Winners\n");
    printf("4. Search a robot by robot_name\n");
    printf("5. Input/update robot information\n");
    printf("6. Save all results\n");
    printf("7. Save robot information\n");
    printf("0. Exit Program\n");

    printf("> ");
    scanf("%d", &choice);
    while (choice < 0 || choice > 7) {
        printf("Invalid choice. Reenter please > ");
        scanf("%d", &choice);
    }
    /* skip '\n' */
    while ((ch = fgetc(stdin)) != '\n') {}

    return choice;
}

