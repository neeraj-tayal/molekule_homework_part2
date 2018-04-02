# molekule_homework_part2

To build and run the code with logging enabled

gcc -o scheduler scheduler.c test_scheduler.c -D LOGGING_ENABLED && ./scheduler

To build without logging

gcc -o scheduler scheduler.c test_scheduler.c && ./scheduler

/*Assumptions/Constraints/Improvements

1. No more than 64 events can be created
2. Static memory allocation (array data structure) is used for handling the events
(Time Complexity for searching O(1))
3. Memory for 64 events can be statically allocated without corrupting memory for other code in the FW
4. Client not able to override the existing event without deleting the existing event first
5. Linked List can be used if we know number of events will be fewer than Max at the cost of
Time Complexity of O(n) for searching or removing any event
6. Hashing function can be formed to create event_id in the library itself rather than relying on user to pass 
the right event_id
7. Circular array can be used if we don't want user to delete the events when max events are scheduled
8. Can add another feature to let user modify the existing event config. by simply adding
another bool flag force_override in create_event function

*/

