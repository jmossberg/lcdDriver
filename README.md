A PIC device driver for LCDs compatible with the Hitachi HD44780 controller chip

### How to control the LCD

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

