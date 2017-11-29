#ifndef USER_HPP
#define USER_HPP

#include "seaLib.hpp"

class User{
public:
  User();
  std::string getEmail(void);
  void setEmail(std::string email);
  std::string getPassWord(void);
  void setPassWord(std::string password);
  std::string getLightData(void);
  void setLightData(std::string data);

private:
  std::string PassWord;
  std::string Email;
  std::string LightData;

};

#endif
