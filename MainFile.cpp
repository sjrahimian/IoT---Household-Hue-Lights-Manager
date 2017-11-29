/**
 * @authors: Kenneth Galang, Jason Chung, Nick Friesen, Sama Rahimian
 * @brief: Philips Hue Lights application to manipulate lights
 * 
 * Launches/creates the main webpage to interact with hue lights via bridge.
 *  The user is able to change the name of the light, toggle the light, group their lights, toggle the group of lights,
 *  and change the brightness, saturation, and colour of the light.
 */

 #include "MainFile.h"

Light bridge; /**  This is a global variable of what will hold the values of the program, using get and put requests to determine such values. */

std::string ipAddress ="localhost";
std::string port ="8000";

/**
 * @brief: Contains the UI widgets
 * 
 * Contains the UI components of the application. Has a container widget to expand to show lights or groups/schedules
 */
MainFile::MainFile(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{

      root()->addWidget(new Wt::WText("<h1>&#128161;<label style=\"background-color: #fed766;\">Lumineux</label><label style=\"background-color: #b2c6fe;\">: Hue Lights System </label>&#128161;</h1>"));


    Cookie jar;
    std::string value = jar.getCookie("yummy");
      if(value.compare("true") != 0){
        std::cout << "~~~~~~~~~~~~~~~~~  ERROR NO COOKIE BEFORE SUPPER: MUM HID THE COOKIE TO WELL ~~~~~~~~~~~~~~~~~" << std::endl;
        redirect("/errPage");
      }
      else{
        remove( "yummy.txt" );
      }

    menucontainer = new Wt::WContainerWidget();
  lightstack = new Wt::WStackedWidget();
  lightmenu = new Wt::WMenu(lightstack);
  lightcontainer = new Wt::WContainerWidget();
  groupcontainer = new Wt::WContainerWidget();

    setTitle("Hue Lights System");
    bridge.setGT(true);
    bridge.setSched(true);

    //Introduction
    root()->addWidget(new Wt::WText("<h1> Hue Lights System <br/> </h1>"));
    root()->addWidget(new Wt::WBreak());
    logoutButt = new Wt::WPushButton("Logout", root());
    logoutButt->clicked().connect
    (boost::bind(&MainFile::logOut, this));


    root()->addWidget(new Wt::WBreak());
    root()->addWidget(new Wt::WBreak());

    root()->addWidget(new Wt::WText("Enter your bridge IP Address (default is localhost):"));
    root()->addWidget(new Wt::WBreak());
    getIP = new Wt::WLineEdit(root());
    root()->addWidget(new Wt::WBreak());
    goIP = new Wt::WPushButton("Set IP", root());
    goIP->clicked().connect
    (boost::bind(&MainFile::setIP, this));
    root()->addWidget(new Wt::WBreak());
    root()->addWidget(new Wt::WBreak());
    root()->addWidget(new Wt::WText("Enter your bridge host port (default is 8000):"));
    root()->addWidget(new Wt::WBreak());
    getPort = new Wt::WLineEdit(root());
    root()->addWidget(new Wt::WBreak());
    goPort = new Wt::WPushButton("Set Port", root());
    goPort->clicked().connect
    (boost::bind(&MainFile::setPort, this));

    bulbArray= new Wt::WText();
    bulbArray->setText("Hello User, you currently have a list of light bulbs. <br/><br/> This list holds light bulbs: "+ bridge.getBulb() + "<br/>");

    testBox = new Wt::WText();
    testBox->setText("You are currently <b>not</b> dealing with any light. <br/> Please enter the light number in which you want to manipulate.");
    bridge.getLight().testState();

    //user selects a light to play with
    textLight = new Wt::WLineEdit();
    Wt::WPushButton *whatButton = new Wt::WPushButton("Select\nLight");
    whatButton->clicked().connect
    (boost::bind(&MainFile::spitInfo, this));

    root()->addWidget(new Wt::WBreak());

    //toggles on and off the selected light
    root()->addWidget(new Wt::WBreak());
    Wt::WPushButton *button4 = new Wt::WPushButton("Toggle\nOn/Off");
    button4->clicked().connect
    (boost::bind(&MainFile::greet4, this));

    onOff = new Wt::WText();


    //toggles on or off ALL lights
    Wt::WPushButton *buttonGroup = new Wt::WPushButton("Toggle\nAll");
    buttonGroup->clicked().connect
    (boost::bind(&MainFile::groupOnOff, this));


    //updates list of lights
    Wt::WPushButton *getGroup = new Wt::WPushButton("Update\nLights\nList");
    getGroup->clicked().connect
    (boost::bind(&MainFile::lightNameFunction, this));

////////////////////////////////////////////////////////////////////////////////

    //sets/changes name of a light

    nameLight = new Wt::WLineEdit();

    Wt::WPushButton *nameButton = new Wt::WPushButton("Change\nName");
    nameButton->clicked().connect
    (boost::bind(&MainFile::lightNameFunction, this));////////////////////////////



    //slider for changing brightness of a selected light

    Wt::WSlider *scaleSlider = new Wt::WSlider(Wt::Horizontal);
    scaleSlider->setMinimum(0);
    scaleSlider->setMaximum(254);
    scaleSlider->setValue(254);

    scaleSlider->setTickInterval(40);
    scaleSlider->setTickPosition(Wt::WSlider::TicksBothSides);
    scaleSlider->resize(300, 50);

    scaleSlider->sliderMoved().connect(this, &MainFile::brightnessFunction);

    /////////////////////////////////////////////////////////////////////////////////////////////

    //slider for changing color of a selected light
    Wt::WSlider *colSlider = new Wt::WSlider(Wt::Horizontal);
    colSlider->setMinimum(0);
    colSlider->setMaximum(65535);
    colSlider->setValue(32500);
    colSlider->setTickInterval(10000);
    colSlider->setTickPosition(Wt::WSlider::TicksBothSides);
    colSlider->resize(300, 50);

    colSlider->sliderMoved().connect(this, &MainFile::colFunction);


    /////////////////////////////////////////////////////////////////////////////////////////////

    //slider for changing saturation of a selected light

    Wt::WSlider *satSlider = new Wt::WSlider(Wt::Horizontal);
    satSlider->setMinimum(0);
    satSlider->setMaximum(254);
    satSlider->setValue(254);
    satSlider->setTickInterval(40);
    satSlider->setTickPosition(Wt::WSlider::TicksBothSides);
    satSlider->resize(300, 50);

    satSlider->sliderMoved().connect(this, &MainFile::satFunction);

     ///////////////////////////
    //      GROUP STUFF     ///
   ///////////////////////////

   int groupNum = 2;
   std::string msg = "{\"lights\": [";

    //user picks which lights to be in a group
    std::string groupNumber = std::to_string(groupNum);
    Wt::WGroupBox *box = new Wt::WGroupBox("Check off which lights you want in group " + groupNumber);
    w1 = new Wt::WCheckBox("Light 1", box);
    w2 = new Wt::WCheckBox("Light 2", box);
    w3 = new Wt::WCheckBox("Light 3", box);

    //button to create a group from selected lights

    groupName = new Wt::WLineEdit();

    Wt::WPushButton *makeGroup = new Wt::WPushButton("Create\nGroup");
    makeGroup->clicked().connect
    (boost::bind(&MainFile::makeGp, this, msg));
    groupText = new Wt::WText();
    groupText->setText("<br/> <br/>You are currently <b>not</b> dealing with any group. <br/> Please enter the group number in which you want to manipulate.");
    // root()->addWidget(new Wt::WBreak());
    // root()->addWidget(new Wt::WBreak());

    groupLister = new Wt::WText();
    groupLister->setText("Your list of groups: Group 0 (all lights)" + bridge.getGroupArr());

    //allows user to select a light group to manipulate
    textGroup = new Wt::WLineEdit();
    Wt::WPushButton *gButton = new Wt::WPushButton("Select\nGroup");
    gButton->clicked().connect
    (boost::bind(&MainFile::spitGroup, this));

    /////////////////////////////////////////////////////////////////////////////////////////////

    //slider for changing color of a selected group

    Wt::WSlider *colGroupSlider = new Wt::WSlider(Wt::Horizontal, root());
    colGroupSlider->setMinimum(0);
    colGroupSlider->setMaximum(65535);
    colGroupSlider->setValue(32500);
    colGroupSlider->setTickInterval(10000);
    colGroupSlider->setTickPosition(Wt::WSlider::TicksBothSides);
    colGroupSlider->resize(300, 50);
    colGroupSlider->sliderMoved().connect(this, &MainFile::colGroupFunction);

    /////////////////////////////////////////////////////////////////////////////////////////////

    //slider for changing saturation of a selected group

    root()->addWidget(new Wt::WBreak());
    Wt::WSlider *satGroupSlider = new Wt::WSlider(Wt::Horizontal, root());

        satGroupSlider->setMinimum(0);
        satGroupSlider->setMaximum(254);
    satGroupSlider->setValue(254);
    satGroupSlider->setTickInterval(40);
        satGroupSlider->setTickPosition(Wt::WSlider::TicksBothSides);
        satGroupSlider->resize(300, 50);

    satGroupSlider->sliderMoved().connect(this, &MainFile::satGroupFunction);

    /////////////////////////////////////////////////////////////////////////////////////////////

    //slider for changing brightness of a selected light

    Wt::WSlider *briGroupSlider = new Wt::WSlider(Wt::Horizontal, root());
    briGroupSlider->setMinimum(0);
    briGroupSlider->setMaximum(254);
    briGroupSlider->setValue(254);

    briGroupSlider->setTickInterval(40);
    briGroupSlider->setTickPosition(Wt::WSlider::TicksBothSides);
    briGroupSlider->resize(300, 50);
    briGroupSlider->sliderMoved().connect(this, &MainFile::brightnessGroupFunction);

    schedule1= new Wt::WText();
    schedule1->setText("<br/> <h3>Select Certain Schedule for Your Program</h3><br/>");
    
    schedule= new Wt::WText();
    schedule->setText("<br/>These are your schedules<br/>" + bridge.getSchedArr() + "<br/>");
    scheduleDeal= new Wt::WText();
    scheduleDeal->setText("<br/>You currently don't have a scheduled time. <br/>");
    nameMe = new Wt::WLineEdit();
    scheduleGroupH = new Wt::WLineEdit();
    scheduleGroupH->setText("00");
    scheduleGroupM = new Wt::WLineEdit();
    scheduleGroupM->setText("00");
    scheduleGroupS = new Wt::WLineEdit();
    scheduleGroupS->setText("00");
    Wt::WPushButton *setScheduleButton = new Wt::WPushButton("Add schedule (HH/MM/SS)");
    setScheduleButton->clicked().connect
    (boost::bind(&MainFile::addTimer, this));


    Wt::WPushButton *togButton = new Wt::WPushButton("Schedule\nToggle");
    togButton->clicked().connect
    (boost::bind(&MainFile::toggleSched, this));

    brightnessSched = new Wt::WLineEdit();
    Wt::WPushButton *brightSchedButton = new Wt::WPushButton("Add Brightness\nSchedule");
    brightSchedButton->clicked().connect
    (boost::bind(&MainFile::pickSched, this, 3));

    satSchedT = new Wt::WLineEdit();
    Wt::WPushButton *satButton = new Wt::WPushButton("Add Saturation\nSchedule");
    satButton->clicked().connect
    (boost::bind(&MainFile::pickSched, this, 2));


    colSchedT = new Wt::WLineEdit();
    root()->addWidget(new Wt::WBreak());
    Wt::WPushButton *colButton = new Wt::WPushButton("Add Colour\nSchedule");
    colButton->clicked().connect
    (boost::bind(&MainFile::pickSched,  this, 1));
   

    //delete a group

    delG = new Wt::WLineEdit();
    Wt::WPushButton *delbutt = new Wt::WPushButton("Delete \n Group");
    delbutt->clicked().connect
    (boost::bind(&MainFile::deleteGroup, this));

    deleteSched = new Wt::WText();
    deleteSched->setText("Select the schedule number you want to delete.");
    deleteMe = new Wt::WLineEdit();
    Wt::WPushButton *deleteSchedButton= new Wt::WPushButton("Delete\nSchedule");
    deleteSchedButton->clicked().connect
    (boost::bind(&MainFile::deleteSchedFunc,  this));

  menucontainer = new Wt::WContainerWidget();
  lightstack = new Wt::WStackedWidget();
  lightmenu = new Wt::WMenu(lightstack);
  lightcontainer = new Wt::WContainerWidget();
  groupcontainer = new Wt::WContainerWidget();

    // lightcontainer -> addWidget(new Wt::WText("<h3> saaaaaaaaaaaaaaaaaaavsvss <br/> </h3>"));
  lightcontainer -> addWidget(bulbArray);
  lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(testBox);
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(textLight);
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(whatButton);
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(button4);
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(onOff);
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(buttonGroup);
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(getGroup);
      lightcontainer -> addWidget(new Wt::WBreak());

      lightcontainer->addWidget(new Wt::WText("<h4> Set Name of selected light <br/> </h4>"));
          lightcontainer -> addWidget(nameLight);
      lightcontainer -> addWidget(new Wt::WBreak());   
      lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(nameButton);
      lightcontainer -> addWidget(new Wt::WBreak());
      lightcontainer->addWidget(new Wt::WText("<h3> Brightness of Light <br/> </h3>"));
         lightcontainer -> addWidget(new Wt::WBreak());
      lightcontainer -> addWidget(scaleSlider);
      lightcontainer -> addWidget(new Wt::WBreak());
      lightcontainer->addWidget(new Wt::WText("<h3> Color of Light <br/> </h3>"));
         lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(colSlider);
      lightcontainer -> addWidget(new Wt::WBreak());
      lightcontainer->addWidget(new Wt::WText("<h3> Saturation of Light <br/> </h3>"));
         lightcontainer -> addWidget(new Wt::WBreak());
    lightcontainer -> addWidget(satSlider);
    groupcontainer ->addWidget(box);
    groupcontainer->addWidget(new Wt::WText("Name of group"));
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer->addWidget(groupName);
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer ->addWidget(makeGroup);
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer ->addWidget(groupText);
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer->addWidget(groupLister);
    groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer->addWidget(new Wt::WBreak());
  groupcontainer->addWidget(textGroup);
    groupcontainer->addWidget(new Wt::WBreak());
  groupcontainer->addWidget(gButton);
  groupcontainer->addWidget(new Wt::WBreak());
  groupcontainer->addWidget(new Wt::WBreak());
    groupcontainer->addWidget(new Wt::WText("<h3> Colour of Current Group <br/> </h3>"));

groupcontainer->addWidget(new Wt::WBreak());
groupcontainer-> addWidget(colGroupSlider);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("<h3> Saturation of Current Group <br/> </h3>"));
groupcontainer-> addWidget(satGroupSlider);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("<h3> Brightness of Group <br/> </h3>"));
groupcontainer->addWidget(briGroupSlider);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("<br/> <h3>Select Certain Schedule for Your Program</h3><br/>"));
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("<br/>These are your schedules<br/>" + bridge.getSchedArr() + "<br/>"));
groupcontainer->addWidget(new Wt::WBreak()); 
groupcontainer->addWidget(new Wt::WText("<br/>You currently don't have a scheduled time. <br/>"));
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("Name <br/>"));
groupcontainer->addWidget(nameMe);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(scheduleGroupH);
groupcontainer->addWidget(scheduleGroupM);
groupcontainer->addWidget(scheduleGroupS);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(setScheduleButton);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(togButton);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("Change Brightness (Number from 1 to 254)"));
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(brightnessSched);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(brightSchedButton);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("Change Saturation (Number from 1 to 254)"));
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(satSchedT);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(satButton);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("Change Colour (Number from 1 to 65535)"));
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(colSchedT);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(colButton);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WText("<h3> Delete a Group <br/> </h3>"));
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(delG);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(delbutt);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(deleteSched);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(deleteMe);
groupcontainer->addWidget(new Wt::WBreak());
groupcontainer->addWidget(deleteSchedButton);
   menucontainer -> addWidget(lightmenu);
    
    lightmenu -> addItem("Click Here to Show Lights", lightcontainer);
    lightmenu -> addItem("Click Here to Show Groups and Schedules", groupcontainer);


   menucontainer->addWidget(lightstack);

   root()->addWidget(menucontainer);

    root()->addWidget(new Wt::WBreak());

    root()->addWidget(new Wt::WText("<h3> Additional Features <br/> </h3>"));
    
    root()->addWidget(new Wt::WBreak());
    Wt::WPushButton *ravebutt = new Wt::WPushButton("Rave \n Time", root());
    ravebutt->clicked().connect
    (boost::bind(&MainFile::rave, this));


    //////////////////////////////////////////////////////////////////

    root()->addWidget(new Wt::WBreak());
   root()->addWidget(new Wt::WBreak());

   Wt::WPushButton *startGameButton = new Wt::WPushButton("Christmas \n Colors", root());
   startGameButton->clicked().connect
    (boost::bind(&MainFile::christmas, this));
   root()->addWidget(new Wt::WBreak());
   root()->addWidget(new Wt::WBreak());
   Wt::WPushButton *lightOne = new Wt::WPushButton("Glow Loop\nAll Colors", root());
   lightOne->clicked().connect
    (boost::bind(&MainFile::glow, this));
   root()->addWidget(new Wt::WBreak());
   root()->addWidget(new Wt::WBreak());

  }
  
