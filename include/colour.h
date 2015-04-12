#ifndef _COLOUR_H_
#define _COLOUR_H_

class Colour {
public:
  float red;
  float green;
  float blue;
  float alpha;
  
  Colour(void);
  Colour(float pred, float pgreen, float pblue, float palpha);

  void clear(void);
  void set(float pred, float pgreen, float pblue, float palpha);
  float getRed(void);
  float getGreen(void);
  float getBlue(void);
  float getAlpha(void);

  void add(Colour c);
  Colour changeDivide(float scalar);
  Colour returnDivide(float scalar);
  void multiply(Colour c);
  void multiply(float scalar);
  void scaleLuminance(float scalar);
};

#endif