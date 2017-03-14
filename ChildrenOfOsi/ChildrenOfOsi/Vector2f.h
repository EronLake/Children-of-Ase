#pragma once

#include "stdafx.h"

class Vector2f
{
  public:

  float xloc;
  float yloc;

  Vector2f(): xloc(0), yloc(0) {}
  Vector2f(float x, float y): xloc(x), yloc(y) {}
  Vector2f(const Vector2f&) = default;
  Vector2f(Vector2f&&) = default;
  Vector2f& operator=(const Vector2f&) = default;
  Vector2f& operator=(Vector2f&&) = default;
  ~Vector2f() = default;

  float getXloc() { return this->xloc; };
  float getYloc() { return this->yloc; };

  void setXloc(float x) { this->xloc = x; };
  void setYloc(float y) { this->yloc = y; };
  void shiftXloc(float dist) { this->xloc += dist; };
  void shiftYloc(float dist) { this->yloc += dist; };

  float dist(Vector2f end);

  bool operator==(const Vector2f& that) const { return this->xloc == that.xloc && this->yloc == that.yloc; };
  bool operator!=(const Vector2f& that) const  { return !(this->xloc == that.xloc && this->yloc == that.yloc); };
  bool operator<(const Vector2f& that) const  { return this->xloc < that.xloc || (!(that.xloc < this->xloc)) && (that.yloc < this->yloc); };
  bool operator<=(const Vector2f& that) const  { return (this->xloc < that.xloc || this->yloc < that.yloc) || (this->xloc == that.xloc && this->yloc == that.yloc); }
  bool operator>(const Vector2f& that) const  { return !((this->xloc < that.xloc || this->yloc < that.yloc) || (this->xloc == that.xloc && this->yloc == that.yloc)); }
  bool operator>=(const Vector2f& that) const  { return !(this->xloc < that.xloc || this->yloc < that.yloc); }
};

