cmake_minimum_required(VERSION 3.17)
project(assignment_olt2new
        LANGUAGES C CXX
        )

CONFIGURE_FILE(messages.in new_implementation/messages.in COPYONLY)
CONFIGURE_FILE(messages.in old_implementation/messages.in COPYONLY)


add_subdirectory(new_implementation)
add_subdirectory(old_implementation)