/**
 * @brief: Deletes schedules using DELETE request
 * 
 * Does a DELETE request to delete a selected schedule.
 */
void MainFile::deleteSchedFunc(){

  Wt::WString delW = deleteMe->text();
  std::wstring wstringName5 = delW.value();
  std::string deleteNeeded = std::string(wstringName5.begin(), wstringName5.end());

  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");

  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::string requestSched = "http://" + ipAddress+ ":" + port + "/api/newdeveloper/schedules/" + deleteNeeded;

  client->deleteRequest(requestSched, *message);
  ioservice->stop();

  bridge.getLight().testSched();
  bridge.getLight().schedTests();
  schedule->setText("<br/>These are your schedules<br/>" + bridge.getSchedArr() + "<br/>");

}

/**
 * @brief: does a GET request to get ALL information from a user
 * 
 * Does a GET request to retrieve all info for the user to ouput to file
 */
void Function::testLogout(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::testLogoutT, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port +"/api/newdeveloper");
  ioservice->stop();

}

/**
 * @brief: outputs the get request for ALL info of a user
 * 
 * outputs the get request for ALL info of a user to the user profile text file
 * 
 * @param err description the error code returned when error arises
 * @param response description the response from the request
 * 
 */
void Function::testLogoutT(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);
  bridge.setLogString(response.body());

  userProfile.setLightData(bridge.getLogString());
  userProfile.exportUser();


}

