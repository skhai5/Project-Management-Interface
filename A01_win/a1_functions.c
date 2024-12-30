/********* a1_functions.c ********

  Student Name 	= "Salma Khai"
  Student Number = "101301357"
*/
/********* a1_functions.c ********

  Student Name 	= "Salma Khai"
  Student Number = "101301357"
*/
/********* a1_functions.c ********

  Student Name 	= "Salma Khai"
  Student Number = "101301357"
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "a1_functions.h"
#include <string.h>

unsigned short int get_input_usi(void) {
    unsigned short value;
    int result;

    while (1) {
        result = scanf("%hu", &value);
        if (result == 1 && value >= 0) {
            while (getchar() != '\n'); // Clear the input buffer
            break;
        } else {
            while (getchar() != '\n'); // Clear the input buffer
            printf("Invalid input. Please enter a positive unsigned short integer: ");
        }
    }
    return value;
}

float get_input_f(void) {
    float value;
    int result;

    while (1) {
        printf("Enter a positive float: ");
        result = scanf("%f", &value);

        if (result == 1 && value > 0) {
            while (getchar() != '\n'); // Clear the input buffer
            break;
        } else {
            while (getchar() != '\n'); // Clear the input buffer
            printf("Invalid input. Please enter a positive float: ");
        }
    }
    return value;
}

void init_milestone(milestone_t *milestone_to_int, unsigned short int num_activities) {
    milestone_to_int->actual_cost = 0;
    milestone_to_int->actual_duration = 0;
    milestone_to_int->completed = false;
    for (int i = 0; i < num_activities; i++) {
        printf("Initializing activity %u: \n", i + 1);
        init_activity(&milestone_to_int->activity_list[i]);
    }
}

void init_activity(activity_t *activity_to_int) {
    activity_to_int->actual_duration = 0;
    activity_to_int->actual_cost = 0;
    printf("What is the planned hours: ");
    activity_to_int->planned_duration = get_input_usi();
    activity_to_int->planned_cost = activity_to_int->planned_duration * 30;
    activity_to_int->completed = false;
}

project_t init_project(char name[], milestone_t *milestone_list, int number_milestones, const int *number_activities) {
    project_t ret;
    memcpy(ret.name, name, 100); 
    int total_cost = 0;
    int total_hours = 0;
    for (int i = 0; i < number_milestones; i++) {
        for (int j = 0; j < number_activities[i]; j++) {
            total_cost += milestone_list[i].activity_list[j].planned_cost;
            total_hours += milestone_list[i].activity_list[j].planned_duration;
        }
    }
    double days = total_hours / 24.0f;
    ret.planned_cost = total_cost;
    ret.planned_duration = ceil(days);
    ret.actual_cost = 0;
    ret.actual_duration = 0;
    ret.completed = false;
    return ret;
}

void print_main_menu(void) {
    printf("Please select one of the following options: \n");
    printf("1. Update activity \n");
    printf("2. Print Stats \n");
    printf("3. Exit \n");
}

void print_milestone_stats(const milestone_t *list_milestones, int num_milestones, const int *number_activities) {
    for (int i = 0; i < num_milestones; i++) {
        float total_planned_cost = 0;
        int num_completed = 0, total_planned_duration = 0;
        for (int j = 0; j < number_activities[i]; j++) {
            total_planned_cost += list_milestones[i].activity_list[j].planned_cost;
            total_planned_duration += list_milestones[i].activity_list[j].planned_duration;
            if (list_milestones[i].activity_list[j].completed) {
                num_completed++;
            }
        }
        if (list_milestones[i].completed) {
            printf("Milestone completed: %s\n", list_milestones[i].name);

            if (list_milestones[i].actual_cost - total_planned_cost > 0) {
                printf("Milestone over budget: %.2f\n", list_milestones[i].actual_cost);
            } else if (list_milestones[i].actual_cost - total_planned_cost == 0) {
                printf("Milestone was perfectly budgeted\n");
            } else {
                printf("Milestone was under budget: %.2f\n", -1 * (list_milestones[i].actual_cost - total_planned_cost));
            }
        } else {
            printf("Milestone incomplete: %s\n", list_milestones[i].name);
            printf("Num completed: %u\n", num_completed);
            printf("Total planned duration: %d\n", total_planned_duration);
            printf("Total planned cost: %.2f\n", total_planned_cost);
        }
    }
}

void print_project_stats(project_t details, const milestone_t *list_milestones, int num_milestones, const int *number_activities) {
    printf("Project name: %s\n", details.name);
    if (details.completed) {
        printf("Project complete? Yes\n");
        if (details.actual_cost - details.planned_cost > 0) {
            printf("Project was over budget: %.2f dollars\n", details.actual_cost - details.planned_cost);
        } else if (details.actual_cost - details.planned_cost == 0) {
            printf("Project was properly budgeted\n");
        } else {
            printf("Project was under budget: %.2f dollars\n", (details.actual_cost - details.planned_cost) * -1);
        }

        if (details.actual_duration - details.planned_duration > 0) {
            printf("Project was delayed: %d days\n", details.actual_duration - details.planned_duration);
        } else if (details.actual_duration - details.planned_duration == 0) {
            printf("Project was on time\n");
        } else {
            printf("Project was early: %d days\n", (details.actual_duration - details.planned_duration) * -1);
        }
    } else {
        printf("Project complete? No\n");
        print_milestone_stats(list_milestones, num_milestones, number_activities);
    }
}

void update_activity(activity_t *activity_to_update) {
    printf("Update Actual hours: ");
    activity_to_update->actual_duration = get_input_usi();

    printf("Enter the actual cost: ");
    activity_to_update->actual_cost = get_input_f();

    printf("Is this completed? 1 for yes, 0 for no: ");
    unsigned short int status_activity = get_input_usi();
    activity_to_update->completed = (status_activity != 0);
}

void update_milestone(milestone_t *milestone_to_update, int activities_in_milestone) {
    bool all_complete = true;
    milestone_to_update->actual_cost = 0.0f;
    milestone_to_update->actual_duration = 0;

    for (int i = 0; i < activities_in_milestone; i++) {
        if (!milestone_to_update->activity_list[i].completed) {
            all_complete = false;
        }
        milestone_to_update->actual_cost += milestone_to_update->activity_list[i].actual_cost;
        milestone_to_update->actual_duration += milestone_to_update->activity_list[i].actual_duration;
    }

    milestone_to_update->completed = all_complete;
    if (all_complete) {
        printf("All activities in milestone are completed.\n");
        printf("Actual cost: %.2f\n", milestone_to_update->actual_cost);
        printf("Actual duration: %u\n", milestone_to_update->actual_duration);
    }
}

void update_project(const milestone_t *milestone_array, int num_milestones, const int *number_activities, project_t *my_project) {
    bool all_complete = true;
    my_project->actual_cost = 0.0f;
    my_project->actual_duration = 0;

    for (int i = 0; i < num_milestones; i++) {
        if (!milestone_array[i].completed) {
            all_complete = false;
        }
        my_project->actual_cost += milestone_array[i].actual_cost;
        my_project->actual_duration += milestone_array[i].actual_duration;
    }

    if (all_complete) {
        my_project->completed = true;
        printf("Project is now complete.\n");
    }
}
