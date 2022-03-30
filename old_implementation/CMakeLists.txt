
add_executable(old_implementation main.c message_api.c message_broker.c timestamp.c message_list.c message_list.h)

set_target_properties(old_implementation
        PROPERTIES
            LANGUAGE C
            C_STANDARD 11
            C_STANDARD_REQUIRED YES
            C_EXTENSIONS NO
        )

target_compile_options(old_implementation PRIVATE -Og -Wall -Wextra -pedantic)
