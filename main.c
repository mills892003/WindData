//  Created by Milan Patel on 5/1/18.
//  Copyright © 2018 Milan Patel. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SITES 5
#define DAYS_SITE 7

typedef struct{                 //Define structure type for measured data
    int site_id_num;
    int wind_speed;
    int day_of_month;
    int temperature;
} measured_data_t;

typedef struct{                 //Define structure type for calculated data
    int site_id_num;
    int low_temp, high_temp;
    int avg_speed;
} calculated_data_t;


int main(void) {
    measured_data_t data[SITES*DAYS_SITE];      //initiate structures
    calculated_data_t calculate[SITES];
    int i=0, j=0;
    
    FILE *inventoryp;                           //Open data file
    inventoryp = fopen("data.txt", "r");
    
    for(i=0; i<(SITES*DAYS_SITE); ++i){         //Scan in data to measured data structure
        fscanf(inventoryp, "%d%d%d%d", &data[i].site_id_num, &data[i].day_of_month, &data[i].wind_speed, &data[i].temperature);
    }
    
    for(j=0; j<SITES; ++j){                     //Copy over data and initiate calculated data
        calculate[j].site_id_num = data[j*DAYS_SITE].site_id_num;
        calculate[j].low_temp=50;
        calculate[j].high_temp=0;
        calculate[j].avg_speed=0;
    }
    
    for(i=0; i<(SITES*DAYS_SITE);++i){          //set low and high temps for sites
        for(j=0; j<SITES; ++j){
            if(calculate[j].site_id_num==data[i].site_id_num){
                if(calculate[j].low_temp>data[i].temperature){
                    calculate[j].low_temp = data[i].temperature;
                }
                if(calculate[j].high_temp<data[i].temperature){
                    calculate[j].high_temp = data[i].temperature;
                }
                calculate[j].avg_speed=calculate[j].avg_speed + data[i].wind_speed;     //Add sum for avg speed
            }
        }
    }
    
    for(j=0;j<SITES; ++j){
        calculate[j].avg_speed = calculate[j].avg_speed / DAYS_SITE;        // set avg speed
    }
    
    
    
    
    int variation[SITES];
    int site_high_average=0, site_high_variation=0;
    int high_average=0, high_variation=0;
    
    for(j=0; j<SITES; ++j){
        if(calculate[j].avg_speed > high_average){                      // Set high averages
            high_average = calculate[j].avg_speed;
            site_high_average = calculate[j].site_id_num;
        }
        variation[j] = calculate[j].high_temp - calculate[j].low_temp;
        if(variation[j]>high_variation){                                // Set high variation
            high_variation = variation[j];
            site_high_variation = calculate[j].site_id_num;
        }
    }
    
    printf("\nThe site with the highest average wind speed is: %d \n", site_high_average);
    printf("The site with the greatest variation in temperature is: %d \n", site_high_variation);

fclose(inventoryp);                     //close data file
    
    return (0);
}
