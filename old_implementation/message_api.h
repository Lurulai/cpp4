#ifndef ASSIGNMENT_OLT2NEW_MESSAGE_API_H
#define ASSIGNMENT_OLT2NEW_MESSAGE_API_H

#include "message.h"

extern message_t create_message(const long target_id, const device_t target_type, const char* text);

extern void print_message(message_t* pmsg);

extern const char* device2str(device_t dev);

#endif //ASSIGNMENT_OLT2NEW_MESSAGE_API_H
