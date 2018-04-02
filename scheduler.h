#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*Assumptions/Constraints/Improvements
1. No more than 64 events can be created
2. Static memory allocation (array data structure) is used for handling the events 
(Time Complexity for searching O(1))
3. Memory for 64 events can be statically allocated i.e. we have that much memory available
4. Client not able to override the existing event without deleting the existing event first
5. Linked List can be used if we know number of events will be fewer than Max at the cost of 
Time Complexity of O(n) for searching or removing any event
6. Hashing function can be formed to create event_id in the library itself 
rather than relying on user to pass the right event_id
7. Circular array can be used if we don't want user to delete the events when max events are scheduled
8. Can add another feature to let user modify the existing event config. by simply adding
another bool flag force_override in create_event function
*/

typedef void (*action)();
struct _event
{
    uint8_t event_id;
    uint32_t start_time;
    action scheduled_start_action;
    uint32_t duration;//Assumption: start_time and duration units are same
    action scheduled_stop_action;
    bool registered;
};

enum error_t
{
    E_SUCCESS = 0,
    E_EVENT_ID_EXISTS = 1,
    E_INVALID_EVENT_ID = 2,
    E_MAX_EVENTS_ALREADY_CREATED = 3,
};

uint8_t get_available_event_id();

//Return true if event is registered
//Return false if event is not registered or is invalid
bool is_event_registered(uint8_t event_id);

//Return E_SUCCESS if event created succesfully 
//Return E_INVALID_EXISTS if event_id already exists
//Return E_INVALID_EVENT_ID if event_id passed is out of range (0-63)
enum error_t create_event(uint8_t event_id, uint32_t start_time, uint32_t duration, void (*start_action), 
                    void (*stop_action));
//Returns E_SUCCESS if event is deleted succesfully 
//Returns E_INVALID_EVENT_ID if event_id passed is out of range (0-63)
enum error_t delete_event(uint8_t event_id);

void evaluate_and_execute_events(uint32_t cur_time);

#endif
