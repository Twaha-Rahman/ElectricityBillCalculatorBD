#include "colorizer.h"
using namespace std;

Colorizer::Colorizer() : isActive{false}, currentColorCode{""} {}
Colorizer::Colorizer(string colorToSet)
    : isActive{true}, currentColorCode{colorToSet} {}
Colorizer::~Colorizer() { reset(); }

void Colorizer::reset() {

  isActive = false;
  currentColorCode = "";

  cout << "\033[0m";
}

bool Colorizer::isColoring() const { return isActive; }
string Colorizer::colorInUse() const { return currentColorCode; }

void Colorizer::setRedText() {
  isActive = true;
  currentColorCode = to_string(Red);

  setColor();
}

void Colorizer::setGreenText() {
  isActive = true;
  currentColorCode = to_string(Green);

  setColor();
}

void Colorizer::setYellowText() {
  isActive = true;
  currentColorCode = to_string(Yellow);

  setColor();
}

void Colorizer::setBlueText() {
  isActive = true;
  currentColorCode = to_string(Blue);

  setColor();
}

void Colorizer::setPurpleText() {
  isActive = true;
  currentColorCode = to_string(Purple);

  setColor();
}

void Colorizer::setCyanText() {
  isActive = true;
  currentColorCode = to_string(Cyan);

  setColor();
}

void Colorizer::setWhiteText() {
  isActive = true;
  currentColorCode = to_string(White);

  setColor();
}
