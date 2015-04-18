#Myunit folders
PICUNIT=/home/jacob/git/picUnit
PICUNIT_SRC=$(PICUNIT)/src
PICUNIT_HEADER=$(PICUNIT_SRC)
PICUNIT_TESTS=$(PICUNIT)/tests

#Myunit source code files
PICUNIT_FILES=$(PICUNIT_SRC)/picUnit.c
PICUNIT_SELFTEST=$(PICUNIT_TESTS)/picUnit_test.c

#PIC Platform
##PIC tools
PICUNIT_PIC_COMPILER=/opt/microchip/xc8/v1.11/bin/xc8
PICUNIT_PIC_PK2CMD=../../../tools/pk2cmd
PICUNIT_PIC_PK2CMD=/home/jacob/svntrac/cidemo/tools/pk2cmd
PICUNIT_PIC_TARGET=lcdDriverTestPic
##PIC folders
PICUNIT_PIC_SRC=$(PICUNIT_SRC)/platform/pic
PICUNIT_PIC_INC_DIRS=$(PICUNIT_PIC_SRC)
PICUNIT_PIC_OUT=$(PICUNIT)/out/xc8
##PIC Platform specific souce code
PICUNIT_PIC_FILES=$(PICUNIT_PIC_SRC)/eepromDriver.c $(PICUNIT_PIC_SRC)/picUnit_pic.c

#GCC Platform
##GCC Tools
PICUNIT_GCC_COMPILER=gcc
PICUNIT_GCC_TARGET=lcdDriverTestGcc
##GCC folders
PICUNIT_GCC_SRC=$(PICUNIT_SRC)/platform/gcc
PICUNIT_GCC_INC_DIRS=$(PICUNIT_GCC_SRC)
PICUNIT_GCC_OUT=$(PICUNIT)/out/gcc
##GCC Platform specific source code
PICUNIT_GCC_FILES=$(PICUNIT_GCC_SRC)/picUnit_gcc.c

#lcdIO Mock
LCDIO_MOCK_FILES=../tests/mock_lcdIO/mock_lcdIO.c
LCDIO_MOCK_HEADER=../tests/mock_lcdIO

#lcdDriver
LCDDRIVER_TESTS=../tests
LCDDRIVER_SELFTEST=$(LCDIO_MOCK_FILES) $(LCDDRIVER_TESTS)/lcdDriver_test.c
LCDDRIVER_SELFTEST_HEADER=$(LCDIO_MOCK_HEADER)
LCDDRIVER=../src
LCDDRIVER_FILES=$(LCDDRIVER)/lcdDriver.c
LCDDRIVER_HEADER=$(LCDDRIVER)
LCDDRIVER_OUT_PIC=../out/xc8
LCDDRIVER_OUT_GCC=../out/gcc

#lcdIO
#PIC
LCD_IO_FILES=../src/platform/pic/lcdIO.c
LCD_IO_PLATFORM_HEADER=../src/platform/pic

#test on hardware
TEST_ON_HARDWARE_TEST_FILE=../tests/lcdDriver_testOnHardware.c
TEST_ON_HARDWARE_PIC_TARGET=lcdDriver_testOnHardware

#lcdIO test on hardware
LCD_IO_ACTIVATE_COMMAND_MODE_TEST_FILE=../tests/lcdIO_activateCommandMode_test.c
LCD_IO_ACTIVATE_COMMAND_MODE_PIC_TARGET=lcdIO_activateCommandMode_TestPic
LCD_IO_ACTIVATE_CHARACTER_MODE_TEST_FILE=../tests/lcdIO_activateCharacterMode_test.c
LCD_IO_ACTIVATE_CHARACTER_MODE_PIC_TARGET=lcdIO_activateCharacterMode_TestPic
LCD_IO_SET_ENABLE_HIGH_TEST_FILE=../tests/lcdIO_setEnableHigh_test.c
LCD_IO_SET_ENABLE_HIGH_PIC_TARGET=lcdIO_setEnableHigh_TestPic
LCD_IO_TOGGLE_ENABLE_TEST_FILE=../tests/lcdIO_toggleEnable_test.c
LCD_IO_TOGGLE_ENABLE_PIC_TARGET=lcdIO_toggleEnable_TestPic
LCD_IO_SET_DATA_BITS_TEST_FILE=../tests/lcdIO_setDataBits_test.c
LCD_IO_SET_DATA_BITS_PIC_TARGET=lcdIO_setDataBits_TestPic

