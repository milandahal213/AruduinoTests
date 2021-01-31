import hub
import utime
import backpack

#ESTABLISHING CONNECTION
#connecting the WIO to port C 
t=backpack.screen(hub.port.C)


###########################
#colors are 16 bit integers
#pure blue is 31
#pure green is 2016
#pure red is 63488
# add the numbers to get the color of your choice

#so if you need yellow you should add red and green i.e. 65504
###########################


#filling the screen with color 65504 
t.fillScreen(65504)


#setTextSize to 3
t.setTextSize(3)
t.drawString("Size 3",200,50)

#setTextSize to 2
t.setTextSize(2)
t.drawString("Size 2",200,100)


#drawLine from (20,20) to (180,20) of color 31 i.e blue
t.drawLine(20,20,180,20,31)


#drawPixel at 40,40 of color 65535 i.e. white
t.drawPixel(100,10,65535)

#drawRect from (20,30) with width 50 and height 50 of color 5555 
t.drawRect(20,30,50,50,5555)


#draw a filled rectangle from (130,30) with width 50 and height 50 with color 5555
t.fillRect(130,30,50,50,5555)

#drawCircle with center at 100,40 with radius 20 of color 9000
t.drawCircle(100,40,20,9000)

#draw a filled circle at center 100,80 with radius 20 with color 9000
t.fillCircle(100,80,20,9000)

#drawTriangle with vertices at (30,40),(60,70), (30,70) of color 9000
t.drawTriangle(30,40,60,70,30,70,9000)

#fill a triangle at (170,40),(140,70),(170,70) with color 9000
t.fillTriangle(170,40,140,70,170,70,9000)

#drawRoundRect with vertices at (20,100) with width 50 and height 50 and with a corner radius of 5 of color 63488
t.drawRoundRect(20,100,50,50,5,63488)

#fillRoundRect with vertices at (130,100) with width 50 and height 50 with corner radius of 5 with color 9000
t.fillRoundRect(130,100,50,50,5,9000)

#CONNECTING TO WIFI

#connect to wifi with ssid ="ssid" and password="password"
t.connectWifi("ssid","password")

#WORKING WITH AIRTABLE
#to use airtable api you should start by connecting to wifi, setting up airtable credentials and then call get or post 
#set airtable with appkey="appkey" and baseid="baseid"
t.setAirtable("appkey","baseid")

#post to airtable with table name="Table" and Field name="Variables" with value="ttt"
b=t.postAirtable("Table","Variables","ttt")

#get info of Airtable with Table name= "Table"
a=t.getAirtable("Table")

print(a)

