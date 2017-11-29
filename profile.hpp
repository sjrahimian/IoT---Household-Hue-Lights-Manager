/**
*/

#ifndef PROFILE_HPP
#define PROFILE_HPP

#include "seaLib.hpp"
#include "user.hpp"
#include "auth.hpp"

class Profile : public User{
public:
  Profile();
  Profile(std::string emailNew, std::string passwordNew); //new user profile
  void importHelper(std::string email, std::string password, std::string data, std::string fn);  //set user profile
  int importUser(std::string email, std::string password);  //Import user profile
  bool exportUser(void); //export user profile
  std::string changePassWord(std::string currentPW, std::string newPW, std::string confirmNewPW);

private:
  std::string fileName = "database/";
  std::string defaultLights = "Lorem ipsum dolor sit amet,..."; //temp placeholder text
  Auth auth;

};

#endif
