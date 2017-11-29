#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/Http/Client>
#include <Wt/WIOService>
#include <iostream>
// #include "Hello.h"
#include <Wt/Json/Object>

class Function{
	
public:
  // bool toggle;
  // Function getLight();
  void testSched();
  void testSchedT(boost::system::error_code err, const Wt::Http::Message& response);
  void addTimer();
  void handleHttpResponseG(boost::system::error_code err, const Wt::Http::Message& response);
  void getGroupState();
  void schedTests();
  void schedObjects(boost::system::error_code err, const Wt::Http::Message& response);
  
  void testLogoutT(boost::system::error_code err, const Wt::Http::Message& response);
  void testLogout();

  void groupObjects(boost::system::error_code err, const Wt::Http::Message& response);
  void groupTests();
  void testGroupT(boost::system::error_code err, const Wt::Http::Message& response);
  void testGroup();

  void getState();
  // void parseMe();
  void handleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response);
  void turnMeOn1();
  void turnMeOff1();
  // void createLight();
  void testState();
  void testResponse(boost::system::error_code err, const Wt::Http::Message& response);
  void turnGroupOn();

  void turnGroupOff();
  // void getGroupState();
  void bulbTests();
  void bulbObjects(boost::system::error_code err, const Wt::Http::Message& response);

  // void lightNameFunction();
  // void groupOnOff();
   // void spitInfo();
   // void callMe();
   // void brightnessFunction(int valueMe);
   // void satFunction(int valueMe);
  // void satSet();
  // void brightnessSet();
      // void turnSingle();
    // void callThis();
    // void colFunction(int valueMe);
  void turnSchedOff();
  void turnSchedOn();
};
