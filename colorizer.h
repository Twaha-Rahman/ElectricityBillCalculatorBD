#if !defined(COLORIZER_H)
#define COLORIZER_H

#include <iostream>
using namespace std;

class Colorizer {
private:
  bool isActive;
  string currentColorCode;

  string prefix{"\033["};
  string postfix{"m"};

  void setColor() {
    string ansiText = prefix + currentColorCode + postfix;
    cout << ansiText;
  }

protected:
  enum ansiForgroundColorCodes {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Purple = 35,
    Cyan = 36,
    White = 37
  };

  enum ansiBackgroundColorCodes {
    bgBlack = 30,
    bgRed,
    bgGreen,
    bgYellow,
    bgBlue,
    bgPurple,
    bgCyan,
    bgWhite
  };

public:
  Colorizer();
  Colorizer(string colorToSet);
  ~Colorizer();

  void reset();

  bool isColoring() const;
  string colorInUse() const;

  void setRedText();
  void setGreenText();
  void setYellowText();
  void setBlueText();
  void setPurpleText();
  void setCyanText();
  void setWhiteText();
};

#endif
