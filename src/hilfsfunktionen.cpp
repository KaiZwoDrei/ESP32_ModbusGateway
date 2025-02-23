#include "hilfsfunktionen.h"

// String ist einer Nummer?
bool isNumeric(String str) {
  /*bool isNum;
  for(byte i=0;i<str.length();i++)
  {
    isNum = isDigit(str.charAt(i)) || str.charAt(i) == '+' || str.charAt(i) == '.' || str.charAt(i) == '-';
    if(!isNum) return false;
  }
  return true;*/

    unsigned int stringLength = str.length();
 
    if (stringLength == 0) {
        return false;
    } 
    bool zahl = false; 
    for(unsigned int i = 0; i < stringLength; ++i) {
        if (isDigit(str.charAt(i))) {
            continue;
        } 
        if (str.charAt(i) == '.') {
            if (zahl) {
                return false;
            }
            zahl = true;
            continue;
        }
        return false;
    }
    return true;
}

// auch Nachkomma runden
float runden(float in, byte nachkomma) {
  float shift = 1;
  while (nachkomma--) {
    shift *= 10;
  }
  return floor(in * shift + .5) / shift;
}
float runden(float in){
  return runden(in, 2); 
}
