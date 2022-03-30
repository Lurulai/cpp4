#ifndef ASSIGNMENT_OLT2NEW_MESSAGE_LIST_H
#define ASSIGNMENT_OLT2NEW_MESSAGE_LIST_H

#include <stdbool.h>
#include "message.h"

extern void lst_close();
extern _Bool lst_open(const char* file_name);
extern const message_t* lst_read_next();

#endif //ASSIGNMENT_OLT2NEW_MESSAGE_LIST_H
