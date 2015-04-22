A PIC device driver for LCDs compatible with the Hitachi HD44780 controller chip

### LCD pins

LCDs compatible with the Hitachi HD44780 controller chip make use of the following pins:

Pin No. | Name | Function
--------|------|---------
1       | Vss  | Ground
2       | Vdd  | + Supply
3       | Vee  | Contrast
4       | RS   | Register Select
5       | R/W  | Read/Write
6       | E    | Enable
7       | D0   | Data bit 0
8       | D1   | Data bit 1
9       | D2   | Data bit 2
10      | D3   | Data bit 3
11      | D4   | Data bit 4
12      | D5   | Data bit 5
13      | D6   | Data bit 6
14      | D7   | Data bit 7

#### RS (Register Select)

Value | Description
------|------------
Low   | LCD is in command mode, i.e. all data transferred to the LCD will be interpreted as commands.
High  | LCD is in character mode, i.e all data transferred to the LCD will be interpreted as characters. 

#### R/W (Read/Write)

Value | Description
------|------------
Low   | LCD is in write mode, i.e commands/characters can be sent to the LCD 
High  | LCD is in read mode, i.e status registers or character data can be read from the LCD 

#### E (Enable)

Value       | Description
------------|------------
Low to High | Used when reading from the LCD. Data will be avilable after low to high transition.
High to Low | Used when writing to the LCD. Data will be transferred on the high to low transition. 

#### D0 - D7 (Data bits)

Used two transfer 8 bits of data at a time. However a 4-bit mode is available where only D4 - D7 are used. The 8 bits to be sent are sent in two batches when i 4-bit mode. The upper four bits are sent first, followed by the lower four bits.

### LCD command codes

Command          | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | Hex
-----------------|----|----|----|----|----|----|----|----|----
Clear Display    | 0  | 0  | 0  | 0  | 0  | 0  | 0  | 1  | 01
