/**
* @authors Jason Chung, Nick Friesen, Kenny Galang, Sama Rahimian
*
* @brief: This class can make and retrieve a cookie.
*
* This class can create and retrieve a cookie.
*
*/

#include "cookie.hpp"

Cookie::Cookie(){}

/**@brief Gets the cookie by name and returns the value stored inside
*
* Gets the cookie by name and returns the value stored inside
*
* @param name takes in string that is name of the cookie.
* @return value the value stored in the cookie as a string
*/
std::string Cookie::getCookie(std::string name){
  std::string value;
  std::fstream fileIn;
  std::string fileSearch = name + ".txt";

  fileIn.open(fileSearch, std::ios::in);
  if(!fileIn){  //no file found
    fileIn.close();
    return "cookieCrumbs";
  }

  //get password from first line of file
  fileIn >> value;

  return value;
}

/** @brief Creates cookie
 *
 * Creates a simple cookie file.
 *
 * @param: name takes in string and creates name for cookie
 * @param: value takes in pointer
 * @return void
*/
void Cookie::setCookie(std::string name, std::string value){
  std::fstream fileOut;
  fileOut.open(name + ".txt", std::ios::out);

  //write data to file;
  fileOut << value << std::endl;

  fileOut.close();
}
