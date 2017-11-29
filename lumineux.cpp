/**
* @authors Jason Chung, Nick Friesen, Kenny Galang,  Sama Rahimian
*
* @brief Creates and runs the main apps
*
* Creats and runs the main applications for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
*/

#include "wittyLib.hpp"
#include "login.hpp"
#include "MainFile.h"

/**
* @brief Creates and runs the main apps
*
* Creats and runs the main applications: the page for login and the page for controlling the hue lights systems. It also sets up the hue lights app with a custom URL extension to redirect to.
*
* @param createApplicatoin The first application to be created
* @param createSecondApplication Creates the second application.
* @return - will return an integer on error
*/
int LumineuxRun(int argc, char *argv[], Wt::ApplicationCreator createApplication, Wt::ApplicationCreator createSecondApplication)
{
  try {
    // use argv[0] as the application name to match a suitable entry
    // in the Wt configuration file, and use the default configuration
    // file (which defaults to /etc/wt/wt_config.xml unless the environment
    // variable WT_CONFIG_XML is set)
    Wt::WServer server(argv[0],"");

    // WTHTTP_CONFIGURATION is e.g. "/etc/wt/wthttpd"
    server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);

    // add a single entry point, at the default location (as determined
    // by the server configuration's deploy-path)
    server.addEntryPoint(Wt::Application, createApplication);
    server.addEntryPoint(Wt::Application, createSecondApplication,"/lights");
    if (server.start()) {
      int sig = Wt::WServer::waitForShutdown(argv[0]);

      std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
      server.stop();

      /*
      if (sig == SIGHUP)
        WServer::restart(argc, argv, environ);
      */
      }
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  } catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << "\n";
    return 1;
  }
}

int main(int argc, char **argv){

  Function testMe;

  testMe.testState();
  testMe.bulbTests();


  testMe.testSched();
  testMe.schedTests();

  testMe.testGroup();
  testMe.groupTests();

  return LumineuxRun(argc, argv, &createLogin, &createMainFile);
}
