/**
* @authors Jason Chung, Nick Friesen, Kenny Galang, Sama Rahimian
*
* @brief A simple app for users to login and new users to register
*
* A simple login page for the user to enter their email and password for authentication and loading of their personal account. There is "Sign up" button for new users to create their own custom account
*
*/

#include "login.hpp"


Profile userProfile;


Login::Login(const Wt::WEnvironment &env) : WApplication (env){
  root()->addWidget(new Wt::WText("<h1>&#128161;<label style=\"background-color: #b2c6fe;\">Welcome to </label><label style=\"background-color: #fed766;\">Lumineux</label>&#128161;</h1>"));
  Wt::WText *intro = new Wt::WText("<p><b><i>Lumineux</i></b> is your friendly Hue Lights System for controlling your new Hue Lights. Setup is as easy as giving students 100% on their assignment. You'll be up and shining in no time.</p>");
  intro->setStyleClass("intro");
  root()->addWidget(intro);
  root()->addWidget(new Wt::WBreak());
  root()->addWidget(new Wt::WBreak());

  // Login
  loginContainer = new Wt::WContainerWidget(root());
  Login::pageLogin();
  loginContainer->setStyleClass("login");


  root()->addWidget(new Wt::WBreak());
  root()->addWidget(new Wt::WBreak());

}

/** Creates the elements neccessary for user to enter identification information to login.
*
* Creates the elements neccessary for user to enter identification information to login
*
* @param void
* @returns void
*/
void Login::pageLogin(){
    //create input fields
    Email_ = new Wt::WLineEdit(loginContainer);
    Email_->setPlaceholderText("Email");
    Email_->setFocus();

    PassWord_ = new Wt::WLineEdit(loginContainer);
    PassWord_->setPlaceholderText("Password");
    PassWord_->setEchoMode(Wt::WLineEdit::EchoMode::Password);
    PassWord_->setFocus();

    //create buttons
    Wt::WPushButton *buttonLogIn;
    buttonLogIn = new Wt::WPushButton("Log in", loginContainer);
    buttonLogIn->setStyleClass("btn log");
    Wt::WPushButton *buttonSignUp;
    buttonSignUp = new Wt::WPushButton("Sign up", loginContainer);
    buttonSignUp->setStyleClass("btn sgn");

    //button actions
    buttonLogIn->clicked().connect(this, &Login::LoginProfile);
    buttonLogIn->enterPressed().connect(boost::bind(&Login::LoginProfile, this));
    buttonSignUp->clicked().connect(this, &Login::pageRegister);
    buttonSignUp->clicked().connect(buttonSignUp, &Wt::WPushButton::disable);

    //handle error messages
    errMsg = new Wt::WText();
    errMsg->setText("");
    errMsg->setStyleClass("err");

    //add everything to container
    loginContainer->addWidget(errMsg);
    loginContainer->addWidget(Email_);
    loginContainer->addWidget(PassWord_);
    loginContainer->addWidget(buttonLogIn);
    loginContainer->addWidget(buttonSignUp);

}

/** @brief Creates a container and adds all the elements neccessary for user registration.
*
* Creates a container and adds all the elements neccessary for user registration.
*
* @param void
* @returns void
*/
void Login::pageRegister(){
  //create containers and set styles
  signUpContainer = new Wt::WContainerWidget(root());
  signUpContainer->setStyleClass("register");

  Wt::WGroupBox *regBox = new Wt::WGroupBox("Sign Up");
  regBox->resize(420, Wt::WLength::Auto);
  regForm = new Wt::WTemplate(regBox);

  //create input fields
  regForm->bindWidget("userID-input", RegEmail_ = new Wt::WLineEdit());
  RegEmail_->setPlaceholderText("name@example.com");
  regForm->bindWidget("PssWrd-input", RegPW_ = new Wt::WLineEdit());
  RegPW_->setEchoMode(Wt::WLineEdit::EchoMode::Password);
  regForm->bindWidget("confPssWrd-input", ConfirmPW_ = new Wt::WLineEdit());
  ConfirmPW_->setEchoMode(Wt::WLineEdit::EchoMode::Password);

  //create button
  Wt::WPushButton *buttonRegister;
  regForm->bindWidget("reg-button", buttonRegister = new Wt::WPushButton("Register", regBox));
  buttonRegister->setStyleClass("btn reg");

  //error handling
  regForm->bindWidget("errReg", errReg = new Wt::WText(regBox));
  errReg->setText(" ");

  //Text to display
  regForm->setTemplateText("All fields with <label class=\"err\">*</label> are requried. <div class=\"err\">${errReg}</div><div><label class=\"err\">*</label>E-mail: ${userID-input}<br /><label class=\"err\">*</label>Password: ${PssWrd-input}<br /><label class=\"err\">*</label>Confirm Password: ${confPssWrd-input}</div><div style=\"text-align: center; \">${reg-button}</div>");

  //button action and add everything to main container
  buttonRegister->clicked().connect(this, &Login::RegisterProfile);
  buttonRegister->enterPressed().connect(boost::bind(&Login::RegisterProfile, this));
  signUpContainer->addWidget(regBox);

}

