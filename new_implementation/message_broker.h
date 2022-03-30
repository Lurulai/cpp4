//
// Created by hello on 26/03/2022.
//

#ifndef ASSIGNMENT_OLT2NEW_MESSAGE_BROKER_H
#define ASSIGNMENT_OLT2NEW_MESSAGE_BROKER_H

#include "message.h"
#include <vector>
#include <string>

class message_broker{
public:
    explicit message_broker();

    void add (TargetType target_type, long target_id, std::string text);
    void add (const message& msg);

    [[nodiscard]] int count() const;
    [[nodiscard]] int count (long target_id) const;
    [[nodiscard]] message& peek_message_for (long target_id) const;
    [[nodiscard]] message pop_message_for (long target_id);

    void print (long target_id) const;
    void print() const;

private:
    std::vector <message> messages;
    const long _count {};
};


#endif //ASSIGNMENT_OLT2NEW_MESSAGE_BROKER_H
