
cmake .
cmake -Dgtest_force_shared_crt=TRUE
cmake --build .
read -n 1 -p "Press any key to continue"