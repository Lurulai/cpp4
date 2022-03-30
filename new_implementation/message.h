//
// Created by hello on 26/03/2022.
//

#ifndef ASSIGNMENT_OLT2NEW_MESSAGE_H
#define ASSIGNMENT_OLT2NEW_MESSAGE_H

#include <string>
#include <sstream>

enum class TargetType: int {
    dev_undefined = 0x00,
    dev_temperature_sensor,
    dev_pressure_sensor,
    dev_humidity_sensor,
    dev_heater,
    dev_air_purifier,
    UNKNOWN,
    DEV_LAST
};
struct device_t { enum TargetType devices; };

int const *g_MSG_LENGTH { reinterpret_cast <const int *> (255) };

// Based on the current message.h and message_api.h.
class message{
public:
    explicit message ();
    explicit message (TargetType target_type, long target_id, const std::string& text);

    [[nodiscard]] TargetType get_c_target_type() const;
    [[nodiscard]] long get_c_msg_id() const;
    [[nodiscard]] long get_c_target_id() const;
    [[nodiscard]] long long int get_c_timestamp() const;
    [[nodiscard]] const std::string &get_c_text() const;
    void set_c_text(const std::string &text);
    [[nodiscard]] bool is_valid() const;
    [[nodiscard]] std::string as_string() const;

private:
    const device_t c_target_type {};
    const long c_msg_id {};
    const long c_target_id {};
    const long long c_timestamp {};
    std::string c_text;
};

std::string device2str(device_t device);

#endif //ASSIGNMENT_OLT2NEW_MESSAGE_H
