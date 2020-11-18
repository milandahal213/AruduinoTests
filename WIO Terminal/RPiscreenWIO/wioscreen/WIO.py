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
        self.ret=self.call_function(2,[x])
        return self.ret

    def setTextSize(self, x):
        self.ret=self.call_function(3,[x])
        return self.ret

    def drawString(self, string,x,y):
        self.ret=self.call_function(1,[string,x,y])
        return self.ret

    def drawLine(self, x1,y1,x2,y2,c):
        self.ret=self.call_function(4,[x1,y1,x2,y2,c])
        return self.ret
       
    def drawPixel(self, x,y,c):
        self.ret=self.call_function(5,[ x,y,c])
        return self.ret
    
    def drawRect(self, x1,y1,x2,y2,c):
        self.ret=self.call_function(6,[x1,y1,x2,y2,c])
        return self.ret
       
    def fillRect(self, x1,y1,x2,y2,c):
        self.ret=self.call_function(7,[x1,y1,x2,y2,c])
        return self.ret
       
    def drawCircle(self, x,y,r,c):
        self.ret=self.call_function(8,[x,y,r,c])
        return self.ret
    
    def fillCircle(self, x,y,r,c):
        self.ret=self.call_function(9,[x,y,r,c])
        return self.ret
    
    def drawTriangle(self, x1,y1,x2,y2,x3,y3,c):
        self.ret=self.call_function(10,[x1,y1,x2,y2,x3,y3,c])
        return self.ret
    
    def fillTriangle(self, x1,y1,x2,y2,x3,y3,c):
        self.ret=self.call_function(11,[x1,y1,x2,y2,x3,y3,c])
        return self.ret
    
    def drawRoundRect(self, x1,y1,x2,y2,r,c):
        self.ret=self.call_function(12,[x1,y1,x2,y2,r,c])
        return self.ret
    
    def fillRoundRect(self, x1,y1,x2,y2,r,c):
        self.ret=self.call_function(13,[x1,y1,x2,y2,r,c])
        return self.ret

    
    def color_conversion(c):
        
        return c

    def call_function(self, fname,arg):
        try:
            self._waitACK= b''
            self._iter=len(arg)
            time.sleep(0.01)
            self.s.write(("{\"function\":\""+ str(fname) + "\",").encode())
            time.sleep(0.01)
            self.s.write(("\"lib\":\"graphics\",").encode())
            time.sleep(0.01)
            self.s.write("\"arg\":[".encode())
            for _index in range(self._iter-1):
                self.s.write(("\""+str(arg[_index])+"\",").encode())
                time.sleep(0.001)
            self.s.write(("\""+ str(arg[self._iter-1])+"\"").encode())
            time.sleep(0.001)
            self.s.write("]}".encode())
            time.sleep(0.001)
            self.s.write("done".encode())
            time.sleep(0.01)
            
            _waitACK=self.s.read(self.s.inWaiting())
            while(_waitACK.decode("UTF-8").find("True")<0 and _waitACK.decode("UTF-8").find("False")<0):
                _waitACK+= self.s.read(self.s.inWaiting())
                time.sleep(0.01)
            print(_waitACK.decode("UTF-8"))
            if(_waitACK.decode("UTF-8").find("True")<0):
                raise Exception("Arduino sent false")
            else:
                return True
        except:
            print("ran into exception:")
            raise Exception("Error on Python")
        

