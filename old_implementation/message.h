#ifndef ASSIGNMENT_C_MESSAGE_H
#define ASSIGNMENT_C_MESSAGE_H

// FIXME: unsafe enumeration with no type checking
enum device_type {
    dev_undefined = 0x00,
    dev_temperature_sensor,
    dev_pressure_sensor,
    dev_humidity_sensor,
    dev_heater,
    dev_air_purifier,
    DEV_LAST
};
typedef int device_t;

// FIXME: use of #define to declare a constant
#define MSG_LENGTH (255)

typedef struct message {
    // FIXME: message text takes always 255 bytes - that's a waste of memory for most messages!
    char text[MSG_LENGTH];
    // FIXME: all the fields are non-const, they should be, messages are not mutable.
    long msg_id;
    long long timestamp;
    long target_id;
    device_t target_type;
} message_t;

#endif //ASSIGNMENT_C_MESSAGE_H
