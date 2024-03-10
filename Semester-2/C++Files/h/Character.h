#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
  Character();
  Character(int x, int y);

  int getX() const;
  int getY() const;

  void setX(int x);
  void setY(int y);

  void move(char direction);

protected:
  int x;
  int y;

private:
  bool validateCoordinates(int coordinate) const;
};

#endif // CHARACTER_H
