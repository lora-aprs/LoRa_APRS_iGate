
#ifndef DISPLAY_H_
#define DISPLAY_H_

void init_display();

void show_display(String header, int wait = 0);
void show_display_1(String header, String line1, int wait = 0);
void show_display_2(String header, String line1, String line2, int wait = 0);
void show_display_3(String header, String line1, String line2, String line3, int wait = 0);
void show_display_4(String header, String line1, String line2, String line3, String line4, int wait = 0);
void show_display_5(String header, String line1, String line2, String line3, String line4, String line5, int wait = 0);

#endif