/**
 * @brief: sets IP address
 * 
 * sets IP address given by the user for the URL
 * 
 */
void MainFile::setIP()
{
    Wt::WString textIP = getIP->text();
    std::wstring wstringIP = textIP.value();
    std::string tempIP = std::string(wstringIP.begin(), wstringIP.end());
    ipAddress = tempIP;
}

/**
 * @brief: sets port nubmer
 * 
 * sets port number given by the user for the URL
 * 
 */
void MainFile::setPort()
{
    Wt::WString textPort = getPort->text();
    std::wstring wstringPort = textPort.value();
    std::string tempPort = std::string(wstringPort.begin(), wstringPort.end());
    port = tempPort;
}

/**
 * @brief: rave function
 * 
 * random selects a color for all lights and flashes the lights
 * 
 */
void MainFile::rave(){

  for(int i = 0; i < 10; i++)
  {
        int rand1;
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  /* initialize random seed: */
  srand (time(NULL));

  rand1 = rand() % 65535;

  groupOnOff();

  colAllGroupFunction(rand1);
  } 
}

/**
 * @brief: sets color for group 0
 * 
 * sets the color of all lights to be the same
 * 
 * @param valueMe description the color to be made in integer
 */
 void MainFile::colAllGroupFunction(int valueMe){

    std::string me2 = std::to_string(valueMe);
    std::string value2 = "{\"hue\": ";
    value2 = value2 + me2;
    value2 = value2 + "}";

    Wt::WIOService *ioservice = new Wt::WIOService();
    ioservice->start();
    Wt::Http::Message *message = new Wt::Http::Message();
    message->addHeader("Content-type", "application/json");
    message->addBodyText(value2);
    Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
    std::cout<<message->body()<<std::endl;

    client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/groups/0/action", *message);
    ioservice->stop();
  }

  /**
 * @brief: christmas lights
 * 
 * flashes red and green christmas lights for all lights alternating
 * 
 */
