/**
* @authors Jason Chung, Nick Friesen, Kenny Galang, Sama Rahimian
*
* @brief The basic requirments that user must have.
*
* User allows for getting and setting email, password, and the lightdata.
*
*/

#include "user.hpp"

User::User(){}

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
std::string User::getEmail(void){
  return this->Email;
}

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
void User::setEmail(std::string email){
  this->Email = email;
}

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
std::string User::getPassWord(void){
  return this->PassWord;
}

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
void User::setPassWord(std::string password){
  this->PassWord = password;
}

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
std::string User::getLightData(void){
  return this->LightData;
}

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
void User::setLightData(std::string jsonData){
  this->LightData = jsonData;
}
