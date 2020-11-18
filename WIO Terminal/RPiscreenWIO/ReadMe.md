Download and save the wioscreen folder on your /home/pi folder. Access the library by importing wioscreen on python. Make sure you are running [this](https://github.com/milandahal213/AruduinoTests/tree/master/WIO%20Terminal/SPIKEscreenWIO/on%20WIO) Arduino code on WIO Terminal. 



<code>
  
  from wioscreen import WIO   
  w=WIO.screen("/dev/ttyACM0")
  w.drawString("Milan",10,10)
  w.drawRect(40,50,90,100,32)

</code>

colors are 16 bit integers
pure blue is 31
pure green is 2016
pure red is 63488
add the numbers to get the color of your choice
