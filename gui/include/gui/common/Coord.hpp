#ifndef COORD_HPP
#define COORD_HPP

class Coord
{
private:
  int _x;
  int _y;

public:
  Coord(int x=0, int y=0) : _x{x}, _y{y} {}
  ~Coord();

  int getX() const {return _x;}
  int getY() const {return _y;}

  Coord operator+ (Coord b) {return Coord(getX() + b.getX(), getY() + b.getY());}
  Coord operator- (Coord b) {return Coord(getX() - b.getX(), getY() - b.getY());}
};



#endif