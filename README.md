<h1>Internet Of Things – Hue Lights Project – Agile Project Management</h1>

### C++, Wt library, Philips Hue API, Jira, Bitbucket

Worked in <b>Agile</b> environment with daily meetings and code reviews before every commit.

<br>
Includes a login authentication screen for users.

Used Web Toolkit API to create a web application that can manipulate lights within a household.
User can toggle lights and groups, change brightness, saturation, colour, create groups and schedules, and have saved sessions.
Additional features include rave lights, christmas lights, and glowing lights.

Sends POST, PUT, and GET requests to the server in order to manipulate lights.

Includes DOXYGEN type comments, and UML diagrams.

<br>
<h3>Members Include: Kenneth Galang, Jason Chung, Sama Rahimian, Nick Friesen</h3>
<br>


To compile & run:
```
g++ *.cpp -o main.out -std=c++11 -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time

./main.out --docroot /usr/local/share/Wt --http-address localhost --http-port 8080
```

To add CSS:
```
sudo cp css/login.css css/hueLights.css /usr/loal/share/Wt/css
```
