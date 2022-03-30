#include "message_list.h"
#include "message.h"
#include "message_api.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE (1024)

static FILE* fp = NULL;
static char buffer[BUFFER_SIZE];
static message_t message;

void lst_close() {
    if (fp) {
        fclose(fp);
        fp = NULL;
    }
}

_Bool lst_open(const char* file_name) {
    lst_close();
    return (fp = fopen(file_name, "r")) != NULL;
}

// FIXME: returns a pointer with no clear ownership - here the pointer is to an internal data structure
//        this can be dangerous if somebody tries to free this pointer!
const message_t* lst_read_next(){

    if (fp && !feof(fp)){
        if (fgets(buffer, BUFFER_SIZE, fp)){
            char* str = NULL;
            long target_id = strtol(buffer, &str, 10);
            if (&buffer[0] != str){
                // parsed the target_type id

                // skip over all the spaces:
                while (isspace(*str)) ++str;

                // identify the target_type type
                // FIXME: identification is based on the first three characters only - not future prof
                device_t target_type = dev_undefined;
                for (int dev = dev_undefined; dev < DEV_LAST; ++dev){
                    // compare 3 first characters of the dev ids
                    if (strncmp(str, device2str(dev), 3) == 0){
                        target_type = dev;
                        break;
                    }
                }
                // skip the whole device identification string
                str = strpbrk(str, " \t");
                // skip over all the spaces:
                while (isspace(*str)) ++str;
                // search for a newline and if it's there replace it with '\0'
                char* end = strpbrk(str, "\n");
                if (end) *end = '\0';

                message = create_message(target_id, target_type, str);
                return &message;
            }

        }
    }
    return NULL;
}



