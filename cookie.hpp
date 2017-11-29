#ifndef COOKIE_HPP
#define COOKIE_HPP

#include "seaLib.hpp"

class Cookie{
public:
  Cookie();
  std::string getCookie(std::string name);
  void setCookie(std::string name, std::string value);

};

#endif
