downlaod and extract the tar.gz folder
follow the steps:
cd libserial-0.5.2
./configure
make
make install
cd ..
rm libserial-0.5.2.tar.gz
rm -d libserial-0.5.2

To link the dynamic library,add these lines to the CMakeList
# link the libraries to the executable
link_directories(/usr/lib)
target_link_libraries(node_name serial)

If you have just now installed the library, you may simply need to run,
sudo ldconfig 
(ref http://manpages.ubuntu.com/manpages/precise/man8/ldconfig.8.html)
