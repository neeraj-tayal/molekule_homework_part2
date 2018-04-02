#include "scheduler.h"

#define MAX_SCHEDULED_EVENTS 64
static struct _event event[MAX_SCHEDULED_EVENTS];
static uint8_t event_count=0;


//Include LOGGING_ENABLED while building by adding -D LOGGING_ENABLED in build command line
#ifdef LOGGING_ENABLED
    #define LOG printf
#else
    #define LOG(x,y) do {} while (0)
#endif

enum error_t create_event(uint8_t event_id, uint32_t start_time, uint32_t duration, void (*start_action), 
                    void (*stop_action))
{
    if(event_count>=MAX_SCHEDULED_EVENTS)
    {   
        printf("Cant create any more events\n");
        printf("Delete events to create more events\n");
	return E_MAX_EVENTS_ALREADY_CREATED;
    }
    if(event_id>=MAX_SCHEDULED_EVENTS)
    {
        LOG("Invalid event_id %u\n",event_id);
	return E_INVALID_EVENT_ID;
    }
    event[event_id].registered = false;
    event[event_id].event_id = event_id;
    event[event_id].start_time = start_time;
    event[event_id].scheduled_start_action = start_action;
    event[event_id].scheduled_stop_action = stop_action;
    event[event_id].duration = duration;
    event[event_id].registered = true;
    event_count++;
    LOG("Event %d created\n",event_id);
    return E_SUCCESS;
}

enum error_t delete_event(uint8_t event_id)
{
    if(event_id>=MAX_SCHEDULED_EVENTS)
    {    
	LOG("Invalid event_id %d\n",event_id);
	return E_INVALID_EVENT_ID;
    }
    event[event_id].registered = false;
    event[event_id].start_time = 0;
    event[event_id].duration =0;
    event[event_id].scheduled_start_action = 0;
    event[event_id].scheduled_stop_action = 0;
    event_count--;
    LOG("Event %d Deleted\n",event_id);
    return E_SUCCESS;
}

uint8_t get_available_event_id()
{
     for(int i = 0; i < MAX_SCHEDULED_EVENTS; i++)
     {
	 if(!event[i].registered)
	     return i;
     }
     return (uint8_t)E_MAX_EVENTS_ALREADY_CREATED;
}

bool is_event_registered(uint8_t event_id)
{
    if(!(event_id>=MAX_SCHEDULED_EVENTS))
	 return event[event_id].registered;
    return false;
}
void evaluate_and_execute_events(uint32_t cur_time){
	for(uint8_t i = 0; i<MAX_SCHEDULED_EVENTS; i++){
            if(event[i].registered)
	    {
	        if(event[i].start_time == cur_time && event[i].scheduled_start_action)
		    (*event[i].scheduled_start_action)();
                if((event[i].start_time + event[i].duration) == cur_time && event[i].scheduled_stop_action)
		    (*event[i].scheduled_stop_action)();
            }
	}
}
