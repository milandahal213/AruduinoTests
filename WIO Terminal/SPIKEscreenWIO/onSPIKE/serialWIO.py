# Write your code here :-)
import hub
import utime
B=hub.port.B
B.mode(hub.port.MODE_FULL_DUPLEX)
utime.sleep(1)
hub.port.B.baud(115200)


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
        B.write("incomingFunction\n")
        print("sent incomingFunction")
        _waitACK=B.read(5)
        while(_waitACK.decode("UTF-8").find("g2g")<0):
            print(_waitACK)
            _waitACK+=B.read(5)
            utime.sleep(0.01)
        _waitACK=b''
        _iter=len(arg)
        utime.sleep(0.01)
        B.write("{\"function\":\""+fname + "\",\n")
        utime.sleep(0.01)
        B.write("\"arg\":[\n")
        for _index in range(_iter-1):
            B.write("\""+str(arg[_index])+"\",\n")
            print("sent index ", _index)
            utime.sleep(0.01)
        B.write("\""+ str(arg[_iter-1])+"\"\n")
        utime.sleep(0.01)
        B.write("]}\n")
        utime.sleep(0.01)
        B.write("done\n")
        utime.sleep(0.01)
        _ret=B.read(10)
        _retS=_ret.decode("UTF-8")
        if(_retS.lower()=="true"):
            return True
        else:
            return False
    except:
        return False

