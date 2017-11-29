g++ *.cpp -o main.out -std=c++11 -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options -lboost_date_time

./main.out --docroot /usr/local/share/Wt --http-address localhost --http-port 8080
