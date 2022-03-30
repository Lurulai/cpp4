//
// Created by hello on 26/03/2022.
//

#ifndef ASSIGNMENT_OLT2NEW_MESSAGE_READER_H
#define ASSIGNMENT_OLT2NEW_MESSAGE_READER_H

#include "message.h"
#include "message_broker.h"
#include <iostream>
#include <fstream>

class message_reader{
public:
    explicit message_reader (std::string file_name);
    message read_next();
    bool has_next();
private:
    std::vector<message> msgs {};
    int current_index {0};
};


#endif //ASSIGNMENT_OLT2NEW_MESSAGE_READER_H
