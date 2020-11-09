# Write your code here :-)
import serial
s=serial.Serial("/dev/serial0",115200)
import time

def set_bg_color(x):
    ret=call_function("fillScreen",[x])
    return ret

def set_font_size(x):
    ret=call_function("setTextSize",[x])
    return ret

def text(string,x,y):
    ret=call_function("drawString",[string,x,y])
    return ret

def drawLine(x1,y1,x2,y2,c):
    ret=call_function("drawLine",[x1,y1,x2,y2,c])
    return ret

def call_function(fname,arg):
    try:
        s.write("incomingFunction".encode())
        _waitACK=s.read(s.inWaiting())
        while(_waitACK.decode("UTF-8").find("g2g")<0):
            _waitACK+= s.read(s.inWaiting())
            time.sleep(0.01)
        _waitACK= b''
        _iter=len(arg)
        time.sleep(0.01)
        s.write(("{\"function\":\""+ str(fname) + "\",").encode())
        time.sleep(0.01)
        s.write("\"arg\":[".encode())
        for _index in range(_iter-1):
            s.write(("\""+str(arg[_index])+"\",").encode())
            time.sleep(0.001)
        s.write(("\""+ str(arg[_iter-1])+"\"").encode())
        time.sleep(0.001)
        s.write("]}".encode())
        time.sleep(0.001)
        s.write("done".encode())
        time.sleep(0.01)
        _ret=s.read(s.inWaiting())
        _retS=_ret.decode("UTF-8")
        if(_retS.lower()=="true"):
            return True
        else:
            return False
    except:
        return False
