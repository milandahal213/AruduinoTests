# Write your code here :-)
import serial
import time

#colors are 16 bit integers
#pure blue is 31
#pure green is 2016
#pure red is 63488
# add the numbers to get the color of your choice
func=["fillScreen","setTextSize","drawString","drawLine","drawPixel","drawRect","fillRect","drawCircle","fillCircle","drawTriangle","fillTriangle","drawRoundRect","fillRoundRect"]


class screen:
    def __init__(self, port):    
        self.s=serial.Serial(port,115200)
        
    def fillScreen(self, x):
        self.ret=self.call_function(2,"graphics",[x])
        return self.ret

    def setTextSize(self, x):
        self.ret=self.call_function(3,"graphics",[x])
        return self.ret

    def drawString(self, string,x,y):
        self.ret=self.call_function(1,"graphics",[string,x,y])
        return self.ret

    def drawLine(self, x1,y1,x2,y2,c):
        self.ret=self.call_function(4,"graphics",[x1,y1,x2,y2,c])
        return self.ret
       
    def drawPixel(self, x,y,c):
        self.ret=self.call_function(5,"graphics",[ x,y,c])
        return self.ret
    
    def drawRect(self, x1,y1,x2,y2,c):
        self.ret=self.call_function(6,"graphics",[x1,y1,x2,y2,c])
        return self.ret
       
    def fillRect(self, x1,y1,x2,y2,c):
        self.ret=self.call_function(7,"graphics",[x1,y1,x2,y2,c])
        return self.ret
       
    def drawCircle(self, x,y,r,c):
        self.ret=self.call_function(8,"graphics",[x,y,r,c])
        return self.ret
    
    def fillCircle(self, x,y,r,c):
        self.ret=self.call_function(9,"graphics",[x,y,r,c])
        return self.ret
    
    def drawTriangle(self, x1,y1,x2,y2,x3,y3,c):
        self.ret=self.call_function(10,"graphics",[x1,y1,x2,y2,x3,y3,c])
        return self.ret
    
    def fillTriangle(self, x1,y1,x2,y2,x3,y3,c):
        self.ret=self.call_function(11,"graphics",[x1,y1,x2,y2,x3,y3,c])
        return self.ret
    
    def drawRoundRect(self, x1,y1,x2,y2,r,c):
        self.ret=self.call_function(12,"graphics",[x1,y1,x2,y2,r,c])
        return self.ret
    
    def fillRoundRect(self, x1,y1,x2,y2,r,c):
        self.ret=self.call_function(13,"graphics",[x1,y1,x2,y2,r,c])
        return self.ret
    
    def connectWifi(self,  ssid, password ):
        self.ret=self.call_function(1,"wifi",[ssid, password])
        return self.ret
    
    def get(self, url, port ):
        self.ret=self.call_function(2,"wifi",[url, port])
        return self.ret
    def show(self):
        return self.s.read(10);

    def call_function(self,  fname, library,arg):
        try:
            self._waitACK= b''
            arguments=""
            last_argument=""
            self._iter=len(arg)
            time.sleep(0.01)
            header="{\"function\":\""+ str(fname) + "\",\"lib\":\"" + str(library) + "\",\"arg\":["
            for _index in range(self._iter-1):
                arguments+="\""+str(arg[_index])+"\","
            last_argument="\""+ str(arg[self._iter-1])+"\""
            to_send=header+arguments+last_argument+"]}"+"done"
            self.s.write(to_send.encode())
            time.sleep(0.01)
            
            _waitACK=self.s.read(self.s.inWaiting())
            while(_waitACK.decode("UTF-8").find("True")<0 and _waitACK.decode("UTF-8").find("False")<0):
                _waitACK+= self.s.read(self.s.inWaiting())
                time.sleep(0.01)
            self.s.flush()
            if(_waitACK.decode("UTF-8").find("True")<0):
                raise Exception("Arduino sent false")
            else:
                return _waitACK[:-6].decode("UTF-8")
        except:
            print("ran into exception:")
            raise Exception("Error on Python")
        


