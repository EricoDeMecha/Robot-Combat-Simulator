#include "simulation.h"

/*Function implementation*/


/* Initialization of the robot simulation list */
/* Post: list is initializes to capacity 10, size 0 */
void init_sim_list(l_sim * list){
    /* do nothing if list is null */
    if (list == NULL) return;

    list->capacity = 1;
    list->size = 0;
    list->data = (t_sim*) malloc (sizeof(t_sim) * (list->capacity));
}

/* Add one simulation record to the end of the list */
/* Reallocates memory (increase capacity by 10) if list is full */
void add_sim(l_sim * list, t_sim * sim) {
    t_sim * old_data;
    int i;

    /* do nothing if simulation is null or list is null */
    if (sim == NULL || list == NULL) return;

    /* If list is full */
    if (list->size == list->capacity) {
        /* save pointer of old data items */
        old_data = list->data;

        /* allocate new memory - increase capacity by 10 */
        list->capacity += 10;
        list->data = (t_sim*) malloc (sizeof(t_sim) * (list->capacity));

        /* copy all existing robot data records */
        for (i = 0; i < list->size; i++) {
            list->data[i].Test_ID = old_data[i].Test_ID;
            list->data[i].Robot_number = old_data[i].Robot_number;
            list->data[i].finish_line_distance = old_data[i].finish_line_distance;
            list->data[i].finish_line_time = old_data[i].finish_line_time;
            list->data[i].Strength = old_data[i].Strength;
            list->data[i].Test_score = old_data[i].Test_score;
        }

        /* free memory allocated by old data items */
        free(old_data);
    }

    /* copy robot data at the end of the list */
    list->data[list->size].Test_ID = sim->Test_ID;
    list->data[list->size].Robot_number = sim->Robot_number;
    list->data[list->size].finish_line_distance = sim->finish_line_distance;
    list->data[list->size].finish_line_time = sim->finish_line_time;
    list->data[list->size].Strength = sim->Strength;
    list->data[list->size].Test_score = sim->Test_score;

    /* increase list size */
    list->size++;
}

/* Printing one simulation data to the screen */
void display_sim(const t_sim* sim) {
    printf("Test ID          : %d\n", sim->Test_ID);
    printf("Robot number : %d\n", sim->Robot_number);
    printf("Finish Line distance : %d\n", sim->finish_line_distance);
    printf("Finish Line Time  : %d\n", sim->finish_line_time);
    printf("Strength  : %d\n", sim->Strength);
    printf("Test Score  : %d\n", sim->Test_score);
}


/* Printing simulation list to the screen */
void display_sim_list(const l_sim * list) {
    int i;

    /* do nothing if list is null */
    if (list == NULL) return;

    /* print table header */
    printf("----------------------------------------------------------------------\n");
    printf("%-30s %15s %15s %15s %15s %s\n", "Test ID", "Robot Number","Finish line Distance", "Finish line time",
           "Strength","Test Score");
    printf("----------------------------------------------------------------------\n");

    /* display list data */
    for (i = 0; i < list->size; i++) {
        printf("%-30d %15d %15d %15d %15d %15d", list->data[i].Test_ID, list->data[i].Robot_number, list->data[i].finish_line_distance,
               list->data[i].finish_line_time,list->data[i].Strength,list->data[i].Test_score);
    }
    printf("----------------------------------------------------------------------\n\n");
}

/* Searches for simulation with given name at the list
 * Return index of proper record if proper name found, -1 otherwise */
int find_sim(const l_sim * list, const int number) {
    int i;

    if (list == NULL)
        return -1;

    for (i = 0; i < list->size; i++) {
        if (list->data[i].Robot_number == number)
            return i;       /* robot number found */
    }
    return -1; /* number not found */
}

/* Free memory allocated by simulation list data items (not the list record itself */
void clear_sim_list(l_sim* list) {
    if (list == NULL) return;

    free(list->data);
    list->capacity = 0;
    list->size = 0;
}

/* Save robot list to the given file name */
void save_sim_list(const l_sim * list, const char * fname) {
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
        fprintf(fp,"%d,%d,%d,%d,%d,%d\n", list->data[i].Test_ID,list->data[i].Robot_number,
                list->data[i].finish_line_distance,list->data[i].finish_line_time, list->data[i].Strength,
                list->data[i].Test_score);
    }

    /* close resulting file */
    fclose(fp);
}

/* Load simulation data from the given file name
 * Pre: list should be previously initialized.
 * Post: all records from the file will be added at the end of the list.
 */
void load_sim_list(l_sim * list, const char * fname) {
    FILE * fp;
    t_sim smt;
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
    while (fscanf(fp, "%d", smt.Test_ID) == 1 && !feof(fp)) {
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &smt.Robot_number);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &smt.finish_line_distance);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &smt.finish_line_time);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &smt.Strength);
        fscanf(fp,"%c", &ch); /* skip ',' */
        fscanf(fp,"%d", &smt.Test_score);

        /* skip '\n' */
        while (!feof(fp) && ((ch = fgetc(fp)) != '\n')) {}

        /* Add robot at the end of the list */
        add_sim(list, &smt);
    }

    /* close source file */
    fclose(fp);
}

/* Rank simulation data
 * Based on the  Test score */
void rank_sim(const l_sim * list, t_sim * sim){
    if (list == NULL)
        return;
    int max_score = list->data[0].Test_score;
    for (int i = 0; i < list->size; i++) {
        if (list->data[i].Robot_number > max_score){
            max_score = list->data[i].Robot_number;
        }
    }
    /* copy all existing robot data records */
    for (int i = 0; i < list->size; i++) {
        /*To be be completed*/
    }
}