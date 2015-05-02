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

Command                 | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0 | Hex
------------------------|----|----|----|----|----|----|----|----|----
Clear Display           | 0  | 0  | 0  | 0  | 0  | 0  | 0  | 1  | 01
Display & Cursor Home   | 0  | 0  | 0  | 0  | 0  | 0  | 1  | x  | 02 or 03
Character Entry Mode    | 0  | 0  | 0  | 0  | 0  | 1  |I/D | S  | 04 to 07
Display On/Off & Cursor | 0  | 0  | 0  | 0  | 1  | D  | U  | B  | 08 to 0F
Function Set            | 0  | 0  | 1  |8/4 |2/1 |10/7| x  | x  | 20 to 3F
Set CGRAM Address       | 0  | 1  | A  | A  | A  | A  | A  | A  | 40 to 7F
Set Display Address     | 1  | A  | A  | A  | A  | A  | A  | A  | 80 to FF

<pre>
I/D: 1=Increment(1), 0=Decrement
S: 1=Display shift on, 0=Display shift off
D: 1=Display On, 0=Display Off(1)
U: 1=Cursor underline on, 0=Underline off(1)
B: 1=Curser blink on, 0=Cursor blink off(1)
D/C: 1=Display shift, 0=Cursor move
R/L: 1=Right shift, 0=Left shift
8/4: 1=8 bit interface(1), 0=4 bit interface
2/1: 1=2 line mode, 0=1 line mode(1)
10/7: 1=5x10 dot format, 0=5x7 dot format (1)

(1) = Initialisation settings
</pre>

### Show character 'a' on the LCD

The following steps have to be performed in order to display a on the LCD:

Description                                             | Pin            |
--------------------------------------------------------|----------------|
Activate command mode                                   | RS = Low       |              
Set 4 bit mode, 1 line mode, 5x7 dot format             | D7-D0 = 0x20   |           
Clear display                                           | D7-D0 = 0x01   |           
Turn on display, Curser underline off, Cursor blink off | D7-D0 = 0x0B   |
Activate character mode                                 | RS = High      |
Send character a to LCD                                 | D7-D0 = 0x41   | 