void MainFile::christmas()
{
  bool next = true;
   for(int i = 0; i < 10; i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if(next)
    {
      next = false;
    bridge.setStr("1");
    colFunction(2260);

    bridge.setStr("2");
    colFunction(24632);

    bridge.setStr("3");
    colFunction(2260);
  }
  
  else
  {
    next = true;
    bridge.setStr("1");
    colFunction(24632);

    bridge.setStr("2");
    colFunction(2260);

    bridge.setStr("3");
    colFunction(24632);
  }
    
  }
}

/**
 * @brief: glow transitions 
 * 
 * glow transitions for all colors of all lights
 * 
 */
void MainFile::glow(){
  bool next = true;
  std::string tempStringGame = bridge.getG();
  bridge.setG("0");
   for(int i = 0; i < 3; i++)
  {
    if(next)
    {
      next = false;
      for(int w = 0; w<65000; w = w + 1000){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
      colGroupFunction(w);

      }   
  }
  
  else
  {
    next = true;
    for(int w = 65000; w>100; w = w - 1000){
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      colGroupFunction(w);

      }

  }
  }
  bridge.setG(tempStringGame);
}

/**
 * @brief: deletes group
 * 
 * DELETE request for a given group from user
 * 
 */
void MainFile::deleteGroup(){

    Wt::WString textD1 = delG->text();
    std::wstring wstringD1 = textD1.value();
    std::string temp1D = std::string(wstringD1.begin(), wstringD1.end());
    std::string stringMe = "http://" + ipAddress+ ":" + port + "/api/newdeveloper/groups/2";

    Wt::WIOService *ioservice = new Wt::WIOService();
    ioservice->start();
    Wt::Http::Message *message = new Wt::Http::Message();
    message->addHeader("Content-type", "application/json");
    Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
    std::cout<<message->body()<<std::endl;

    client->deleteRequest(stringMe, *message);
   

    bridge.getLight().testGroup();
    bridge.getLight().groupTests();
    groupLister->setText("Your list of groups:  Group 0 (all groups) , " + bridge.getGroupArr());
    ioservice->stop();
  }

/**
 * @brief: creates a custom schedule
 * 
 * creates a given schedule using HH/MM/SS format for everything you can do with a regular group
 * 
 * @param one description Picks which button is pressed for the schedule
 */