buildall: buildforpic buildforgcc

runall: runonpic runongcc printrunresults

rungccresults: runongcc printrunresultsgcc

runpicresults: runonpic printrunresultspic

printrunresults: printrunresultspic printrunresultsgcc 

printrunresultspic:
	@echo
	@echo PIC
	@echo ===
	cat $(LCDDRIVER_OUT_PIC)/lcdDriver_testresults.xml

printrunresultsgcc:
	@echo 
	@echo GCC
	@echo ===
	cat $(LCDDRIVER_OUT_GCC)/lcdDriver_testresults.xml

clean:
	rm -f $(LCDDRIVER_OUT_PIC)/*
	rm -f funclist
	rm -f $(LCDDRIVER_OUT_GCC)/*

buildforpic: clean
	@echo Compiling lcdDriver test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(PICUNIT_PIC_FILES) $(PICUNIT_FILES) $(LCDDRIVER_FILES) $(LCDDRIVER_SELFTEST) -I$(PICUNIT_SRC) -I$(PICUNIT_PIC_INC_DIRS) -I$(LCDDRIVER_SELFTEST_HEADER) -I$(LCDDRIVER_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(PICUNIT_PIC_TARGET)
	@echo Removing funclist file
	rm -f funclist

testonpicbuild: clean
	@echo Compiling lcdDriver hardware test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCDDRIVER_FILES) $(TEST_ON_HARDWARE_FILES) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(TEST_ON_PIC_TARGET)
	@echo Removing funclist file
	rm -f funclist

lcdDriverTestOnPicBuild: clean
	@echo Compiling lcdDriver_testOnHardware test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCDDRIVER_FILES) $(TEST_ON_HARDWARE_TEST_FILE) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(TEST_ON_HARDWARE_PIC_TARGET)

lcdDriverTestOnPicRun: lcdDriverTestOnPicBuild
	@echo Load program $(TEST_ON_HARDWARE_PIC_TARGET) on to PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(TEST_ON_HARDWARE_PIC_TARGET).hex -M -Z
	@echo Power on PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
	@echo Verify state, then push enter to run next test...
	@read input
	@echo Read configuration bits
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -GI
	@echo Power down PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W

lcdIOTestOnPicBuild: clean
	@echo Compiling lcdIO_activateCommandMode test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCD_IO_ACTIVATE_COMMAND_MODE_TEST_FILE) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(LCD_IO_ACTIVATE_COMMAND_MODE_PIC_TARGET)
	@echo Compiling lcdIO_activateCharacterMode test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCD_IO_ACTIVATE_CHARACTER_MODE_TEST_FILE) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(LCD_IO_ACTIVATE_CHARACTER_MODE_PIC_TARGET)
	@echo Compiling lcdIO_setEnableHigh test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCD_IO_SET_ENABLE_HIGH_TEST_FILE) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(LCD_IO_SET_ENABLE_HIGH_PIC_TARGET)
	@echo Compiling lcdIO_toggleEnableHigh test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCD_IO_TOGGLE_ENABLE_TEST_FILE) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(LCD_IO_TOGGLE_ENABLE_PIC_TARGET)
	@echo Compiling lcdIO_setDataBits test with xc8 for Pic
	$(PICUNIT_PIC_COMPILER) --CHIP=16F690 $(LCD_IO_FILES) $(LCD_IO_SET_DATA_BITS_TEST_FILE) -I$(LCDDRIVER_HEADER) -I$(LCD_IO_PLATFORM_HEADER) --OUTDIR=$(LCDDRIVER_OUT_PIC) --OUTPUT=intel -O$(LCDDRIVER_OUT_PIC)/$(LCD_IO_SET_DATA_BITS_PIC_TARGET)
	@echo Removing funclist file
	rm -f funclist

lcdIOTestOnPicRun: lcdIOTestOnPicBuild
#	@echo Load program $(LCD_IO_ACTIVATE_COMMAND_MODE_PIC_TARGET) on to PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(LCD_IO_ACTIVATE_COMMAND_MODE_PIC_TARGET).hex -M
#	@echo Power on PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
#	@echo Verify state, then push enter to run next test...
#	@read input
#	@echo Power down PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W
#	@echo Wait 1 second
#	@sleep 1
#	@echo Load program $(LCD_IO_ACTIVATE_CHARACTER_MODE_PIC_TARGET) on to PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(LCD_IO_ACTIVATE_CHARACTER_MODE_PIC_TARGET).hex -M
#	@echo Power on PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
#	@echo Verify state, then push enter to run next test...
#	@read input
#	@echo Power down PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W
#	@echo Wait 1 second
#	@sleep 1
#	@echo Load program $(LCD_IO_SET_ENABLE_HIGH_PIC_TARGET) on to PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(LCD_IO_SET_ENABLE_HIGH_PIC_TARGET).hex -M
#	@echo Power on PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
#	@echo Verify state, then push enter to run next test...
#	@read input
#	@echo Power down PIC
#	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W
#	@echo Wait 1 second
#	@sleep 1
	@echo Load program $(LCD_IO_TOGGLE_ENABLE_PIC_TARGET) on to PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(LCD_IO_TOGGLE_ENABLE_PIC_TARGET).hex -M
	@echo Power on PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
	@echo Verify state, then push enter to run next test...
	@read input
	@echo Read configuration bits
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -GI
	@echo Power down PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W
	@echo Wait 1 second
	@sleep 1
	@echo Load program $(LCD_IO_SET_DATA_BITS_PIC_TARGET) on to PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(LCD_IO_SET_DATA_BITS_PIC_TARGET).hex -M
	@echo Power on PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
	@echo Verify state, then push enter to run next test...
	@read input
	@echo Read configuration bits
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -GI
	@echo Power down PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W

buildforgcc: clean
	@echo Compiling lcdDriver test with gcc
	$(PICUNIT_GCC_COMPILER) -ggdb $(PICUNIT_GCC_FILES) $(PICUNIT_FILES) $(LCDDRIVER_FILES) $(LCDDRIVER_SELFTEST) -I$(PICUNIT_SRC) -I$(PICUNIT_GCC_INC_DIRS) -I$(LCDDRIVER_SELFTEST_HEADER) -I$(LCDDRIVER_HEADER) -o$(LCDDRIVER_OUT_GCC)/$(PICUNIT_GCC_TARGET).o

runonpic: buildforpic
	@echo Load program on to PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -F$(LCDDRIVER_OUT_PIC)/$(PICUNIT_PIC_TARGET).hex -M
	@echo Power on PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -T -R
	@echo Wait 2 seconds
	@sleep 2
	@echo Power down PIC
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -W
	@echo Read EEPROM memory
	$(PICUNIT_PIC_PK2CMD)/pk2cmd -PPIC16F690 -B$(PICUNIT_PIC_PK2CMD) -GE0-ff | tee $(LCDDRIVER_OUT_PIC)/eeprom.txt
	@echo Parse test names
	cat $(LCDDRIVER_SELFTEST) | grep picUnit_run_test | sed 's/^.*(//g' | sed 's/,.*$$//g' | tee $(LCDDRIVER_OUT_PIC)/testNames.txt
	@echo Generate test report in xml format
	python $(PICUNIT_SRC)/generateJunitReportFromEeprom.py -p pic -r $(LCDDRIVER_OUT_PIC)/eeprom.txt -x $(LCDDRIVER_OUT_PIC)/lcdDriver_testresults.xml -t $(LCDDRIVER_OUT_PIC)/testNames.txt

runongcc: buildforgcc
	@echo Running $(PICUNIT_GCC_TARGET)
	$(LCDDRIVER_OUT_GCC)/$(PICUNIT_GCC_TARGET).o | tee $(LCDDRIVER_OUT_GCC)/testResults.txt
	@echo Parse test names
	cat $(LCDDRIVER_SELFTEST) | grep picUnit_run_test | sed 's/^.*(//g' | sed 's/,.*$$//g' | tee $(LCDDRIVER_OUT_GCC)/testNames.txt
	@echo Generate test report in xml format
	python $(PICUNIT)/scripts/generateTestReport/src/generatetestreport.py -p gcc -r $(LCDDRIVER_OUT_GCC)/testResults.txt -x $(LCDDRIVER_OUT_GCC)/lcdDriver_testresults.xml -t $(LCDDRIVER_OUT_GCC)/testNames.txt
