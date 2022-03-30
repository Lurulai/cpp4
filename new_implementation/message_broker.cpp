//
// Created by hello on 26/03/2022.
//

#include "message_broker.h"
#include <vector>
#include <iostream>

message_broker::message_broker() = default;

void message_broker::add (TargetType target_type, long target_id, std::string text) {
    message msg = message(target_type, target_id, text);
    this->messages.push_back(msg);
}

void message_broker::add (const message& msg) {
    this->messages.push_back(msg);
}

int message_broker::count() const {
    return (int) this->messages.size();
}

int message_broker::count (long target_id) const {
    auto count {0};
    for (auto i {0}; i < (int) this->messages.size(); ++i) {
        if (this->messages.at(i).get_c_target_id() == target_id) {
            count ++;
        }
    }
    return count;
}

message &message_broker::peek_message_for (long target_id) const {
    auto msg_nr {0}; // Returning first message in case of 0.
    for (auto i {0}; i < (int) this->messages.size(); ++i) {
        if (this->messages.at(i).get_c_target_id() == target_id) {
            return const_cast<message &>(messages.at(i));
        }
    }
    return const_cast<message &>(messages.at(msg_nr));
}

message message_broker::pop_message_for(long target_id) {
    auto msg_nr {0}; // First index of vector (first message).
    for (auto i {0}; i < (int) this->messages.size(); ++i) {
        if (this->messages.at(i).get_c_target_id() == target_id) {
            message cpy_msg = message(this->messages.at(i).get_c_target_type(),
                                      this->messages.at(i).get_c_target_id(),
                                      this->messages.at(i).get_c_text());
            this->messages.erase(messages.begin() + i);
            return cpy_msg;
        }
    }
    return messages.at(msg_nr);
}

void message_broker::print(long target_id) const {
    std::cout << "ID: [" << target_id << "]" <<std::endl;
    for (auto i {0}; i < (int) this->messages.size(); ++i) {
        if (this->messages.at(i).get_c_target_id() == target_id) {
            std::cout << messages.at(i).as_string() << std::endl;
        }
    }
}

void message_broker::print() const {
    for (auto i {0}; i < (int) messages.size(); ++i) {
        std::cout << messages.at(i).as_string() << std::endl;
    }
}
