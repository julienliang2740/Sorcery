#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

  public:
    Xwindow(int width=1800, int height=1800);  // Constructor; displays the window.
    ~Xwindow();                              // Destructor; destroys the window.

    enum {White=0, Black, Red, Green, Blue, LightBlue}; // Available colours.

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    void drawString(int x, int y, std::string msg);

    void drawWhiteString(int x, int y, std::string msg);

    // Draws a rectangle
    void drawRectangle(int x, int y, int width, int height);

    // Draws a centered string
    void drawCenteredString(int centerX, int y, std::string msg);

    // Draws a wrapped string
    void drawWrappedString(int x, int y, const std::string &text, int maxWidth);

    // Draws a line
    void drawLine(int x1, int y1, int x2, int y2);

    // Fills in everything with a solid colour, effectively clearing the board
    void clearWindow();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Actual displaying functions

    // Builds the static parts of the board
    void buildBoard(int cardWidth, int cardHeight, int spacing); // x-length, y-length

    // Building cards...
    void graphics_display_minion_no_ability(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence);
    void graphics_display_minion_triggered_ability(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence,std::string trigger_desc);
    void graphics_display_minion_activated_ability(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence,int ability_cost, std::string ability_desc);

    void graphics_display_ritual(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int ritual_cost,std::string ritual_desc,int ritual_charges);

    void graphics_display_spell(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc);

    void graphics_display_enchantment_attack_defence(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc,std::string attack,std::string defence);
    void graphics_display_enchantment(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc);

    void graphics_display_player_card(int x, int y, int cardWidth, int cardHeight, int player_num, std::string name,int life,int mana);

    //Helpers to build cards...
    void graphics_display_minion_general(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence);
    void graphics_display_enchantment_general(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc);
};

#endif
