import traceback 
import time from grovepi 
import math from grove_rgb_led 

button = 3
sensor = 0

#Port for Button
print ("Setting pin mode...)
pinMode(button,"INPUT")
       
print ("Setting Text...")
setText ("Presiona el\nboton" )
       
print ("Setting RGB...")
setRGB (128, 0,0)
       
print ("Entering while true...")

while True:
       #setText ("Presiona el\nboton")
       try:
          print ("Reading button...")
          button status= digitalRead (button)
          #Read the Button status
          print ("Button", button_status)
              if button status:
                 #If the Button is in HIGH position, run the program
                 temp_raw = temp(sensor, '1.21')
                 temp_read = "Temp = " + str(int(temp_raw)) + "C"
                 setRGB (0,128,0)
                 setText (temp_read)
              else:
                 #If Button is in Off position, print "off" on the screen
                 setRGB (128, 0,0)
                 setText ("Presiona el\nboton" )
       except KeyboardInterrupt:
          print ("Key Error")
          break
       except (IOError, TypeError):
          print (traceback. format_exc())
       time.sleep (0.5)
