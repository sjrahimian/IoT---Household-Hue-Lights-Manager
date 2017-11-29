#ifndef AUTH_HPP
#define AUTH_HPP

#include "seaLib.hpp"

class Auth{
public:
  Auth();
  bool checkEmail(std::string email);
  bool dupID(std:: string id);
  bool checkPassWord(std::string pw1, std::string pw2);
  std::string passWordCipher(std::string password);

};


#endif
