#pragma once
#ifndef _SCHIFF_HPP_
#define _SCHIFF_HPP_

#include "ISchiff.hpp"

class Schiff : public ISchiff {
public:
  virtual ~Schiff();
  Schiff(int shell, int damage, int size);
  //   void move() override;
  void setHuelle(int value) override;
  void setSchaden(int value) override;
  void setGroesse(int value) override;
  //   void setx(int value) override;
  //   void sety(int value) override;
  //   void setXP(int value) override;
  int getHuelle() const override;
  int getSchaden() const override;
  int getGroesse() const override;
  //   int getx() const override;
  //   int gety() const override;
  //   int getXP() const override;

protected:
  int Huelle;
  int Schaden;
  int Groesse;
  //   int x;
  //   int y;
  //   int xp;
};

#endif
