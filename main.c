#include "robot.h"
#include "simulation.h"

/* File name of the data records */
#define ROBOTS_SRC "Robots.txt"
/*Simulation data dump file*/

#define SIM_DUMP "Simulation.txt"

int main()
{
    /* robot data*/
    t_robot  rbt;
    t_list list;
    /*Simulation data*/
    t_sim smt;
    l_sim sim;

    /* Initialize robot list */
    init_robot_list(&list);

    /*Initialize simulation list*/
    init_sim_list(&sim);

    /* Load robot list from the file at startup */
    load_robot_list(&list, ROBOTS_SRC);

    /*load previous simulation data*/
    load_sim_list(&sim, SIM_DUMP);

    /*Display robot list after loading*/
    display_robot_list(&list);

    int  choice; /*Choice*/
    char name[NAME_LENGTH];/*Robot name*/
    int  index;/*Robot index*/

    do{
        /*Display menu items and get the user choice*/
        choice = get_menu_choice();
        switch (choice){
            case 1:/*Simulate robot vs human*/
                printf("Simulation of robot vs human feature has not been completed yet\n");
                display_robot_list(&list);
                printf(" Select >");
                /*TODO:
                 * - get the robot data and perform the simulation */
                break;
            case 2:/*Display the simulation results*/
                display_sim_list(&sim);
                break;
            case 3:/*Display winners*/
                if(sim.size == 0){/*simulation list is empty*/
                    perror("No winners yet, no test has been ran\n");
                }else{
                    /*rank simulation data*/
                    t_sim win;
                    rank_sim(&sim, &win);
                    display_sim(&win);
                }
                break;
            case 4:/*Search robot by name*/
                printf("\n\n--- Search Robot by Name ---\n");
                printf("Please enter robot name: ");
                scanf("%[^\n]%*c", name);
                /* looking for robot by name */
                index = find_robot(&list, name);
                if (index == -1) {
                    printf("Robot name %s not found!\n\n", name);
                }
                else {
                    /* Display Robot record */
                    display_robot(&list.data[index]);
                }
                break;
            case 5:/*Input/Update robot information*/
                printf("\n\n--- MODIFY ROBOT INFORMATION ---\n");
                char resp,ch;
                do {
                    printf("Would you like to input(i) or modify(m)? (i/m) : ");
                    scanf("%c", &resp);

                    /* skip rest of the line */
                    while ((ch = getc(stdin)) && ch != '\n') {}

                } while (!(resp == 'i' || resp == 'm'));
                if(resp == 'i'){
                    read_robot(&rbt);
                    add_robot(&list, &rbt);
                }else{
                    printf("Please enter robot name: ");
                    scanf("%[^\n]%*c", name);
                    /* looking for robot by name */
                    index = find_robot(&list, name);
                    if (index == -1) {
                        printf("Robot name %s not found!\n\n", name);
                    }
                    else {
                        /* Display Robot record */
                        display_robot(&list.data[index]);
                        printf("\nEnter new record data\n");
                        /* Enter new data record */
                        read_robot(&list.data[index]);
                    }
                }
                break;
            case 6:/*Save all results*/
                save_sim_list(&sim, SIM_DUMP);
                break;
            case 7:/*Save robot information*/
                save_robot_list(&list, ROBOTS_SRC);
                break;
            default:/*Exit*/
                break;
        }
    }while(choice != 0);



    /* Save list into the file before exiting */
    save_robot_list(&list, ROBOTS_SRC);

    /* clear allocated memory */
    clear_robot_list(&list);
    clear_sim_list(&sim);
    return 0;
}