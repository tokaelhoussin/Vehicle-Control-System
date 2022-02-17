/*
 * project1.c
 *
 *  Created on: Sep 11, 2021
 *      Author: as
 */

/*
 * Projct.c
 *
 *  Created on: Sep 9, 2021
 *      Author: as
 */
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1
//global variables
char x;//input
int quit=1;//flag
char y='a';//input_sensors //initialized to a
char traffic_color;

//functions prototype
void main_menu(void);
void sensors_set_menu(void);
void Input(char *input);
void traffic_light(void);
void room_temp(void);
void engine_temp(void);
void print_state(void);


struct current_vehicle_state{
    char Engine_state[4];
    char AC[4];
    float Vehicle_speed;
    float Room_Temp;
    char Engine_Temperature_Controller_State[4];
    float Engine_Temperature;
}vehicle1;



int main(){
	//initialization
    strcpy(vehicle1.Engine_state,"ON");
    strcpy(vehicle1.AC,"ON");
    vehicle1.Vehicle_speed=100;
    vehicle1.Room_Temp=25;
    strcpy(vehicle1.Engine_Temperature_Controller_State,"ON");
    vehicle1.Engine_Temperature=100;

    main_menu();
	scanf(" %c",&x);
	Input(&x);
	if(quit==0)
		return 0;
}


//functions definition
void main_menu(void){
	printf("a. Turn on the vehicle engine\n");
	fflush(stdout);
	printf("b. Turn off the vehicle engine\n");
	fflush(stdout);
	printf("c. Quit the system\n");
	fflush(stdout);
}
void sensors_set_menu(void){
	char x='b';//initialization to show the main menu again if choose to turn off
	printf("\n");
	fflush(stdout);
	printf("a. Turn off the engine\n");
	fflush(stdout);
	printf("b. Set the traffic light color\n");
	fflush(stdout);
	printf("c. Set the room temperature (Temperature Sensor)\n");
	fflush(stdout);
#if WITH_ENGINE_TEMP_CONTROLLER==1
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
	fflush(stdout);
#endif
	scanf(" %c",&y);
	if(y=='a')
        Input(&x);
	else if(y=='b'){
          scanf(" %c",&traffic_color);
          traffic_light();
	}
	else if(y=='c'){
         scanf(" %f",&vehicle1.Room_Temp);
         room_temp();
	}
	else if(y=='d'){
		scanf(" %f",&vehicle1.Engine_Temperature);
		engine_temp();
	}
}

void Input(char *input){
	if(*input=='c'){
			printf("Quit the system\n");
			fflush(stdout);
			quit=0;
		}
	else if(*input=='b'&&y=='a'){
			printf("Turn off the vehicle engine\n");
			fflush(stdout);
			main_menu();
			scanf(" %c",&x);
			Input(&x);
		}
	if(*input=='a'){
			printf("Turn on the vehicle engine\n");
			fflush(stdout);
			sensors_set_menu();
	}
}
void traffic_light(void){
 if(traffic_color=='g'||traffic_color=='G')
	 vehicle1.Vehicle_speed=100;
 else if(traffic_color=='o'||traffic_color=='O')
 	     vehicle1.Vehicle_speed=30;
 else if(traffic_color=='r'||traffic_color=='R')
  	     vehicle1.Vehicle_speed=0;
 print_state();

}
void room_temp(void){
if(vehicle1.Room_Temp<10){
    strcpy(vehicle1.AC,"ON");
	vehicle1.Room_Temp=20;
}
else if(vehicle1.Room_Temp>30){
    strcpy(vehicle1.AC,"ON");
	vehicle1.Room_Temp=20;
}
else
    strcpy(vehicle1.AC,"OFF");
print_state();

}
void engine_temp(void){
#if WITH_ENGINE_TEMP_CONTROLLER==1

	if(vehicle1.Engine_Temperature<100){
	    strcpy(vehicle1.Engine_Temperature_Controller_State,"ON");
		vehicle1.Engine_Temperature=125;
	}
	else if(vehicle1.Engine_Temperature>150){
	    strcpy(vehicle1.Engine_Temperature_Controller_State,"ON");
		vehicle1.Engine_Temperature=125;
	}
	else
	    strcpy(vehicle1.Engine_Temperature_Controller_State,"OFF");
    print_state();
#endif
}
void print_state(void){
	if(vehicle1.Vehicle_speed==30){
	    strcpy(vehicle1.AC,"ON");
		vehicle1.Room_Temp=vehicle1.Room_Temp*(1.25)+1;
#if WITH_ENGINE_TEMP_CONTROLLER==1
	    strcpy(vehicle1.Engine_Temperature_Controller_State,"ON");
		vehicle1.Engine_Temperature=vehicle1.Engine_Temperature*(1.25)+1;
#endif
	}
	printf("Engine is %s\n",vehicle1.Engine_state);
	fflush(stdout);
	printf("AC is %s\n",vehicle1.AC);
	fflush(stdout);
	printf("Vehicle speed: %f Km/hr\n",vehicle1.Vehicle_speed);
	fflush(stdout);
	printf("Room Temperature: %f C\n",vehicle1.Room_Temp);
	fflush(stdout);
#if WITH_ENGINE_TEMP_CONTROLLER==1
	printf("Engine Temp Controller is %s\n",vehicle1.Engine_Temperature_Controller_State);
	fflush(stdout);
	printf("Engine Temperature: %f C\n",vehicle1.Engine_Temperature);
	fflush(stdout);
#endif
	sensors_set_menu();
}



