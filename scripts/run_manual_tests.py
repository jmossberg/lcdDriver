import load_sw_stm32

#Test1: Display character A 
load_sw_stm32.load_sw_stm32('/home/jacob/git/lcdDriver/build/test/endtoend/test1_display_character_a/test1_display_character_a.bin')
test1 = input('Test1: Is character A displayed on LCD? LED should be blinking with 3 seconds intervall if all test code executed.')

print('Test results: ')
print('test1: ' + test1)