void MainFile::pickSched(int one){
  Wt::WString nameW = nameMe->text();
  std::wstring wstringName4 = nameW.value();
  std::string nameNeeded = std::string(wstringName4.begin(), wstringName4.end());

  Wt::WString colW = colSchedT->text();
  std::wstring wstringName3 = colW.value();
  std::string colNeeded = std::string(wstringName3.begin(), wstringName3.end());

  Wt::WString satW = satSchedT->text();
  std::wstring wstringName2 = satW.value();
  std::string satNeeded = std::string(wstringName2.begin(), wstringName2.end());

  Wt::WString briW = brightnessSched->text();
  std::wstring wstringName1 = briW.value();
  std::string briNeeded = std::string(wstringName1.begin(), wstringName1.end());
  std::string changeMe = "";
  std::string numberNeeded = "";

  if(one == 1){
    changeMe = "hue";
    numberNeeded = colNeeded;
  }
  else if(one == 2){
    
    changeMe = "sat";
    numberNeeded = satNeeded;
  }
  else if(one == 3){
    changeMe = "bri";
    numberNeeded = briNeeded;
  }

  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  std::string messageMe = "{\"name\": \"" + nameNeeded + "\",\"description\": \"My wake up alarm\",\"command\": { \"address\": \"/api/newdeveloper/debugger/groups/" + bridge.getG() + "/action\",\"method\": \"PUT\",\"body\": {\"" + changeMe + "\":" + numberNeeded + "}},\"time\": \"" + bridge.getSchedString() + "\"}";
  message->addBodyText(messageMe);
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;
  client->post("http://" + ipAddress+ ":" + port +"/api/newdeveloper/debugger/schedules", *message);
  ioservice->stop();

  bridge.getLight().testSched();
  bridge.getLight().schedTests();
  schedule->setText("<br/>These are your schedules<br/>" + bridge.getSchedArr() + "<br/>");
}


/**
 * @brief: gets current time
 * 
 * gets current time from local time
 * 
 */

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}


/**
 * @brief: adds timer
 * 
 * adds a timer using the format HH/MM/SS
 * 
 */
void MainFile::addTimer(){

  std::string newTime = currentDateTime();
  newTime[10] = 'T';
  std::cout<<newTime<<std::endl;

  Wt::WString hour= scheduleGroupH->text();
  std::wstring whour= hour.value();
  std::string hourH = std::string(whour.begin(), whour.end());
  int hourInt = std::stoi(hourH);


  Wt::WString min= scheduleGroupM->text();
  std::wstring wmin= min.value();
  std::string minH = std::string(wmin.begin(), wmin.end());
  int minInt = std::stoi(minH);


  Wt::WString sec= scheduleGroupS->text();
  std::wstring wsec= sec.value();
  std::string secH = std::string(wsec.begin(), wsec.end());
  int secInt = std::stoi(secH);

  std::string tempHour = newTime.substr(11,2);
  int inth = stoi(tempHour) + hourInt;

std::string tempMin = newTime.substr(14,2);
  int intm = stoi(tempMin) + minInt;

  std::string tempSec = newTime.substr(17,2);
  int ints = stoi(tempSec) + secInt;


  if(inth > 24)
  {
    inth -= 24;
  }


if(intm > 60)
  {
    inth += 1;
    intm %= 60;
  }

if(ints > 60)
  {
    intm +=1;
    ints %= 60;
  }

  std::string strHour = std::to_string(inth);

  newTime[11] = strHour[0];
  newTime[12] = strHour[1]; 
  
  std::string strMin = std::to_string(intm);

  newTime[14] = strMin[0];
  newTime[15] = strMin[1];

  std::string strSec = std::to_string(ints);

  newTime[17] = strSec[0];
  newTime[18] = strSec[1];

  std::cout<<newTime<<std::endl;

  bridge.setSchedString(newTime);
  scheduleDeal->setText("<br/>Your schedule is currently: " + bridge.getSchedString() + "<br/><br/>");



}

/**
 * @brief: toggle for schedules 
 * 
 * Toggle function for a given schedule
 * 
 */
void MainFile::toggleSched(){
  bridge.getLight().getGroupState();

  if(bridge.getGB() == true){       bridge.getLight().turnSchedOff();    bridge.setSched(false);  }
  else if(bridge.getGB() == false){ bridge.getLight().turnSchedOn();     bridge.setSched(true);   }


}

/**
 * @brief: gets the state of group 
 * 
 * gets the state of the given current group
 * 
 */
void Function::getGroupState(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::handleHttpResponseG, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port +"/api/newdeveloper/groups/1/state");
  ioservice->stop();
}

/**
     *  This parses the JSON file and determines if it is on or off, and updates the bridge's current light's state.
     *
     * @param err: the error message returned when an error arises
     * @param response: the HTTP response to be parsed
     *
     */
void Function::handleHttpResponseG(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object object;
  Wt::Json::parse(response.body(),object);
  Wt::Json::Object lightsObject = object.get("groups");

  std::cout<< bridge.getG() + "\nI a JSON\n\n\n"<<std::endl;
  Wt::Json::Object bulbObject = lightsObject.get(bridge.getG());
  Wt::Json::Object stateObject = bulbObject.get("action");
  bool toggleMe = stateObject.get("on");
  if(toggleMe == true){

    bridge.setGB(true);
  }else{
    bridge.setGB(false);
  }

}

/**
 * @brief: turns off schedule
 * 
 * does a POST request to turn off schedule
 * 
 */
void Function::turnSchedOff(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  std::string messageMe = "{\"name\": \"test\",\"description\": \"My wake up alarm\",\"command\": { \"address\": \"/api/newdeveloper/debugger/groups/" + bridge.getG() + "/action\",\"method\": \"PUT\",\"body\": {\"on\": false}},\"time\": \"" + bridge.getSchedString() + "\"}";

  message->addBodyText(messageMe);

  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->post("http://" + ipAddress+ ":" + port + "/api/newdeveloper/debugger/schedules", *message);
  ioservice->stop();
}

/**
 * @brief: turns on schedule
 * 
 * does a POST request to turn on schedule
 * 
 */
