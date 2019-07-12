// 
// MIT License
// 
// Copyright (c) 2019 Ross Newman (ross@rossnewman.com)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// 

#ifndef RENDERER_H
#define RENDERER_H
#include "debug.h"

#define MAX_HANDLES 10

#define AMBER 255, 153, 0
#define WHITE 255, 255, 255
#define RED 255, 0, 0
#define GREY 127, 127, 127
#define MEDIUM_GREY 96, 96, 96
#define DARK_GREY 64, 64, 64
#define GREEN 0, 255, 0
#define DARK_GREEN 0, 128, 0
#define DARK_GREEN2 0, 75, 0
#define BLUE 0, 0, 255
#define CYAN 0, 255, 255
#define DARK_BLUE 51, 102, 153
#define LIGHT_BLUE 50, 50, 255
#define BLACK 0, 0, 0
#define YELLOW 255 , 255, 0
#define ORANGE 255,165,0
#define NONE -1, -1, -1


struct colour_type
{
  int red;
  int green;
  int blue;
};

struct point_type
{
  int x;
  int y;
};

struct resolution_type
{
  int width;
  int height;
  int depth;
};

class rendererSdl;
class rendererCairo;

class renderer
{
public:
  int init (int width, int height);
  virtual void setPixel (int x, int y) = 0;
  virtual void setColour (int red, int green, int blue) = 0;
  virtual void setColourForground (int red, int green, int blue) = 0;
  virtual void setColourBackground (int red, int green, int blue) = 0;
  int getWidth () { return width_; };
  int getHeight () { return height_; };
  virtual int drawLine (int x1, int y1, int x2, int y2) = 0;
  virtual void drawCircle (int x, int y, int radius, bool fill) = 0;
  virtual void drawRectangle (int x1, int y1, int x2, int y2, bool fill) = 0;
  virtual int drawColor (int r, int g, int b) = 0;
  virtual int textureRGB (int x, int y, void *buffer, char *file) = 0;
  virtual void scale (float x) = 0;
  virtual void present () = 0;
private:
  int height_;
  int width_;
  colour_type forground_colour_;
  colour_type background_colour_;
  friend class rendererSdl;
  friend class rendererCairo;
};

#endif
