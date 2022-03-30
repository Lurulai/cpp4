#ifndef ASSIGNMENT_OLT2NEW_MESSAGE_BROKER_H
#define ASSIGNMENT_OLT2NEW_MESSAGE_BROKER_H

#include <stddef.h>
#include <stdlib.h>
#include "message.h"
#include "message_api.h"

typedef struct message_node{
    message_t* msg;
    struct message_node* _next;
} message_node_t;

typedef struct message_broker {
    message_node_t* _first;
    message_node_t* _last;
    long _count;
} message_broker_t;


message_broker_t create_broker();

long push(message_broker_t* pbroker, message_t* msg);

message_t* next_message_for(message_broker_t* pbroker, long target_id);

int print_messages_for(message_broker_t* pbroker, long target_id);

int count_messages_for(message_broker_t* pbroker, long target_id);

#endif //ASSIGNMENT_OLT2NEW_MESSAGE_BROKER_H