void Function::turnSchedOn(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");

  std::string messageMe = "{\"name\": \"test\",\"description\": \"My wake up alarm\",\"command\": { \"address\": \"/api/newdeveloper/debugger/groups/" + bridge.getG() + "/action\",\"method\": \"PUT\",\"body\": {\"on\": true}},\"time\": \"" + bridge.getSchedString() + "\"}";
  message->addBodyText(messageMe);

  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->post("http://" + ipAddress+ ":" + port +"/api/newdeveloper/debugger/schedules", *message);
  ioservice->stop();
}

/**
     * @brief: sets brightness of group
     * 
     * Whenever the brightness slider is moved, a signal is sent to brightness function which then takes the value parameter of the
     *  position of the slider and converts it into a put request. It changes the current group's brightness each request.
     *
     *  @param valueMe: the value of brightness in integer
     *
     */
void MainFile::brightnessGroupFunction(int valueMe){
  std::string me = std::to_string(valueMe);
  std::string value = "{\"bri\": ";
  value = value + me;
  value = value + "}";
  std::cout<<"\n\n\nwtf??" + value << std::endl;
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText(value);
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port + "/api/newdeveloper/groups/" + bridge.getG() + "/action", *message);
  ioservice->stop();

}

/**
     * @brief: outputs what is current group
     * 
     * ouputs info for the current group you are dealing with
     *
     */
void MainFile::spitGroup(){
    Wt::WString textG = textGroup->text();
    std::wstring wstringG = textG.value();
    std::string tempG = std::string(wstringG.begin(), wstringG.end());
    bridge.setG(tempG);
    std::string stringThis =  "You are currently dealing with group: <b>" + bridge.getG() + "</b>";
    groupText->setText(stringThis);

  }

/**
     *  @brief: sets the color of the group
     * 
     * Whenever the colour slider is changed, it sends a signal with an int of the position of the slider.
     *  This sends a put request each time (according to the set ticks) to colGroupFunction and does a put request for the current value to manipulate
     *  the current colour for the current group selected.
     *
     *  @param valueMe: the value of color in integer
     *
     */

  void MainFile::colGroupFunction(int valueMe){

    std::string me2 = std::to_string(valueMe);
    std::string value2 = "{\"hue\": ";
    value2 = value2 + me2;
    value2 = value2 + "}";

    Wt::WIOService *ioservice = new Wt::WIOService();
    ioservice->start();
    Wt::Http::Message *message = new Wt::Http::Message();
    message->addHeader("Content-type", "application/json");
    message->addBodyText(value2);
    Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
    std::cout<<message->body()<<std::endl;

    client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/groups/" + bridge.getG()+ "/action", *message);
    ioservice->stop();
  }

    /**
     * @brief: sets the saturation of the current group 
     * 
     * Whenever the saturation slider is moved, a signal is sent to satGroupFunction which then takes the value parameter of the
     *  position of the slider and converts it into a put request. It changes the current groups's saturation each request.
     *
     *  @param valueMe: the value of saturation in integer
     *
     */
    void MainFile::satGroupFunction(int valueMe){

        std::string me2 = std::to_string(valueMe);
        std::string value2 = "{\"sat\": ";
        value2 = value2 + me2;
        value2 = value2 + "}";

        Wt::WIOService *ioservice = new Wt::WIOService();
        ioservice->start();
        Wt::Http::Message *message = new Wt::Http::Message();
        message->addHeader("Content-type", "application/json");
        message->addBodyText(value2);
        Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
        std::cout<<message->body()<<std::endl;

        client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/groups/" + bridge.getG()+ "/action", *message);
        ioservice->stop();
        }

    /**
     * @brief: makes a group given the checkboxes checked off for lights 
     * 
     * Creates groups consisting of the selected groups from the checkboxes.
     * Then does a POST request to create the group. This function also updates the list of groups made
     *
     * @param msg - string that holds the JSON body for each light being added to a group
     */
void MainFile::makeGp(std::string msg)
{   
    Wt::WString nameWg = groupName->text();
    std::wstring wstringName4g = nameWg.value();
    std::string groupNeeded = std::string(wstringName4g.begin(), wstringName4g.end());

    bridge.groupNum += 1;

    if(w1->isChecked())
    {
        msg = msg + ",\"1\"";
    }
    if(w2->isChecked())
    {
        msg = msg + ",\"2\"";
    }
    if(w3->isChecked())
    {
        msg = msg + ",\"3\"";
    }
    msg = msg + "], \"name\":" + "\"" + groupNeeded + "\"}";


    Wt::WIOService *ioservice = new Wt::WIOService();
    ioservice->start();
    Wt::Http::Message *message = new Wt::Http::Message();
    message->addHeader("Content-type", "application/json");
    message->addBodyText(msg);
    Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
    std::cout<<message->body()<<std::endl;

    client->post("http://" + ipAddress + ":" + port +"/api/newdeveloper/groups/", *message);

    std::string stringSecond =  "\n Group " + std::to_string(bridge.getGNum());
    totalString += stringSecond;

    bridge.getLight().testGroup();
    bridge.getLight().groupTests();
    groupLister->setText("Your list of groups:  Group 0 (all groups) , " + bridge.getGroupArr());

    ioservice->stop();

  }

/**
     * @brief: names the light 
     * 
     * Whenever a name is changed, it takes the string inside the text box and converts it to a string.
     *  It then checks what light is being dealt with with bridge.getStr() and does a put request to change the name of the bulb.
     *  Finally, it updates the array of bulbs text for the user to see.
     */
