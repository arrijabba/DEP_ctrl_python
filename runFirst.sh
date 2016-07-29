
#!/bin/bash

clear			

echo "The script starts now."
unzip pigpio.zip
cd PIGPIO
make -j4
sudo make install