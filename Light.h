#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/Http/Client>
#include <Wt/WIOService>
#include <iostream>
#include "Function.h"
#include <Wt/Json/Object>


class Light{
	bool groupState;
	int bulbSize;
    std::string str1;
    std::string group1;
	std::string bulb;
	bool currentToggle;
	Function thisIsLight;
	bool groupToggle;
	bool schedTog;
	int schedSize;
	std::string schedule1;
	std::string arraySched;
	std::string scheduleBri;
	std::string logString;
	std::string groupString;
	int groupSize;

public:

	std::string getSchedArr();
	std::string getGroupArr();
	void setGroupArr(std::string groupString);
	int getGroupsize();
	void setGroupsize(int groupSize);
	void setSchedArr(std::string arraySched);
	void setGB(bool groupState);
	bool getGB();

	std::string getLogString();
	void setLogString(std::string logString);


	void setSched(bool schedTog);
	bool getSched();


	void setSchedBri(std::string scheduleBri);
	std::string getSchedBri();
	
	


	void setSchedString(std::string schedule1);
	std::string getSchedString();
	void setBulbsize(int bulbSize){
		this->bulbSize = bulbSize;
	}
	int getBulbsize(){
		return bulbSize;
	}
	void setSchedsize(int schedSize);
	int getSchedsize();

	std::string getStr();

    std::string getG();

    void setG(std::string group1);
    
	void setStr(std::string str1);

	int groupNum = 1;
	
	int getGNum();

	std::string getBulb();

	void setBulb(std::string bulb);

	bool getGT();
	
	void setGT(bool groupToggle);

	bool getCT();

	void setCT(bool currentToggle);

	Function getLight();

	void setLight(Function thisIsLight);

};