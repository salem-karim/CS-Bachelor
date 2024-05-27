cmake_minimum_required(VERSION 3.27)
project(Flottenkampf)

set(CMAKE_CXX_STANDARD 14)

add_executable(
  Flottenkampf
  main.cpp
  Spiel/Spiel.cpp,
  Schiff/Schiff.cpp
  Schiff/ISchiff.cpp,
  Jaeger/Jaeger.cpp,
  Kreuzer/Kreuzer.cpp,
  Zersoerer/Zersoerer.cpp)
