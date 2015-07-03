include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test2_display_string.elf main.c $<TARGET_OBJECTS:lcdDriver_src> $<TARGET_OBJECTS:stm32_src>)  

set_target_properties(test2_display_string.elf PROPERTIES COMPILE_FLAGS "-fno-common -O0 -g -mcpu=cortex-m3 -mthumb")
set_target_properties(test2_display_string.elf PROPERTIES LINK_FLAGS "-T/home/jacob/git/stm32/stm32.ld -nostartfiles")

add_custom_command(
    TARGET test2_display_string.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_CURRENT_BINARY_DIR}/test2_display_string.elf ${CMAKE_CURRENT_BINARY_DIR}/test2_display_string.bin
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Convert the ELF output file to a binary image" )

add_custom_command(
    TARGET test2_display_string.elf POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -S ${CMAKE_CURRENT_BINARY_DIR}/test2_display_string.elf > ${CMAKE_CURRENT_BINARY_DIR}/test2_display_string.lst
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Convert the ELF output file to a list of assembly instructions" )
