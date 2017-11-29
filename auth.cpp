
#include "auth.hpp"

Auth::Auth(){}

/* Check to see if email/ID is properly formatted by looking for '@' and period
* @param: id - takes the string to be checked
* @return: 'false' if one or the other is not found
*           'true' if both are found
*/
bool Auth::checkEmail(std::string id){
  std::size_t at = id.find("@");
  std::size_t period = id.find(".");

  if(at == std::string::npos || period == std::string::npos)
    return false;
  else
    return true;

}

/* Search for duplicate email/ID in database
* @param: id - string to be checked
* @return: 'false' if no duplicate of email/userID found
*           'true' if duplicate email/UserID found
*/
bool Auth::dupID(std:: string id){
  std::fstream fileIn;
  std::string idCheck = "database/" + id + ".txt";

  fileIn.open(idCheck, std::ios::in);
  if(fileIn){  //no file found
    fileIn.close();
    return true;
  }
  else{
    fileIn.close();
    return false;
  }

}

/**check two passwords to see if they are identical.
* @param: pw1 - first password to be compared
*         pw2 - second password to be compared
* @return: 'true' if passowrds match
*          'false' if passwords don't match
*/
bool Auth::checkPassWord(std::string pw1, std::string pw2){
  if (pw1.compare(pw2) == 0)//match
    return true;
  else
    return false;
}

/** Encryption using ceaser cipher method
* @param: password - user's password to be encripted
*/
std::string Auth::passWordCipher(std::string password){
  std::string ccipher = "";
  int num = 55;

  for(int i=0; i<password.length(); i++){
    if(isupper(password[i]))  //encrypt uppercase
      ccipher = ccipher + char(int(password[i]+num-65)%26 +65);
    else  //encrypt lowercase
      ccipher = ccipher + char(int(password[i]+num-97)%26 +97);
  }

  return ccipher;
}


/* Class tester */
// int main(int argc, char **argv){
//   std::string u = "sama@uwo.ca";
//   std::string _u = "somethi.ingcom";
//   std::string p = "1234";
//   std::string _p = "asdf7980!@#$";
//
//   Auth testing;
//
//   std::cout<<"passWordCipher:: " + testing.passWordCipher(p) + " == " + testing.passWordCipher(p) +" != " + testing.passWordCipher(_p) << "\n\n";
//
//   std::cout<< "Email Check test:: False==" << testing.checkEmail(_u) << std::endl;
//   std::cout<< "Email Check test:: True==" << testing.checkEmail(u) << "\n\n";
//
//   std::cout<< "PassWord Check test:: False==" << testing.checkPassWord(_p, p) << std::endl;
//   std::cout<< "PassWord Check test:: True==" << testing.checkPassWord(_p, _p) << std::endl;
//   std::cout<< "PassWord Check test:: True==" << testing.checkPassWord(p, p) << "\n\n";
//
//
//   return 0;
// }
