#include "ssd1306.h"
#include "nano_gfx.h"
#include "sova.h"
#include <stdbool.h>

bool DEBUG_MODE = false;
SAppMenu menu;
int id = 0;

const char *MENU_LABELS[] = {
  "ROLL","YAW","PITCH","THROTTLE",
};

char *menuItems[] = {
    "Joystick : [ACTIVE]",
    "                          ",
    "yaw      : 15%",
    "pitch    : 75%",
    "throttle : 13%",
};

void set_roll(int value){
  char *s1, v1[10];
  String s = String("roll     : ");
  itoa(value,v1,10);
  if(value<10)
    s += "   ";
  else if(value<100)
    s += "  ";
  else
    s += " ";
  s += v1;
  s += "%  ";
  s.toCharArray(menuItems[1],s.length()+1);
  if(DEBUG_MODE)
    Serial.println(menuItems[1]);  
  
}
void set_yaw(int value){
  char *s1, v1[10];
  String s = String("yaw      : ");
  itoa(value,v1,10);
  if(value<10)
    s += "   ";
  else if(value<100)
    s += "  ";
  else
    s += " ";
  s += v1;
  s += "%  ";
  s.toCharArray(menuItems[2],s.length()+1);
  if(DEBUG_MODE)
    Serial.println(menuItems[2]);  
  
}

void setup(){
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_128x64_i2c_init();
    ssd1306_clearScreen();
    
    Serial.begin(115200);
    while (!Serial) { ; }
}
void loop(){
 
    set_roll(id);
    set_yaw(id);
    ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
    ssd1306_showMenu( &menu );
   // Serial.println(menuItems[1]);

    id++;
    if(id>100)
      id=0;
}

