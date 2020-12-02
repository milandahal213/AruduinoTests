import requests

Key = "0EFA5BCF"
urlBase = "https://api.m5stack.com/"
urlValue = urlBase + "v1/"+ Key +"/exec"
def Post():
     propValue = "from m5stack import *\nfrom m5ui import *\nfrom uiflow import *\nsetScreenColor(0xFFFF00)\nlcd.print('tata', 0, 0, 0xffffff)"
     try:
          response = requests.post(urlValue,data=propValue)
          print(response.text)
          response.close()
     except:
          print('error with Put')

Post()



