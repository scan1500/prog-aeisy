#include "main.h"

int main(void) {

  init();
	
  while (1) {

    measure_display_sonics();
    measure_display_angle();
    measure_display_pitch();
    measure_display_roll();

    LPC_GPIO1->DIR |= 1 << 21 | 1 << 25 | 1 << 26;

    LPC_GPIO1->SET = 1 << 25;
    LPC_GPIO1->CLR = 1 << 26;
    //	int run = 0;
    //		while(run < 300) {
    //			int f;
    //			LPC_GPIO1->SET = 1 << 21;
    //			for(f = 0; f < 300000; f++);
    //			LPC_GPIO1->CLR = 1 << 21;
    //			for(f = 0; f < 300000; f++);
    //			
    //			run++;

    //		}
    //LPC_GPIO1->CLR = 1 << 21;
  }

}


void measure_display_sonics(void) {
  static uint8_t old_dist1 = 0, old_dist2 = 0, old_dist3 = 0;
  static uint8_t new_dist1, new_dist2, new_dist3;
  point p1 = {.x = 8}, p2 = {.x = 40}, p3 = {.x = 72};
  char str_dist[4]; //helping variable for displaying the distance

  //measure and draw first sonic, this only draws the delta / removes delta
  new_dist1 = sonic_measure(1);
  int_to_string(str_dist, new_dist1, 3);
  lcd_print_string(str_dist, 0, 0);
  if (new_dist1 > old_dist1) {
    p1.y = old_dist1 + 10;
    if (new_dist1 > 128) {
      new_dist1 = 128;
    }
    draw_rectangle( & p1, new_dist1 - old_dist1, 10, 1);
    old_dist1 = new_dist1;
  } else if (new_dist1 < old_dist1) {
    p1.y = new_dist1 + 10;
    clr_rectangle( & p1, old_dist1 - new_dist1, 10);
    old_dist1 = new_dist1;
  }

  //measure and draw second sonic, this only draws the delta / removes delta
  new_dist2 = sonic_measure(2);
  int_to_string(str_dist, new_dist2, 3);
  lcd_print_string(str_dist, 4, 0);
  if (new_dist2 > old_dist2) {
    p2.y = old_dist2 + 10;
    if (new_dist2 > 128) {
      new_dist2 = 128;
    }
    draw_rectangle( & p2, new_dist2 - old_dist2, 10, 1);
    old_dist2 = new_dist2;
  } else if (new_dist2 < old_dist2) {
    p2.y = new_dist2 + 10;
    clr_rectangle( & p2, old_dist2 - new_dist2, 10);
    old_dist2 = new_dist2;
  }

  //measure and draw third sonic, this only draws the delta / removes delta
  new_dist3 = sonic_measure(3);
  int_to_string(str_dist, new_dist3, 3);
  lcd_print_string(str_dist, 8, 0);
  if (new_dist3 > old_dist3) {
    p3.y = old_dist3 + 10;
    if (new_dist3 > 128) {
      new_dist3 = 128;
    }
    draw_rectangle( & p3, new_dist3 - old_dist3, 10, 1);
    old_dist3 = new_dist3;
  } else if (new_dist3 < old_dist3) {
    p3.y = new_dist3 + 10;
    clr_rectangle( & p3, old_dist3 - new_dist3, 10);
    old_dist3 = new_dist3;
  }
}

void measure_display_angle() {
  char str_dir[4];
  volatile uint16_t angle;

  //Print compass
  //angle in degree 360 = North
  angle = get_dir() / 10;
  int_to_string(str_dir, angle, 3);
  lcd_print_string("ANGLE", 16, 1);
  lcd_print_string(str_dir, 22, 1);
}

void measure_display_roll() {

  char str_roll[3];
  volatile int8_t roll = get_roll();

  //Print roll
  //roll in degree +/- 85
  roll = get_roll();
  lcd_print_string("ROLL ", 16, 3);
  if (roll < 0) {
    roll *= -1;
    lcd_print_string("-", 22, 3);
  } else {
    lcd_print_string("+", 22, 3);
  }

  int_to_string(str_roll, roll, 2);
  lcd_print_string(str_roll, 23, 3);

}

void measure_display_pitch() {
  char str_pitch[3];
  volatile int8_t pitch;

  //Print pitch
  //pitch in degree +/- 85
  pitch = get_pitch();
  lcd_print_string("PITCH", 16, 2);
  if (pitch < 0) {
    pitch *= -1;
    lcd_print_string("-", 22, 2);
  } else {
    lcd_print_string("+", 22, 2);
  }

  int_to_string(str_pitch, pitch, 2);
  lcd_print_string(str_pitch, 23, 2);

}

void init(void) {
	
	point p1 = {.x = 105, .y = 0};
	point p2 = {.x = 105, .y = 39};

  //Initialize all devices and clear lcd
  lcd_init();
  timer_init();
  sonic_init();
  cmp_init();
  mtr_init();
  lcd_clr();
	
	draw_rectangle(&p1, 128, 0, 1);
	draw_rectangle(&p2, 0, 134, 1);

}