void MainFile::lightNameFunction(){
  bridge.getLight().testState();
   /*! Change the WString that is entered, and convert it to a string. */
  Wt::WString lightW = nameLight->text();
  std::wstring wstringName = lightW.value();
  std::string nameNeeded = std::string(wstringName.begin(), wstringName.end());

  std::string ww = "{\"name\": \"";
  ww = ww + nameNeeded;
  ww = ww + "\"}";

/*! Create a server which the client points to, and is able to communicate with. */
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  /*! Create a message with header (JSON type) and a body. */
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText(ww);


  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;
 /*! Do a put request with the message. */
  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/" + bridge.getStr() + "/name", *message);
  ioservice->stop();
  /*! Make the array of the lists of bulbs, and then set the text to it. */
  bridge.getLight().bulbTests();

  bulbArray->setText("Hello User, you currently have a list of light bulbs. <br/><br/> This list holds light bulbs: "+ bridge.getBulb() + "<br/>");
}


/**
     * @brief: sets the color of current light 
     * 
     * Whenever the colour slider is changed, it sends a signal with an int of the position of the slider.
     *  This sends a put request each time (according to the set ticks) to colFunction and does a put request for the current value to manipulate
     *  the current colour for the current bulb selected.
     *
     * @param valueMe: the value of color in integer
     *
     */
void MainFile::colFunction(int valueMe){

  std::string me2 = std::to_string(valueMe);
  std::string value2 = "{\"hue\": ";
  value2 = value2 + me2;
  value2 = value2 + "}";

  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText(value2);
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port + "/api/newdeveloper/lights/" + bridge.getStr()+ "/state", *message);
  ioservice->stop();
}

/**
     * @brief: checks and toggles group states 
     * 
     * From the group toggle button, this groupOnOff is called - it determines whether the bridge's all lights are on or off.
     *  It sets all lights off if the light is on, and updates its state, and sets all lights on if the light is off, and updates its state.
     */
void MainFile::groupOnOff(){


     if(bridge.getGT() == true){       bridge.getLight().turnGroupOff();    bridge.setGT(false);  }
     else if(bridge.getGT() == false){ bridge.getLight().turnGroupOn();     bridge.setGT(true);   }
}

/**
     * @brief: turns current group on 
     * 
     * From the groupOnOff function, this function sends a put request to the group 0 which consists of all lights, and turns it on.
     *
     */
void Function::turnGroupOn(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText("{\"on\": true }");
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/groups/0/action", *message);
  ioservice->stop();
}

/**
     * @brief: turns current group off 
     * 
     * From the groupOnOff function, this function sends a put request to the group 0 which consists of all lights, and turns it off.
     *
     */
void Function::turnGroupOff(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText("{\"on\": false }");
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/groups/0/action", *message);
  ioservice->stop();
}

/**
     * @brief: tests the light 
     * 
     * If the user adds a new light, and sends a request to check the amount of bulbs there are and the name of each light.
     *  It then updates the set text of the array of bulbs.
     */
void MainFile::callThis(){
  bridge.getLight().testState();
}


/**
     * @brief: returns which light you are dealing with 
     * 
     * This function sets the bridge of what it light it is pointing to.
     *  It then tells the user what light they are 'dealing' with so they can manipulate it with such buttons and sliders.
     */
void MainFile::spitInfo(){
  Wt::WString textInfo = textLight->text();
  std::wstring wstringLight = textInfo.value();
  std::string tempStr = std::string(wstringLight.begin(), wstringLight.end());
  bridge.setStr(tempStr);
  std::string stringThis =  "You are currently dealing with light: <b>" + bridge.getStr() + "</b>";
  testBox->setText(stringThis);
}


    /**
     * @brief: gets info of state for light 
     * 
     * Does a get request to get all the names of lights by gettings a response, and then calling bulbObjects with parses is to loop through each light.
     */
void Function::bulbTests(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::bulbObjects, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/1/state");
  ioservice->stop();
}

/**
     * @brief: parses the JSON 
     * 
     * Parses the response of the JSON, and sets the bridge's bulb string to contain an array of each name of each light.
     *  Depends on the bulb size that was set in the testState and testResponse function.
     *
     * @param err: the error message return when error arises
     * @param reponse: the HTTP response to be parsed
     *
     */
void Function::bulbObjects(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);
  Wt::Json::Object lightOb = result.get("lights");

  std::string tempBulb = "<br/>";
  for(int i = 1; i < bridge.getBulbsize()+1;i++){
    std::string temp = std::to_string(i);
    Wt::Json::Object currentLight = lightOb.get(temp);

    std::string tempString = currentLight.get("name");
    tempBulb= tempBulb + temp + ": " + tempString + "<br/>";
    }

    bridge.setBulb(tempBulb);
}


/**
     * @brief: gets all schedules
     * 
     * does GET request for all scheduldes for user
     *
     *
     */
void Function::schedTests(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::schedObjects, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port +"/api/newdeveloper/schedules");
  ioservice->stop();
}


/**
     * @brief: parses JSON for schedules
     * 
     * parses JSON information for schedules
     *
     * @param err: the error message return when error arises
     * @param reponse: the HTTP response to be parsed
     *
     */
void Function::schedObjects(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);

    bridge.setSchedArr(response.body());

}
/**
     * @brief: gets info for all lights
     * 
     * does a get request to test state of light
     *
     */
void Function::testState(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::testResponse, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/");
  ioservice->stop();

}

/**
     *  @brief: parses JSON for lights
     * 
     * This function then parses the JSON object and sets the size of the bulb.
     *
     * @param err: the error message returned when an erro arises
     * @param response: the HTTP response to be parsed
     */
void Function::testResponse(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);
  bridge.setBulbsize(result.size());
}

/**
     * @brief: tests schedules
     * 
     * get request to test schedules
     *
     */
void Function::testSched(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::testSchedT, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port +"/api/newdeveloper/schedules/");
  ioservice->stop();

}

/**
     * @brief: tests schedules 
     * 
     * This function then parses the JSON object and sets the size of the bulb.
     *
     * @param err: the error message returned when an erro arises
     * @param response: the HTTP response to be parsed
     */
void Function::testSchedT(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);
  bridge.setSchedsize(result.size());

  std::string me123 = std::to_string(bridge.getSchedsize());

}

