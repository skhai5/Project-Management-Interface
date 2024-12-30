/********* main.c ********
  Student Name 	= "Salma Khai"
  Student Number = "101301357"
*/

#include <stdlib.h>
#include <stdio.h>
#include "a1_functions.h"
#define MAX_MILESTONES 5

int main() {
    printf("***Welcome to ABC Company Project Management Application***\n");

    char proj_name[100];
    int num_milestones;

    // Get project name and number of milestones
    printf("Enter the project name: ");
    scanf("%99s", proj_name);
    while (getchar() != '\n');  // Clear input buffer

    do {
        printf("Enter the number of milestones (up to %d): ", MAX_MILESTONES);
        if (scanf("%d", &num_milestones) != 1 || num_milestones < 0 || num_milestones > MAX_MILESTONES) {
            while (getchar() != '\n');  // Clear invalid input
            printf("Invalid input. Please enter a number between 0 and %d.\n", MAX_MILESTONES);
        } else {
            break;
        }
    } while (1);

    milestone_t milestones[MAX_MILESTONES];
    int milestone_activities[MAX_MILESTONES];

    // Initialize milestones and activities
    for (int i = 0; i < num_milestones; i++) {
        printf("***Initializing Milestone %d***\n", i + 1);
        printf("Enter the number of activities: ");
        milestone_activities[i] = get_input_usi();

        printf("Enter milestone ID: ");
        while (1) {
            milestones[i].id = get_input_usi();
            int is_unique = 1;
            for (int j = 0; j < i; j++) {
                if (milestones[i].id == milestones[j].id) {
                    printf("ID not unique. Enter a different ID: ");
                    is_unique = 0;
                    break;
                }
            }
            if (is_unique) break;
        }

        printf("Enter milestone name: ");
        scanf("%99s", milestones[i].name);
        while (getchar() != '\n');  // Clear input buffer

        // Initialize activities
        for (int k = 0; k < milestone_activities[i]; k++) {
            printf("Enter activity name: ");
            scanf("%99s", milestones[i].activity_list[k].name);
            while (getchar() != '\n');  // Clear input buffer

            printf("Enter activity ID: ");
            while (1) {
                milestones[i].activity_list[k].id = get_input_usi();
                int found = 0;
                for (int m = 0; m <= i && !found; m++) {
                    for (int n = 0; n < (m == i ? k : milestone_activities[m]); n++) {
                        if (milestones[m].activity_list[n].id == milestones[i].activity_list[k].id) {
                            printf("ID not unique. Enter a different ID: ");
                            found = 1;
                            break;
                        }
                    }
                }
                if (!found) break;
            }
        }
        init_milestone(&milestones[i], milestone_activities[i]);
    }

    project_t project1 = init_project(proj_name, milestones, num_milestones, milestone_activities);

    int exit = 0;
    do {
        print_main_menu();
        int user_input = get_input_usi();

        switch (user_input) {
            case 1: {
                printf("Milestones and Activities:\n");
                for (int i = 0; i < num_milestones; i++) {
                    for (int j = 0; j < milestone_activities[i]; j++) {
                        printf("Milestone %d, Activity %d, ID %u, Name: %s\n", i, j, milestones[i].activity_list[j].id, milestones[i].activity_list[j].name);
                    }
                }

                printf("Enter the ID of the activity to update: ");
                unsigned short int selected_id;
                int found = 0, mil = 0, act = 0;
                do {
                    selected_id = get_input_usi();
                    for (int i = 0; i < num_milestones; i++) {
                        for (int j = 0; j < milestone_activities[i]; j++) {
                            if (milestones[i].activity_list[j].id == selected_id) {
                                found = 1;
                                mil = i;
                                act = j;
                                break;
                            }
                        }
                        if (found) break;
                    }
                    if (!found) printf("ID not found, try again: ");
                } while (!found);

                update_activity(&milestones[mil].activity_list[act]);
                update_milestone(&milestones[mil], milestone_activities[mil]);
                update_project(milestones, num_milestones, milestone_activities, &project1);
                break;
            }
            case 2:
                printf("Project Statistics:\n");
                print_project_stats(project1, milestones, num_milestones, milestone_activities);
                break;
            case 3:
                printf("Exiting program.\n");
                exit = 1;
                break;
            default:
                printf("Invalid choice. Please choose between 1 and 3.\n");
                break;
        }
    } while (!exit);

    return EXIT_SUCCESS;
}
