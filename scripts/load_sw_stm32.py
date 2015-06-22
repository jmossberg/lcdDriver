import pexpect, sys

def load_sw_stm32(binary_file):
    child = pexpect.spawn("telnet localhost 4444")
    
    child.expect ('> ')
    child.sendline ('reset halt')
    child.expect ('> ')
    child.sendline ('flash probe 0')
    child.expect ('> ')
    child.sendline ('stm32f1x mass_erase 0')
    child.expect ('> ')
    child.sendline ('flash write_bank 0 ' + binary_file + ' 0')
    child.expect ('> ')
    child.sendline ('reset run')
    child.expect ('> ')
    child.sendline ('exit')

if __name__ == "__main__":
    # execute only if run as a script
    binary_file = sys.argv[1]
    load_sw_stm32(binary_file)
