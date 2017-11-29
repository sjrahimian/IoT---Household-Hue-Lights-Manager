#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/Http/Client>
#include <Wt/WIOService>
#include <iostream>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include "Light.h" 

#include <Wt/WSlider>
#include <Wt/Json/Array>
#include <Wt/WContainerWidget>
#include <Wt/Json/Serializer>

	/**
	 * @authors Kenneth Galang, Jason Chung, Nick Friesen, Sama Rahimian
	 * @brief description This file contains the variables in which manipulate the program
	 *
     * This is the class that allows the user to manipulate variables with information from GET requests and POST/PUT requests.
	 */


    /**
     * @brief Function gets a string of the groups
     *
     * This function gets the whole array of the groups from a GET request
     */
	std::string Light::getGroupArr(){
		return groupString;
	};

    /**
     * @brief Function sets a string of the groups
     *
     * This function sets the whole array of the groups from a GET request
     */
	void Light::setGroupArr(std::string groupString){
		this->groupString = groupString;
	};

    /**
     * @brief Function gets a size of the groups
     *
     * This function gets the whole size of the groups from a GET request
     */
	int Light::getGroupsize(){
		return groupSize;
	}

    /**
     * @brief Function sets a size of the groups
     *
     * This function sets the whole size of the groups from a GET request
     */
	void Light::setGroupsize(int groupSize){
		this->groupSize = groupSize;
	}

    /**
     * @brief Function sets the log of the user
     *
     * This function sets the whole string of the log from a GET request
     */
	void Light::setLogString(std::string logString){
		this->logString = logString;
	};

    /**
     * @brief Function gets the log of the user
     *
     * This function gets the whole string of the log from a GET request
     */
	std::string Light::getLogString(){
		return logString;
	};


    /**
     * @brief Function gets the array of the schedules
     *
     * This function gets the whole array of schedules of the log from a GET request
     */
	std::string Light::getSchedArr(){
		return arraySched;
	};

    /**
     * @brief Function sets the array of the schedules
     *
     * This function sets the whole array of schedules of the log from a GET request
     */
	void Light::setSchedArr(std::string arraySched){
		this->arraySched = arraySched;
	};

    /**
     * @brief Function sets the size of the schedules
     *
     * This function sets the whole size of schedules of the log from a GET request
     */
	void Light::setSchedsize(int schedSize){
		this->schedSize = schedSize;
	}

    /**
     * @brief Function gets the size of the schedules
     *
     * This function gets the whole size of schedules of the log from a GET request
     */
	int Light::getSchedsize(){
		return schedSize;
	}

    /**
     * @brief Function gets the state of the group
     *
     * This function gets the state of the group of the log from a GET request
     */
	bool Light::getGB(){
		return groupState;
	}

    /**
     * @brief Function sets the state of the group
     *
     * This function sets the state of the group of the log from a GET request
     */
	void Light::setGB(bool groupState){
		this->groupState = groupState;
	}

    /**
     * @brief Function gets the group number
     *
     * This function gets the group number
     */
	int Light::getGNum(){
		return groupNum;
	}

    /**
     * @brief Function gets schedule string
     *
     * This function gets the schedule string
     */
	std::string Light::getSchedString(){
		return schedule1;
	}

    /**
     * @brief Function sets schedule string
     *
     * This function sets the schedule string
     */
	void Light::setSchedString(std::string schedule1){
		this->schedule1 = schedule1;
	}

    /**
     * @brief Function gets schedule brightness
     *
     * This function gets the schedule brightness
     */
	std::string Light::getSchedBri(){
		return scheduleBri;
	}

    /**
     * @brief Function sets schedule brightness
     *
     * This function sets the schedule brightness
     */
	void Light::setSchedBri(std::string scheduleBri){
		this->scheduleBri = scheduleBri;
	}

    /**
     * @brief Function gets the schedule's group's state
     *
     * This function gets the schedule's group state from a get request
     */
	bool Light::getSched(){
		return schedTog;
	}

    /**
     * @brief Function sets the schedule's group's state
     *
     * This function sets the schedule's group state from a get request
     */
	void Light::setSched(bool schedTog){
		this->schedTog=schedTog;
	}

    /**
     * @brief Function gets the current light
     *
     * This function gets the current light
     */
	std::string Light::getStr(){
		return str1;
	}

    /**
     * @brief Function sets the current light
     *
     * This function sets the current light
     */
	void Light::setStr(std::string str1){
		this->str1 = str1;
	}

    /**
     * @brief Function gets the current group
     *
     * This function gets the current group
     */
    std::string Light::getG(){
		return group1;
    }
	
    /**
     * @brief Function sets the current group
     *
     * This function sets the current group
     */
    void Light::setG(std::string str1){
		this->group1 = str1;
	}

    /**
     * @brief Function gets the current group size
     *
     * This function gets the current group size from a GET request
     */
	std::string Light::getBulb(){
		return bulb;
	}

    /**
     * @brief Function sets the current group size
     *
     * This function sets the current group size from a GET request
     */
	void Light::setBulb(std::string bulb){
		this->bulb = bulb;
	}

    /**
     * @brief Function gets the current group toggle
     *
     * This function gets the current group toggle from a GET Request
     */
	bool Light::getGT(){
		return groupToggle;
	}
	
    /**
     * @brief Function sets the current group toggle
     *
     * This function sets the current group toggle from a GET Request
     */
	void Light::setGT(bool groupToggle){
		this->groupToggle = groupToggle;
	}

    /**
     * @brief Function gets the current light state
     *
     * This function gets the current light state from a GET request
     */
	bool Light::getCT(){
		return currentToggle;
	}
	
    /**
     * @brief Function sets the current light state
     *
     * This function sets the current light state from a GET request
     */
	void Light::setCT(bool currentToggle){
		this->currentToggle = currentToggle;
	}

    /**
     * @brief Function gets the light
     *
     * This function gets the light from FUNCTION
     */
	Function Light::getLight(){
		return thisIsLight;
	}
	
    /**
     * @brief Function sets the light
     *
     * This function sets the light from FUNCTION
     */
	void Light::setLight(Function thisIsLight){
		this->thisIsLight = thisIsLight;
	}