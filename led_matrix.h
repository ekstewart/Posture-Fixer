/*
	led_matrix.h
	@author Evan Stewart

	File contains necessary variable definitions for each column
	and row pin in an 8x8 LED matrix
	for the appropriate PORT (assuming PORT A and B are being used)


*/

/*
    1_2_3_4_5_6_7_8
  1|x x O x x O x x C3 C6
  2|x x O x x O x x C3 C6
  3|x x O x x O x x C3 C6
  4|O x x x x x x O C1 C8
  5|x O x x x x O x C2 C7
  6|x x O O O O x x C3 C4 C5 C6
  7|x x x x x x x x
  8|x x x x x x x x
  
  1_2_3_4_5_6_7_8
  1|x x O x x O x x C3 C6
  2|x x O x x O x x C3 C6
  3|x x O x x O x x C3 C6
  4|x x x x x x x x
  5|x x x x x x x x
  6|x x O O O O x x C3 C4 C5 C6
  7|x O x x x x O x C2 C7
  8|O x x x x x x O C1 C8

  */


#define COLA1 0x10 //PORTA# 
#define COLB2 0x04 //PORTB
#define COLB3 0x08 //PORTB
#define COLA4 0x02 //PORTA#
#define COLB5 0x20 //PORTB
#define COLA6 0x04 //PORTA#
#define COLA7 0x40 //PORTA#
#define COLA8 0x80 //PORTA#

#define ROWA1 0x01 //PORTA#
#define ROWA2 0x20 //PORTA#
#define ROWB3 0x80 //PORTB
#define ROWA4 0x08 //PORTA#
#define ROWB5 0x01 //PORTB
#define ROWB6 0x40 //PORTB
#define ROWB7 0x02 //PORTB
#define ROWB8 0x10 //PORTB

