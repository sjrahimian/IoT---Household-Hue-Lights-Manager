#ifndef MAINFILE_HPP
#define MAINFILE_HPP

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WGroupBox>
#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/Http/Client>
#include <Wt/WIOService>
#include <Wt/WCheckBox>
#include <iostream>
#include "MainFile.h"
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/WSlider>
#include <Wt/Json/Array>
#include <Wt/WContainerWidget>
#include <Wt/Json/Serializer>
#include "Light.h"
#include <unistd.h>
#include <Wt/Dbo/Json>
#include <thread>
#include <chrono>
#include "login.hpp"
#include "cookie.hpp"


#include <vector>



class MainFile : public Wt::WApplication
{
public:
    MainFile(const Wt::WEnvironment& env);

private:
    
    Wt::WContainerWidget *menucontainer;
    Wt::WStackedWidget *lightstack;
    Wt::WMenu *lightmenu;

    Wt::WContainerWidget *lightcontainer;
    Wt::WContainerWidget *groupcontainer;
    Wt::WContainerWidget *schedulecontainer;
    

    Wt::WLineEdit *brightnessNumber;
    Wt::WPushButton *goIP;
    Wt::WPushButton *goPort;
    Wt::WPushButton *logoutButt;
    Wt::WLineEdit *getIP;
    Wt::WLineEdit *getPort;
    Wt::WLineEdit *satNumber;
    Wt::WLineEdit *textLight;
    Wt::WLineEdit *nameLight;
    Wt::WLineEdit *scheduleGroupH;
    Wt::WLineEdit *scheduleGroupM;
    Wt::WLineEdit *scheduleGroupS;
    Wt::WLineEdit *brightnessSched;
    Wt::WLineEdit *groupName;
    Wt::WLineEdit *satSchedT;
    Wt::WLineEdit *colSchedT;
    Wt::WLineEdit *deleteMe;
    Wt::WLineEdit *nameMe;
    Wt::WLineEdit *delG;
    Wt::WText *bulbArray;
    Wt::WText *schedule1;
    Wt::WText *scheduleDeal;
    Wt::WText *schedule;
    Wt::WText *testBox;
    Wt::WText *deleteSched;
    Wt::WText *nameSched;
    Wt::WText *groupLister;
    Wt::WText *groupText;
    Wt::WText *onOff;
    Wt::WCheckBox *w1;
    Wt::WCheckBox *w2;
    Wt::WCheckBox *w3;
    Wt::WLineEdit *textGroup;
    void game();
    std::string totalString;
    void pickSched(int one);
    void levelOne();
    void glow();
    void rave();
    void christmas();
    void deleteGroup();


    void setPort();
    void setIP();
    void deleteSchedFunc();
    void toggleSched();
    void colAllGroupFunction(int valueMe);
    void addTimer();
    void brightnessGroupFunction(int valueMe);
    void satGroupFunction(int valueMe);
    void makeGp(std::string msg);
    void lightNameFunction();
    void groupOnOff();
    void colGroupFunction(int valueMe);
    void spitInfo();
    void spitGroup();
    void callMe();
    void brightnessFunction(int valueMe);
    void satFunction(int valueMe);
    void satSet();
    void brightnessSet();
    void greet4();
    void callThis();
    void getLights();
    void colFunction(int valueMe);
    void logOut();

};

Wt::WApplication *createMainFile(const Wt::WEnvironment& env);

#endif
