* downlaod and extract the tar.gz folder
* follow the steps:
* cd libserial-0.5.2
* ./configure
* make
* make install
* cd ..
* rm libserial-0.5.2.tar.gz
* rm -d libserial-0.5.2

* To link the dynamic library,add these lines to the CMakeList
* # link the libraries to the executable
* link_directories(/usr/lib)
* target_link_libraries(node_name serial)

* If you have just now installed the library, you may simply need to run,
* sudo ldconfig 
* (ref http://manpages.ubuntu.com/manpages/precise/man8/ldconfig.8.html)


While installing libserial package in fitpc, we got the following errors:
* ERROR: ##unable to create temporary cache file permission denied in ubuntu 14.04 while running a node($ rosrun motion conveyor)
* Soln: Check your permissions for the .ros folder and modify them if you don't have write access or if you don't 
own the folder. The ~/.ros folder is owned by root, change recursively the ownership of that folder
* Type $ sudo chown -R <your_username> ~/.ros in terminal
* ERROR: ##Failed to open port /dev/ttyUSB0 (After solving the above error and entering $ rosrun motion conveyor)
* $ groups 
* If you are not a part of the group it shows a relevant message.
* To add yourself to group:$ gpasswd -a yourUserName dialout
* Restart Xserver by going to root($ sudo su) and typing $ reboot
* Now type $ rosrun motion conveyor 
* Voila! It works...
