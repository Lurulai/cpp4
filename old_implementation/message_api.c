#include <string.h>
#include <stdio.h>
#include "message_api.h"
#include "timestamp.h"

long next_id(){
    static long id = 0x1000;
    return ++id;
}

const char* device2str(device_t dev){
    static const char* names[] = {
        "undefined/ generic",
        "temperature sensor",
        "pressure sensor",
        "humidity sensor",
        "heater",
        "air purifier",
        "UNKNOWN"
    };

    if (dev < DEV_LAST){
        return names[dev];
    }
    return names[DEV_LAST];
}

message_t create_message(const long target_id, const device_t target_type, const char* text){
    message_t message = (message_t){
      .text = {0},
      .timestamp = get_timestamp(),
      .msg_id = next_id(),
      .target_id = target_id,
      .target_type = target_type
    };

    // FIXME: No check is done if `text` is not longer than `MSG_LENGTH` - potential buffer overflow
    strcpy(message.text, text);

    return message;
}


void print_message(message_t* pmsg){
    printf("[id: %ld, ts:%lld, target_id: %ld, target_type: %s]: \"%s\"\n",
           pmsg->msg_id, pmsg->timestamp, pmsg->target_id,
           device2str(pmsg->target_type), pmsg->text);
}
