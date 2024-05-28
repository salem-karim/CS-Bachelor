#pragma once
#ifndef _ISCHIFF_HPP_
#define _ISCHIFF_HPP_

class ISchiff {
public:
  virtual ~ISchiff() {}
  virtual void attack(ISchiff *target) = 0;
  // virtual void move() = 0;
  virtual void setHuelle(int value) = 0;
  virtual void setSchaden(int value) = 0;
  virtual void setGroesse(int value) = 0;
  virtual void setIsSunk(bool value) = 0;
  virtual void setx(int value) = 0;
  virtual void sety(int value) = 0;
  // virtual void setXP(int value) = 0;
  virtual int getHuelle() const = 0;
  virtual int getSchaden() const = 0;
  virtual int getGroesse() const = 0;
  virtual bool getIsSunk() const = 0;
  virtual int getx() const = 0;
  virtual int gety() const = 0;
  // virtual int getXP() const = 0;
};

#endif
