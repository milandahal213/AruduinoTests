# Write your code here :-)
import hub
import utime
s=hub.port.B
s.mode(hub.port.MODE_FULL_DUPLEX)
utime.sleep(1)
hub.port.B.baud(115200)


def set_bg_color(x):
    ret=call_function(1,"graphics",[x])
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

def call_function(fname, library,arg):
    try:
        _waitACK= b''
        arguments=""
        last_argument=""
        _iter=len(arg)
        utime.sleep(0.01)
        header="{\"function\":\""+ str(fname) + "\",\"lib\":\"" + str(library) + "\",\"arg\":["
        for _index in range(_iter-1):
            arguments+="\""+str(arg[_index])+"\","
        last_argument="\""+ str(arg[_iter-1])+"\""
        to_send=header+arguments+last_argument+"]}"+"done"
        s.write(to_send.encode())
        utime.sleep(0.01)

        _waitACK=s.read(s.inWaiting())
        while(_waitACK.decode("UTF-8").find("True")<0 and _waitACK.decode("UTF-8").find("False")<0):
            _waitACK+= s.read(s.inWaiting())
            time.sleep(0.01)
        s.flush()
        if(_waitACK.decode("UTF-8").find("True")<0):
            raise Exception("Arduino sent false")
        else:
            return _waitACK[:-6].decode("UTF-8")
    except:
        print("ran into exception:")
        raise Exception("Error on Python")
        return ("oka")