/**
     *  @brief: sets brightness of current light
     * 
     * Whenever the brightness slider is moved, a signal is sent to brightness function which then takes the value parameter of the
     *  position of the slider and converts it into a put request. It changes the current bulb's brightness each request.
     *
     * @param valueMe: the value of brightness in integer
     *
     */
void MainFile::brightnessFunction(int valueMe){
  std::string me = std::to_string(valueMe);
  std::string value = "{\"bri\": ";
  value = value + me;
  value = value + "}";
  std::cout<<"\n\n\nwtf??" + value << std::endl;
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText(value);
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/" + bridge.getStr() + "/state", *message);
  ioservice->stop();

}

/**
     * @brief: sets saturation for current light 
     * 
     * Whenever the saturation slider is moved, a signal is sent to satFunction which then takes the value parameter of the
     *  position of the slider and converts it into a put request. It changes the current bulb's saturation each request.
     *
     * @param valueMe: the value of saturation in integer
     *
     */
void MainFile::satFunction(int valueMe){
  std::string me1 = std::to_string(valueMe);
  std::string value1 = "{\"sat\": ";
  value1 = value1 + me1;
  value1 = value1 + "}";

  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText(value1);
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/" + bridge.getStr()+ "/state", *message);
  ioservice->stop();
}

/**
     * @brief: checks toggle for current light 
     * 
     * Whenever the toggle button is clicked, it first checks the bulb's current state (whether it's on or off).
     *  It then turns the light off if it is on, or on if it is off, and updates the user to let them know it was successfully turned on/off.
     */
void MainFile::greet4(){
  bridge.getLight().getState();

    if(bridge.getCT()== true){       bridge.getLight().turnMeOff1();    bridge.setCT(false);  onOff->setText("You have successfully turned the light: " + bridge.getStr() + " <b>OFF.</b>");}
    else if(bridge.getCT()
     == false){ bridge.getLight().turnMeOn1();     bridge.setCT(true);  onOff->setText("You have successfully turned the light: " + bridge.getStr() + " <b>ON.</b>"); }
}

/**
     * @brief: gets state of current light 
     * 
     * Does a get request to get the whole JSON file.
     */
void Function::getState(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::handleHttpResponse, this, _1, _2));
  client->get("http://" + ipAddress+ ":" + port + "/api/newdeveloper/lights/1/state");
  ioservice->stop();
}

/**
     * @brief: parses JSON info 
     * 
     * This parses the JSON file and determines if it is on or off, and updates the bridge's current light's state.
     *
     * @param err: the error message returned when an error arises
     * @param response: the HTTP response to be parsed
     *
     */
void Function::handleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object object;
  Wt::Json::parse(response.body(),object);
  Wt::Json::Object lightsObject = object.get("lights");
  Wt::Json::Object bulbObject = lightsObject.get(bridge.getStr());
  Wt::Json::Object stateObject = bulbObject.get("state");\
  bool toggleMe = stateObject.get("on");
  if(toggleMe == true){

    bridge.setCT(true);
  }else{
    bridge.setCT(false);
  }

}

/**
     * @brief: turns current light on 
     * 
     * Does a put request to turn the light on, depending on what bulb is currently selected.
     */
void Function::turnMeOn1(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText("{\"on\": true }");
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;

  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/" + bridge.getStr() + "/state", *message);
}

/**
     * @brief: turns current light off
     * 
     * Does a put request to turn the light off, depending on what bulb is currently selected.
     */

void Function::turnMeOff1(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Message *message = new Wt::Http::Message();
  message->addHeader("Content-type", "application/json");
  message->addBodyText("{\"on\": false }");
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  std::cout<<message->body()<<std::endl;
  client->put("http://" + ipAddress+ ":" + port +"/api/newdeveloper/lights/" + bridge.getStr() + "/state", *message);
  ioservice->stop();
}

/**
     * @brief: tests group
     * 
     * gets all groups
     */
void Function::testGroup(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::testSchedT, this, _1, _2));
  client->get("http://" + ipAddress + ":" + port +"/api/newdeveloper/groups/");
  ioservice->stop();

}

/**
     * @brief: tests state for group
     * 
     * Parses info for group states
     */
void Function::testGroupT(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);
  bridge.setGroupsize(result.size());

  std::string me123 = std::to_string(bridge.getSchedsize());
}


/**
     * @brief: tests group
     * 
     * does a get request to get all groups
     */
void Function::groupTests(){
  Wt::WIOService *ioservice = new Wt::WIOService();
  ioservice->start();
  Wt::Http::Client *client = new Wt::Http::Client(*ioservice);
  client->done().connect(boost::bind(&Function::groupObjects, this, _1, _2));
  client->get("http://" + ipAddress + ":" + port +"/api/newdeveloper/groups");
  ioservice->stop();
}


/**
     * @brief: parses response
     * 
     * parses rseponse for group lights
     */
void Function::groupObjects(boost::system::error_code err, const Wt::Http::Message& response){

  Wt::Json::Object result;

  Wt::Json::parse(response.body(), result);

    bridge.setGroupArr(response.body());

}

/**
     * @brief: gets all info when logging off
     * 
     * gets all info when logging off for a given user
     */
void MainFile::logOut(){
  bridge.getLight().testLogout();
  sleep(2);
  redirect("");
}

/**
     *  @brief: starts lights class
     * 
     * Starts the application.
     * @param env: the Wt environment used when running the application
     */
Wt::WApplication *createMainFile(const Wt::WEnvironment& env){
    Function testMe;
    
    testMe.testState();
    testMe.bulbTests();
    
    
    testMe.testSched();
    testMe.schedTests();
    
    testMe.testGroup();
    testMe.groupTests();

    Wt::WApplication *app = new MainFile(env);
    app->setTitle("Lumineux: Hue Lights System");
    app->useStyleSheet("css/hueLights.css");

    return app;
}
