#include "ssd1306.h"
#include "nano_gfx.h"
#include "sova.h"
#include <stdbool.h>

bool DEBUG_MODE = true;
SAppMenu menu;
int id = 0;

int ROLL = 0, THROTTLE = 0, PITCH = 0, YAW = 0;

const char *MENU_LABELS[] = {
  "ROLL    ",
  "YAW     ",
  "PITCH   ",
  "THROTTLE",
};

char *menuItems[] = {
    "Joystick : [ACTIVE]",
    "                          ",
    "                          ",
    "                          ",
    "                          ",
};

int normalize_test_value(int value){
  while(value<=100)
    value = value/2;
  
  return value;
}

void set_menu_label_value(int menu_label_id, int value){
  char v1[10];

  String s = String("");
  s += MENU_LABELS[menu_label_id];
  s += " : ";
  itoa(value,v1,10);
  if(value<10)
    s += "   ";
  else if(value<100)
    s += "  ";
  else
    s += " ";
  s += v1;
  s += "%  ";
  s.toCharArray(menuItems[menu_label_id+1],s.length()+1);
  if(DEBUG_MODE){
    Serial.println(menuItems[menu_label_id+1]); 
  } 
  
}

void setup(){
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_128x64_i2c_init();
    ssd1306_clearScreen();
    
    Serial.begin(115200);
    while (!Serial) { ; }
}
void loop(){
 
    set_menu_label_value(1, id);
    set_menu_label_value(2, id+33);
  //  set_menu_label_value(2, id+66);
  //  set_menu_label_value(3, id+75);
    ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
    ssd1306_showMenu( &menu );
    //Serial.println(menuItems[1]);

    id++;
    if(id>100)
      id=0;
}

