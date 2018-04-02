#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "scheduler.h"

void turnOnSprinklerA(){
        printf("Sprinkler A turned on\r\n");
}

void turnOnSprinklerB(){
        printf("Sprinkler B turned on\r\n");
}
void turnOffSprinklerA(){
        printf("Sprinkler A turned off\r\n");
}

void turnOffSprinklerB(){
        printf("Sprinkler B turned off\r\n");
}
void init(){
        // Test cases can be added here

	// test events creation
	create_event(1,3,2, &turnOnSprinklerA, &turnOffSprinklerA);
	create_event(0,4,5, &turnOnSprinklerB, &turnOffSprinklerB);
	// test optional config. of stop function
	create_event(0,4,5, &turnOnSprinklerB, 0);
	// test events deletion
        delete_event(1);
        delete_event(3);
        // test invalid event_id creation
        create_event(100,3,2,&turnOnSprinklerA, &turnOffSprinklerA);
        // test available get_id
        uint8_t e_id = get_available_event_id();
        printf("Available event_id %u\n",get_available_event_id());
	create_event(e_id,1,1, &turnOnSprinklerB, &turnOffSprinklerB);
}


uint32_t get_time(){
	static uint32_t time=0;
	return time++;
}

void test_evaluate_and_execute_events(){
	printf("Testing action triggers\r\n");	
        init();	
        for(uint32_t time=get_time(); time<10; time=get_time()){
		printf("Time is %u\r\n", time);
                evaluate_and_execute_events(time);
        }
	printf("\r\n");
	
}
void test_max_event_creation(){
	printf("Testing max event creation response\r\n");
	for(uint8_t i=2; i<66; i++){
		bool create_event_response = create_event(i,3,2, &turnOnSprinklerA, &turnOffSprinklerA);
		if(i>=62) printf("Event %u returned: %s\r\n", i, create_event_response ? "false":"true");
	}
	printf("\r\n");
}
int main(){
	test_evaluate_and_execute_events();
	test_max_event_creation();	
}


