//
// Created by hello on 26/03/2022.
//
#include "timestamp.h"
#include "message.h"

long next_id(){
    static long id {0x1000};
    return ++id;
}

#pragma region Constructors
message::message():
    c_target_type {TargetType::UNKNOWN},
    c_msg_id {next_id()},
    c_timestamp {get_timestamp()}
{ }

message::message (TargetType target_type, long target_id, const std::string& text):
    c_target_type {target_type},
    c_msg_id {next_id()},
    c_target_id {target_id},
    c_timestamp {get_timestamp()}
{
    if ((int) text.length() <= *g_MSG_LENGTH) {
        this->c_text = text;
    } else {
        this->c_text = text.substr(0, *g_MSG_LENGTH);
    }
}
#pragma endregion Constructors

#pragma region Getters
TargetType message::get_c_target_type() const {
    return c_target_type.devices;
}

long message::get_c_msg_id() const {
    return c_msg_id;
}

long message::get_c_target_id() const {
    return c_target_id;
}

long long int message::get_c_timestamp() const {
    return c_timestamp;
}

const std::string &message::get_c_text() const {
    return c_text;
}

#pragma endregion Getters

void message::set_c_text(const std::string &text) {
    c_text = text;
}

bool message::is_valid() const {
    return this->c_target_type.devices != TargetType::UNKNOWN && !this->c_text.empty();
}

std::string device2str(device_t device) {
    static const std::string names[] = {
            "undefined/generic",
            "temperature sensor",
            "pressure sensor",
            "humidity sensor",
            "heater",
            "air purifier",
            "UNKNOWN"
    };

    if (device.devices < TargetType::DEV_LAST){
        return names [(int) device.devices];
    }
    return names [(int) TargetType::DEV_LAST - 1];
}

std::string message::as_string() const {
    std::ostringstream out_stream;
    out_stream << "[id: " << this->c_msg_id << ", ts: " << this->c_timestamp
    << ", target_id: " << c_target_id << ", target_type: " << device2str(this->c_target_type)
    << "]: \"" << this->c_text << "\"" << std::endl;
    return out_stream.str();
}
