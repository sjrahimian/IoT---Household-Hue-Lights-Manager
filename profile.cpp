/**
* @authors Jason Chung, Nick Friesen, Kenny Galang, Sama Rahimian
*
* @brief Profile will set up, retrieve, and export user account information.
*
* Profile will set up, retrieve, and export user account information
*
*/

#include "profile.hpp"

/** @brief Blank constructor.
*
*New default user profile from 'create account' feature. Note: Authentication should have occured before using this function.
*
* @param emailNew Takes a email.
* @param passwordNew Takes a password.
* @return void.
*/
Profile::Profile(){}

/** @brief New default user profile from 'create account' feature.
*
*New default user profile from 'create account' feature. Note: Authentication should have occured before using this function.
*
* @param emailNew Takes a email.
* @param passwordNew Takes a password.
* @return void.
*/
Profile::Profile(std::string emailNew, std::string passwordNew){
  this->setEmail(emailNew);
  std::cout<<getEmail()<<"<----------\n";
  this->setPassWord(auth.passWordCipher(passwordNew));
  this->setLightData(this->defaultLights);

  this->fileName = this->fileName + emailNew + ".txt";
  // std::size_t at = emailNew.find("@"); //old method of saving text files; keep in case of error
  //this->fileName = this->fileName + emailNew.substr(0, at) + ".txt";

}

/** @brief Set user profile.
* @param email - takes string from main login page
* @param password - takes string from main login page
* @param data - is the light information stored in the text file
* @param fn - is the fileName for saving the details
*/
void Profile::importHelper(std::string email, std::string password, std::string data, std::string fn){
  this->setEmail(email);
  this->setPassWord(password);
  this->setLightData(data);
  this->fileName = fn;

  // return this->user.getLightData();
}


/** @brief Import user profile.
*
* This function imports a user profile, represented by an emai and password
* @param: email - takes email from login page
*         password - takes password from login page
* @return: '0' if file found and successfully loaded file information
*          '-1' - email formating or password entered incorrectly
*          '1' - file not found
*/
int Profile::importUser(std::string email, std::string password){
  std::string fileSearch;
  std::string filePssWrd;
  std::string fileData;
  std::fstream fileIn;

  std::string modifiedPssWrd = auth.passWordCipher(password);
  if(auth.checkEmail(email)){
    fileSearch = "database/" + email + ".txt";
  }
  else{  //incorrect email
    return -1;
  }

  fileIn.open(fileSearch, std::ios::in);
  if(!fileIn){  //no file found
    fileIn.close();
    return 1;
  }

  //get password from first line of file
  fileIn >> filePssWrd;
  if(auth.checkPassWord(modifiedPssWrd, filePssWrd)){//get remaining data and load account
    fileIn >> fileData;
    Profile::importHelper(email, filePssWrd, fileData, fileSearch);
    fileIn.close();
    return 0;
  }
  else{ //incorrect password
    fileIn.close();
    return -1;
  }

}

/**@brief Export user profile
*
* This function exports user results by writing their info to a text file
* @return: 'true' on successful export, else 'false'
*/
bool Profile::exportUser(void){
  std::fstream fileOut;
  fileOut.open(this->fileName, std::ios::out);

  //write data to file;
  fileOut << this->getPassWord() << std::endl;
  fileOut << "\r\n";
  fileOut << this->getLightData() << std::endl;

  fileOut.close();
  return true;

}


/** @brief Change user's password
*
* This function changes a users password, by first authorizing their password and supplying a new one
* @param: currentPW - user's current password
*         newPW - the new password the user wants
*         confirmNewPW - user must enter new password twice to ensure correct
* @return: if account belongs to current user, AND current password does not match
*          the new password AND new password matches the confirmation password, then
*          change password and return string success
*          Else returns proper response to show error
*/
std::string Profile::changePassWord(std::string currentPW, std::string newPW, std::string confirmNewPW){
  if(auth.checkPassWord(currentPW, newPW))  //if identical
    return "Your current password and new password cannot be identical.";

  if(!auth.checkPassWord(newPW, confirmNewPW)){ //if not identical
    return "Your new password and the confirmation password do not match.";
  }

  std::string modCurrentPW = auth.passWordCipher(currentPW);
  if(auth.checkPassWord(this->getPassWord(), modCurrentPW)){
    this->setPassWord(auth.passWordCipher(newPW));
    return "Change saved.";
  }
  else{
    return "Using someone elses account is not taken lightly by Lumineux. Please logout and sign into your account.";
  }

}
