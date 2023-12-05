#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[6][11]={"white", "black", "red", "green", "blue", "light blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 6; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawWhiteString(int x, int y, string msg) {
  XSetForeground(d, gc, WhitePixel(d, s));
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
  XSetForeground(d, gc, BlackPixel(d, s));
}

void Xwindow::drawRectangle(int x, int y, int width, int height) {
  XDrawRectangle(d, w, gc, x, y, width, height);
}

void Xwindow::drawCenteredString(int centerX, int y, std::string msg) {
    XFontStruct *font = XLoadQueryFont(d, "fixed");
    if (!font) {
        std::cerr << "can't load font" << std::endl;
        return;
    }

    XSetFont(d, gc, font->fid);

    int textWidth = XTextWidth(font, msg.c_str(), msg.length());
    int startX = centerX - (textWidth / 2);
    drawString(startX, y, msg);
    XFreeFont(d, font);
}

void Xwindow::drawWrappedString(int x, int y, const std::string &text, int maxWidth) {
  XFontStruct *font = XQueryFont(d, XGContextFromGC(gc));
  if (!font) {
    std::cerr << "can't get font information." << std::endl;
    return;
  }

  istringstream words(text);
  string word;
  string line;
  int lineHeight = font->ascent + font->descent;

  while (words >> word) {
    string candidateLine = line + (line.empty() ? "" : " ") + word;
    if (XTextWidth(font, candidateLine.c_str(), candidateLine.length()) > maxWidth) {
      drawString(x,y,line.c_str());
      line = word;
      y += lineHeight;
    }
    else {
      line = candidateLine;
    }
  }
  // and now the last line...
  if (!line.empty()) drawString(x,y,line.c_str());

  XFreeFontInfo(nullptr, font, 1);
}

void Xwindow::drawLine(int x1, int y1, int x2, int y2) {
  XDrawLine(d, w, gc, x1, y1, x2, y2);
}

