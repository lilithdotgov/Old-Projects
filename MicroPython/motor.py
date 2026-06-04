import machine
import time

pwm = machine.PWM(machine.Pin(16), 50, duty_ns = 2000000)

def deg(x): #Takes input from 0 to 180 and converts it to proper lenght
    return int(1000000 * ((x/90) + 0.5))
    
while True:
    pwm.duty_ns(deg(60))
    time.sleep(0.5)
    pwm.duty_ns(deg(120))
    time.sleep(0.5)
        
