#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "wittyLib.hpp"
#include "profile.hpp"
#include "cookie.hpp"

class Login : public Wt::WApplication{
public:
  Login(const Wt::WEnvironment &env);

private:
  Wt::WLineEdit *Email_;
  Wt::WLineEdit *PassWord_;
  Wt::WLineEdit *RegEmail_;
  Wt::WLineEdit *RegPW_;
  Wt::WLineEdit *ConfirmPW_;
  Wt::WContainerWidget *signUpContainer;
  Wt::WContainerWidget *loginContainer;
  Wt::WTemplate *loginView;
  Wt::WTemplate *regForm;
  Wt::WText *errMsg; ///Error message to be displayed for loginView
  Wt::WText *errReg; ///Error message to be displayed
  void pageRegister();
  void pageLogin();
  void LoginProfile();
  void RegisterProfile();

};

Wt::WApplication *createLogin(const Wt::WEnvironment& env);
extern Profile userProfile;

#endif
