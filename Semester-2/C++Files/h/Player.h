//
// Created by karim on 22.02.24.
//

#ifndef CS_BACHELOR_PLAYER_H
#define CS_BACHELOR_PLAYER_H

class Player {
public:
  Player();
  Player(int x, int y);

  int getX() const;
  int getY() const;

  void setX(int x);
  void setY(int y);

  void move(char direction);

private:
  int x;
  int y;
  bool validateCoordinates(int coordinate) const;
};

#endif // CS_BACHELOR_PLAYER_H