/** @brief Function will check user inputs of email, password, and confirmation password for validity and then creates a new profile with default light settings and redirects to main lights page
*
* Function will check user inputs of email, password, and confirmation password for validity and then creates a new profile with default light settings and redirects to main lights page
*
* @param void
* @returns void
*/
void Login::RegisterProfile(){
  Auth auth;
  Cookie ovenReadyFresh;

  //convert Email_
  Wt::WString temp1 = RegEmail_->text();
  std::wstring temp2 = temp1.value();
  std::string em = std::string(temp2.begin(), temp2.end());

  //convert PassWord_
  Wt::WString tempA = RegPW_->text();
  std::wstring tempB = tempA.value();
  std::string pw = std::string(tempB.begin(), tempB.end());

  //convert ConfirmPW_
  Wt::WString tempX = ConfirmPW_->text();
  std::wstring tempY = tempX.value();
  std::string pwConfirm = std::string(tempY.begin(), tempY.end());

  if(em != "" && pwConfirm !="" && pw != ""){
    if(auth.checkEmail(em)){
      if(auth.dupID(em))
          errReg->setText("You are already registered.");
      else if(auth.checkPassWord(pw, pwConfirm)){
        Profile newUser(em, pw);
        userProfile = newUser;
        userProfile.exportUser();
        ovenReadyFresh.setCookie("yummy", "true");
        redirect("/lights");
      }
      else
        errReg->setText("Your passwords do not match.");
    }
    else
      errReg->setText("Error with your email format.");
  }
  else
    errReg->setText("Fields are empty.");
}

/** @brief Will process the user login credentials for authentication. Will prompt user if incorrect information. If credentials are authenticate wil redirect to main lights page.
*
* Will process the user login credentials for authentication. Will prompt user if incorrect information. If credentials are authenticate wil redirect to main lights page.
*
* @param void
* @returns void
*/
void Login::LoginProfile(){
  Cookie snack;

  //convert Email_
  Wt::WString temp1 = Email_->text();
  std::wstring temp2 = temp1.value();
  std::string em = std::string(temp2.begin(), temp2.end());

  //convert PassWord_
  Wt::WString tempA = PassWord_->text();
  std::wstring tempB = tempA.value();
  std::string pw = std::string(tempB.begin(), tempB.end());

  if(em != "" && pw != ""){
    if(userProfile.importUser(em, pw) == 0){
      userProfile.importUser(em,pw);
      // Wt::WApplication *app = WApplication::instance();
      // app->setCookie("yummy", "true",7200,"t.com");
      snack.setCookie("yummy", "true");
      redirect("/lights");
    }
    else if(userProfile.importUser(em, pw) < 0)
      errMsg->setText("Incorrect email or password.");
    else if(userProfile.importUser(em, pw) > 0)
      errMsg->setText("You don't have an account with us. Please register to use the service.");
  }
  else
    errMsg->setText("Fields are empty.");

}

//create the applications
Wt::WApplication *createLogin(const Wt::WEnvironment& env){
  Wt::WApplication *app = new Login(env);
  app->setTitle("Lumineux");
  app->useStyleSheet("css/login.css");
  return app;
}

// int main(int argc, char **argv){
//   return Wt::WRun(argc, argv, &createLogin);
// }
