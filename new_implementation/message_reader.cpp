//
// Created by hello on 26/03/2022.
//

#include "message_reader.h"

message splitter (std::string line) {
    std::string split_holder[3] {};
    std::string buffer;
    auto count {0};

    for (auto i {0}; i < (int) line.length(); ++i) {
        if (isspace(line[i]) && count != 2) {
            split_holder[count] = buffer;
            buffer.clear();
            count++;
        } else {
            buffer.push_back(line[i]);
        }
    }
    split_holder[count] = buffer;


    long target_id {std::stol(split_holder[0])};

    TargetType target_type {TargetType::dev_undefined};
    for (auto dev {(int) TargetType::dev_undefined}; dev < (int) TargetType::DEV_LAST; dev++) {
        device_t dev_t{};
        dev_t.devices = static_cast<TargetType>(dev);
        auto pos {device2str(dev_t).find('_')};
        std::string dev_filter {device2str(dev_t).substr(pos)};

        if (dev_filter == split_holder[1]) {
            target_type = static_cast<TargetType>(dev);
            break;
        }
    }

    return message(target_type, target_id, split_holder[2]);
}

message_reader::message_reader(std::string file_name) {
    std::ifstream input {file_name};
    if (input.is_open()) {
        for (std::string line; getline(input, line);) {
            if (!line.empty()) {
                message msg = splitter(line);
                this->msgs.push_back(msg);
            }
        }
    }
    input.close();
}

message message_reader::read_next() {
    return this->msgs.at(this->current_index++);
}

bool message_reader::has_next() {
    return this->current_index < (int) this->msgs.size();
}
