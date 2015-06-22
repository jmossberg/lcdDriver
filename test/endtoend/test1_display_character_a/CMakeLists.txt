include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test1_display_character_a.elf main.c $<TARGET_OBJECTS:lcdDriver_src> $<TARGET_OBJECTS:stm32_src>)  

set_target_properties(test1_display_character_a.elf PROPERTIES COMPILE_FLAGS "-fno-common -O0 -g -mcpu=cortex-m3 -mthumb")
set_target_properties(test1_display_character_a.elf PROPERTIES LINK_FLAGS "-T/home/jacob/git/stm32/stm32.ld -nostartfiles")

add_custom_command(
    TARGET test1_display_character_a.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_CURRENT_BINARY_DIR}/test1_display_character_a.elf ${CMAKE_CURRENT_BINARY_DIR}/test1_display_character_a.bin
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Convert the ELF output file to a binary image" )

add_custom_command(
    TARGET test1_display_character_a.elf POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -S ${CMAKE_CURRENT_BINARY_DIR}/test1_display_character_a.elf > ${CMAKE_CURRENT_BINARY_DIR}/test1_display_character_a.lst
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Convert the ELF output file to a list of assembly instructions" )
