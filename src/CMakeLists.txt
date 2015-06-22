include_directories(/home/jacob/git/stm32/src)

add_library(lcdDriver_src OBJECT lcdDriver.c platform/stm32/lcdIO.c)

set_target_properties(lcdDriver_src PROPERTIES COMPILE_FLAGS "-fno-common -O0 -g -mcpu=cortex-m3 -mthumb")
