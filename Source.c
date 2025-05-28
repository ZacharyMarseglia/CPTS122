#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function that reads and parses data; stores in array
void read_file(FILE* infile, FitbitData todays_data[NUM_MINUTES])
{
    int counter = 0;
    while (!feof(infile) && counter < NUM_MINUTES)
    {
        // Reads in data
        char holder[100]; // Increase buffer size if needed
        char delim[2] = ",";
        if (fgets(holder, sizeof(holder), infile) == NULL) {
            break; // Stop if fgets fails
        }

        // Parses and stores the data
        char* temp = strtok(holder, delim);
        if (temp) strcpy(todays_data[counter].minute, temp);

        temp = strtok(NULL, delim);
        if (temp) todays_data[counter].calories = atof(temp);

        temp = strtok(NULL, delim);
        if (temp) todays_data[counter].distance = atof(temp);

        temp = strtok(NULL, delim);
        if (temp) todays_data[counter].floors = atoi(temp);

        temp = strtok(NULL, delim);
        if (temp) todays_data[counter].heartRate = atoi(temp);

        temp = strtok(NULL, delim);
        if (temp) todays_data[counter].steps = atoi(temp);

        temp = strtok(NULL, delim);
        if (temp) todays_data[counter].sleepLevel = atoi(temp);

        counter++;
    }
}

/*************************************************************
* Function: compute_total_calories                         *
* Description: Computes the total calories burned based on  *
*              the Fitbit data for the day.                *
* Input parameters: todays_data - array of Fitbit data     *
* Returns: Total calories burned                          *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
double compute_total_calories(FitbitData todays_data[NUM_MINUTES])
{
    double total_calories = 0.0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        total_calories += todays_data[i].calories;
    }
    return total_calories;
}

/*************************************************************
* Function: compute_distance_walked                        *
* Description: Calculates the total distance walked based on*
*              the Fitbit data for the day.                *
* Input parameters: todays_data - array of Fitbit data     *
* Returns: Total distance walked in miles                  *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
double compute_distance_walked(FitbitData todays_data[NUM_MINUTES])
{
    double total_miles = 0.0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        total_miles += todays_data[i].distance;
    }
    return total_miles;
}

/*************************************************************
* Function: compute_floors_walked                          *
* Description: Computes the total number of floors climbed *
*              based on the Fitbit data for the day.       *
* Input parameters: todays_data - array of Fitbit data     *
* Returns: Total number of floors climbed                  *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
unsigned int compute_floors_walked(FitbitData todays_data[NUM_MINUTES])
{
    unsigned int total_floors = 0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        total_floors += todays_data[i].floors;
    }
    return total_floors;
}

/*************************************************************
* Function: compute_steps_taken                            *
* Description: Computes the total number of steps taken based*
*              on the Fitbit data for the day.             *
* Input parameters: todays_data - array of Fitbit data     *
* Returns: Total number of steps taken                     *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
unsigned int compute_steps_taken(FitbitData todays_data[NUM_MINUTES])
{
    unsigned int total_steps = 0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        total_steps += todays_data[i].steps;
    }
    return total_steps;
}

/*************************************************************
* Function: compute_average_heartrate                      *
* Description: Computes the average heart rate based on    *
*              the Fitbit data for the day.                *
* Input parameters: todays_data - array of Fitbit data     *
* Returns: Average heart rate                              *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
double compute_average_heartrate(FitbitData todays_data[NUM_MINUTES])
{
    double average_sum = 0.0;
    int count = 0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        if (todays_data[i].heartRate != 0)
        {
            average_sum += todays_data[i].heartRate;
            count++;
        }
    }
    return (count > 0) ? (average_sum / count) : 0.0;
}

/*************************************************************
* Function: compute_max_steps                              *
* Description: Finds the maximum number of steps taken in  *
*              any single minute based on the Fitbit data  *
*              for the day.                               *
* Input parameters: todays_data - array of Fitbit data     *
* Returns: Maximum number of steps taken in a minute       *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
unsigned int compute_max_steps(FitbitData todays_data[NUM_MINUTES])
{
    unsigned int max_steps = 0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        if (todays_data[i].steps > max_steps)
        {
            max_steps = todays_data[i].steps;
        }
    }
    return max_steps;
}

/*************************************************************
* Function: compute_worst_sleep                            *
* Description: Computes the worst sleep period between     *
*              specified start and end times based on the  *
*              Fitbit data for the day.                    *
* Input parameters: start_time - start of the period,      *
*                   end_time - end of the period,          *
*                   todays_data - array of Fitbit data     *
* Returns: None                                            *
* Preconditions: Array must be populated with Fitbit data  *
* Postconditions: None                                     *
*************************************************************/
void compute_worst_sleep(char* start_time, char* end_time, FitbitData todays_data[NUM_MINUTES])
{
    int max_start = 0, max_end = 0, max_sum = 0;
    int current_sum = 0;
    for (int i = 0; i < NUM_MINUTES; i++)
    {
        if (todays_data[i].sleepLevel > 1)
        {
            int start = i;
            current_sum = 0;
            while (i < NUM_MINUTES && todays_data[i].sleepLevel > 1)
            {
                current_sum += todays_data[i].sleepLevel;
                i++;
            }
            if (current_sum > max_sum)
            {
                max_start = start;
                max_end = i - 1;
                max_sum = current_sum;
            }
        }
    }
    strncpy(start_time, todays_data[max_start].minute, 9);
    start_time[9] = '\0'; // Ensure null-terminated strings
    strncpy(end_time, todays_data[max_end].minute, 9);
    end_time[9] = '\0';   // Ensure null-terminated strings
}
