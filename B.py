import time
import board
import digitalio

print("hello blinky!")

led = digitalio.DigitalInOut(board.D18)
led.direction = digitalio.Direction.OUTPUT

while True :
      led.value = True
      
     