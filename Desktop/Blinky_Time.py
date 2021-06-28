import time
import digitalio
import board

print("hello blinky")

led = digitalio.DigitalInOut(board.D26)
led.direction = digitalio.Direction.OUTPUT

while True:
   led.value= True
   time.sleep(0.5)
   led.value = False
   time.sleep(0.5)