void Xwindow::clearWindow() {
  XSetForeground(d, gc, WhitePixel(d, s)); 
  XFillRectangle(d, w, gc, 0, 0, 10000, 10000);
  XSetForeground(d, gc, colours[Black]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Xwindow::buildBoard(int cardWidth, int cardHeight, int spacing) {
  // Overall board
  drawRectangle(5, 5, 6*spacing+5*cardWidth, 6*spacing+5*cardHeight);

  // Sorcery banner
  fillRectangle(5, 5+3*spacing+2*cardHeight, 6*spacing+5*cardWidth, cardHeight, Xwindow::LightBlue);
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight-35, "  _____                                   ");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight-25, " / ____|                                  ");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight-15, "| (___   ___  _ __ ___ ___ _ __ _   _     ");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight-5, " \\___ \\ / _ \\| '__/ __/ _ \\ '__| | | |");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight+5, " ____) | (_) | | | (_|  __/ |  | |_| |    ");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight+15, "|_____/ \\___/|_|  \\___\\___|_|   \\__, |");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight+25, "                                 __/ |    ");
  drawString(3*spacing+2*cardWidth+16, 3*spacing+2.5*cardHeight+35, "                                |___/     ");

  // Drawing out where each card/box should be, can use this for future reference too
  drawRectangle(5+(1*spacing), 5+(1*spacing), cardWidth, cardHeight); 
  drawRectangle(5+(3*spacing+2*cardWidth), 5+(1*spacing), cardWidth, cardHeight);
  drawRectangle(5+(5*spacing+4*cardWidth), 5+(1*spacing), cardWidth, cardHeight);

  drawRectangle(5+(1*spacing), 5+(2*spacing+1*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(2*spacing+1*cardWidth), 5+(2*spacing+1*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(3*spacing+2*cardWidth), 5+(2*spacing+1*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(4*spacing+3*cardWidth), 5+(2*spacing+1*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(5*spacing+4*cardWidth), 5+(2*spacing+1*cardHeight), cardWidth, cardHeight);

  drawRectangle(5+(1*spacing), 5+(4*spacing+3*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(2*spacing+1*cardWidth), 5+(4*spacing+3*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(3*spacing+2*cardWidth), 5+(4*spacing+3*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(4*spacing+3*cardWidth), 5+(4*spacing+3*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(5*spacing+4*cardWidth), 5+(4*spacing+3*cardHeight), cardWidth, cardHeight);

  drawRectangle(5+(1*spacing), 5+(5*spacing+4*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(3*spacing+2*cardWidth), 5+(5*spacing+4*cardHeight), cardWidth, cardHeight);
  drawRectangle(5+(5*spacing+4*cardWidth), 5+(5*spacing+4*cardHeight), cardWidth, cardHeight);
}

// int x, int y, int cardWidth, int cardHeight

void Xwindow::graphics_display_minion_no_ability(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence) {
  graphics_display_minion_general(x, y, cardWidth, cardHeight, name, cost, attack, defence);
}

void Xwindow::graphics_display_minion_triggered_ability(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence,std::string trigger_desc) {
  graphics_display_minion_general(x, y, cardWidth, cardHeight, name, cost, attack, defence);
  drawWrappedString(x+2, y+(cardHeight/2)-2, trigger_desc, cardWidth-2);
}

void Xwindow::graphics_display_minion_activated_ability(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence,int ability_cost, std::string ability_desc) {
  graphics_display_minion_general(x, y, cardWidth, cardHeight, name, cost, attack, defence);
  
  drawLine(x, y+cardHeight/2, x+cardWidth/9, y+cardHeight/2);
  drawLine(x+cardWidth/9, y+cardHeight/3, x+cardWidth/9, y+cardHeight/2);

  ostringstream abilitycostStr;
  abilitycostStr << ability_cost;
  string abilitycost_output = abilitycostStr.str();
  
  drawCenteredString((x+x+2+cardWidth/9)/2, y+(cardHeight/2)-2,abilitycost_output);
  drawWrappedString(x+2+cardWidth/9, y+(cardHeight/2)-2, ability_desc, cardWidth-2-cardWidth/9);
}

void Xwindow::graphics_display_ritual(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int ritual_cost,std::string ritual_desc,int ritual_charges) {
  // card shell
  drawRectangle(x, y, cardWidth, cardHeight);

  // vertical cost line
  drawLine(x+cardWidth-(cardWidth/9), y, x+cardWidth-(cardWidth/9), y+(cardHeight/6));

  // line below name
  drawLine(x, y+(cardHeight/6), x+cardWidth, y+(cardHeight/6));

  // line below card type
  drawLine(x, y+(cardHeight/3), x+cardWidth, y+(cardHeight/3));

  // Card name
  drawString(x+2, y+(cardHeight/6)-2, name);

  // Card type
  drawString(x+2, y+(cardHeight/3)-2, "Ritual");
  
  // for cost
  ostringstream costStr;
  costStr << cost;
  string cost_output = costStr.str();
  drawCenteredString(((x+cardWidth-(cardWidth/9)+3)+(x+cardWidth))/2, y+24, cost_output);

  // charge cost box
  drawLine(x, y+cardHeight/2, x+cardWidth/9, y+cardHeight/2);
  drawLine(x+cardWidth/9, y+cardHeight/3, x+cardWidth/9, y+cardHeight/2);

  // charge cost output
  ostringstream chargecostStr;
  chargecostStr << ritual_cost;
  string chargecost_output = chargecostStr.str();
  drawCenteredString((x+x+2+cardWidth/9)/2, y+(cardHeight/2)-2,chargecost_output);
  
  // ritual description output
  drawWrappedString(x+2+cardWidth/9, y+(cardHeight/2)-2, ritual_desc, cardWidth-2-cardWidth/9);

  // number of charges output (and box)
  ostringstream chargesStr;
  chargesStr << ritual_charges;
  string charges_output = chargesStr.str();
  drawCenteredString((x+(7*cardWidth/9)+(x+cardWidth))/2, y+cardHeight-3, charges_output);
  drawLine(x+(7*cardWidth/9), y+(5*cardHeight/6), x+cardWidth, y+(5*cardHeight/6)); // horizontal
  drawLine(x+(7*cardWidth/9), y+(5*cardHeight/6), x+(7*cardWidth/9), y+cardHeight); // vertical
    
}

void Xwindow::graphics_display_spell(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc) {
  // card shell
  drawRectangle(x, y, cardWidth, cardHeight);

  // vertical cost line
  drawLine(x+cardWidth-(cardWidth/9), y, x+cardWidth-(cardWidth/9), y+(cardHeight/6));

  // line below name
  drawLine(x, y+(cardHeight/6), x+cardWidth, y+(cardHeight/6));

  // line below card type
  drawLine(x, y+(cardHeight/3), x+cardWidth, y+(cardHeight/3));

  // Card name
  drawString(x+2, y+(cardHeight/6)-2, name);

  // Card type
  drawString(x+2, y+(cardHeight/3)-2, "Spell");
  
  // for cost
  ostringstream costStr;
  costStr << cost;
  string cost_output = costStr.str();
  drawCenteredString(((x+cardWidth-(cardWidth/9)+3)+(x+cardWidth))/2, y+24, cost_output);

  // for description
  drawWrappedString(x+2, y+(cardHeight/2)-2, desc, cardWidth-2);
}

void Xwindow::graphics_display_enchantment_attack_defence(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc,std::string attack,std::string defence) {
  graphics_display_enchantment_general(x, y, cardWidth, cardHeight, name, cost, desc);

  // stats lines
  drawLine(x+(7*cardWidth/9), y+(5*cardHeight/6), x+cardWidth, y+(5*cardHeight/6)); // horizontal
  drawLine(x+(7*cardWidth/9), y+(5*cardHeight/6), x+(7*cardWidth/9), y+cardHeight); // vertical

  // for stats
  ostringstream statsStr;
  statsStr << attack << "/" << defence;
  string stats_output = statsStr.str();
  drawCenteredString((x+(7*cardWidth/9)+(x+cardWidth))/2, y+cardHeight-3, stats_output);

}
void Xwindow::graphics_display_enchantment(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc) {
  graphics_display_enchantment_general(x, y, cardWidth, cardHeight, name, cost, desc);  
}

// int player_num parameter not used, not sure if that really matters
void Xwindow::graphics_display_player_card(int x, int y, int cardWidth, int cardHeight, int player_num,std::string name,int life,int mana) {
  // card shell
  drawRectangle(x, y, cardWidth, cardHeight);

  // print name
  drawCenteredString(x+cardWidth/2, y+cardHeight/2, name);

  // life box (the one on the left)
  drawLine(x+cardWidth/9, y, x+cardWidth/9, y+cardHeight/6);
  drawLine(x, y+cardHeight/6, x+cardWidth/9, y+cardHeight/6);
  ostringstream healthStr;
  healthStr << life;
  string health_output = healthStr.str();
  drawCenteredString((x+x+cardWidth/9)/2,(y+cardHeight/6)-3, health_output);

  // mana box (the one on the right)
  drawLine(x+8*cardWidth/9, y, x+8*cardWidth/9, y+cardHeight/6);
  drawLine(x+8*cardWidth/9, y+cardHeight/6, x+cardWidth, y+cardHeight/6);
  ostringstream manaStr;
  manaStr << mana;
  string mana_output = manaStr.str();
  drawCenteredString(((x+8*cardWidth/9)+(x+cardWidth))/2, (y+cardHeight/6)-3, mana_output);
}

// Helpers...
void Xwindow::graphics_display_minion_general(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,int attack,int defence) {
  // card shell
  drawRectangle(x, y, cardWidth, cardHeight);

  // vertical cost line
  drawLine(x+cardWidth-(cardWidth/9), y, x+cardWidth-(cardWidth/9), y+(cardHeight/6));

  // line below name
  drawLine(x, y+(cardHeight/6), x+cardWidth, y+(cardHeight/6));

  // line below card type
  drawLine(x, y+(cardHeight/3), x+cardWidth, y+(cardHeight/3));

  // stats lines
  drawLine(x+(7*cardWidth/9), y+(5*cardHeight/6), x+cardWidth, y+(5*cardHeight/6)); // horizontal
  drawLine(x+(7*cardWidth/9), y+(5*cardHeight/6), x+(7*cardWidth/9), y+cardHeight); // vertical

  // Card name
  drawString(x+2, y+(cardHeight/6)-2, name);

  // Card type
  drawString(x+2, y+(cardHeight/3)-2, "Minion");
  
  // for cost
  ostringstream costStr;
  costStr << cost;
  string cost_output = costStr.str();
  drawCenteredString(((x+cardWidth-(cardWidth/9)+3)+(x+cardWidth))/2, y+24, cost_output);

  // for stats
  ostringstream statsStr;
  statsStr << attack << "/" << defence;
  string stats_output = statsStr.str();
  drawCenteredString((x+(7*cardWidth/9)+(x+cardWidth))/2, y+cardHeight-3, stats_output);

  // cost and description can be saved for specific function
}

void Xwindow::graphics_display_enchantment_general(int x, int y, int cardWidth, int cardHeight, std::string name,int cost,std::string desc) {
  // card shell
  drawRectangle(x, y, cardWidth, cardHeight);

  // vertical cost line
  drawLine(x+cardWidth-(cardWidth/9), y, x+cardWidth-(cardWidth/9), y+(cardHeight/6));

  // line below name
  drawLine(x, y+(cardHeight/6), x+cardWidth, y+(cardHeight/6));

  // line below card type
  drawLine(x, y+(cardHeight/3), x+cardWidth, y+(cardHeight/3));

  // Card name
  drawString(x+2, y+(cardHeight/6)-2, name);

  // Card type
  drawString(x+2, y+(cardHeight/3)-2, "Enchantment");
  
  // for cost
  ostringstream costStr;
  costStr << cost;
  string cost_output = costStr.str();
  drawCenteredString(((x+cardWidth-(cardWidth/9)+3)+(x+cardWidth))/2, y+24, cost_output);

  // for description
  drawWrappedString(x+2, y+(cardHeight/2)-2, desc, cardWidth-2);

  // stats can be saved for specific function
}

