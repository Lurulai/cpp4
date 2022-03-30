#include "message_broker.h"

message_broker_t create_broker(){
    return (message_broker_t){
        ._first = NULL,
        ._last = NULL,
        ._count = 0
    };
}

// FIXME: msg is taken by non-const pointer
long push(message_broker_t* pbroker, message_t* msg){

    // allocate memory for node
    message_node_t* node = malloc(sizeof (message_node_t));

    // initialize the node, allocating memory for message
    *node = (message_node_t){
        .msg = malloc(sizeof(message_t)),
        ._next = NULL
    };

    // copy the message
    *(node->msg) = *msg;

    // no messages yet
    if (!pbroker->_count){
        pbroker->_first = pbroker->_last = node;
    }
        // there are some messages already, append
    else{
        pbroker->_last->_next = node;
        pbroker->_last = node;
    }

    return ++pbroker->_count;
}

message_t* extract_current(message_broker_t* pbroker, message_node_t* previous, message_node_t* current) {
    // we have a hit, extract the node and return it
    if (previous){
        // if the node is not the first one
        previous->_next = current->_next;
    }
    else{
        pbroker->_first = current->_next;
    }

    // we are removing the last element
    if (current == pbroker->_last){
        pbroker->_last = previous;
    }

    --pbroker->_count;

    message_t* result = current->msg;
    free(current);
    return result;
}

// returns the next message in the broker for the target_id
message_t* next_message_for(message_broker_t* pbroker, long target_id){
    if (!pbroker->_count){
        return NULL;
    }

    message_node_t* previous = NULL;
    message_node_t* current = pbroker->_first;
    while (current){
        if (current->msg->target_id == target_id){
            return extract_current(pbroker, previous, current);
        }
        previous = current;
        current = current->_next;
    }

    return NULL;
}



// target_id==0 prints all the messages
int print_messages_for(message_broker_t* pbroker, long target_id){
    if (!pbroker->_count)
        return 0;

    int count = 0;
    message_node_t* current = pbroker->_first;
    while (current){
        if (current->msg->target_id == target_id || target_id == 0){
            print_message(current->msg);
            ++count;
        }
        current = current->_next;
    }
    return count;
}

int count_messages_for(message_broker_t* pbroker, long target_id){
    if (!pbroker->_count)
        return 0;

    int count = 0;
    message_node_t* current = pbroker->_first;
    while (current){
        if (current->msg->target_id == target_id){
            ++count;
        }
        current = current->_next;
    }
    return count;
}