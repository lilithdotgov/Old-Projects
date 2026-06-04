from graphics import *
import numpy as np
import os
from PIL import Image, ImageDraw
import time

start = time.time()

os.chdir(r"C:\Users\15512\Desktop\Python Projects\Image Manipulation Fun")
image_name = ""
image = Image.open(image_name)
period = 1.5 * (image.size[1] / 12)

def normalize(y):
    y = y - ((np.floor(y / (12 * period))) * (12 * period))
    return y

def rainbow():
    with Image.open(image_name) as image: #TODO change "testsubject.jpg" to method to find image file name
        resolution = image.size
        draw = ImageDraw.Draw(image)
        xres = resolution[0]
        yres = resolution[1]
        x = 0 
        y = 0 
        functional_y = 0
        red = 0
        green = 0.5
        blue =0.5
        while y != yres:
            pcolor = image.getpixel((x,y))
            draw.point((x,y),(int(red * pcolor[0]),int(green * pcolor[1]),int(blue * pcolor[2])))
            x = x + 1
            if x == xres:
                red = (1 + np.exp(-1 * ((((functional_y / period) - 6)/3)**8)))
                blue = (1 + np.exp(-1 * ((((functional_y / period) - 2)/3)**8))) + (np.exp(-1 * ((((functional_y / period) - 14)/3)**8)))
                green = (1 + np.exp(-1 * ((((functional_y / period) - 10)/3)**8))) + (np.exp(-1 * ((((functional_y / period) + 2)/3)**8)))                
                x = 0
                y = y + 1
                functional_y = y
                if period < (image.size[1] / 12):
                    functional_y = normalize(y)
        image.save("wild.png")
        image.show()
rainbow()

end = time.time()
print("Calculation time: ", end - start)

'''
older methods of colors:
using color density diagram:
    red = 4 * np.exp(-1 * abs((40/17) * np.sin((np.pi / 50) * ((y / 1)+ 19))))
    green = 2.8 * np.exp(-1 * abs((25/17) * np.sin((np.pi / 50) * ((y / 1)- 24))))
    blue = 3.5 * np.exp(-1 * abs((35/15) * np.sin((np.pi / 40) * ((y / 1)- 14))))
sum of sines:
    red = 1 * ((3 / 80) * abs((30 * np.sin(np.pi * (y - 0) / (12 * period))) + ((10 / 3) * np.sin(3 * np.pi * (y - 0) / (12 * period)))) + 1)
    blue = 1 * ((3 / 80) * abs((30 * np.sin(np.pi * (y - 9) / (12 * period))) + ((10 / 3) * np.sin(3 * np.pi * (y - 9) / (12 * period)))) + 1)
    green = 1 * ((3 / 80) * abs((30 * np.sin(np.pi * (y - 5) / (12 * period))) + ((10 / 3) * np.sin(3 * np.pi * (y - 5) / (12 * period)))) + 1)
power of sines:
        red = (2 - (abs(np.sin(np.pi * (((y / period) + 1) / (12))) ** 5)))
        blue = (2 - (abs(np.sin(np.pi * (((y / period) - 4) / (12))) ** 5)))
        green = (2 - (abs(np.sin(np.pi * (((y / period) - 9) / (12))) ** 5)))
'''

'''
with Image.open("TestSubject.jpg") as image:
    Image.eval(image, multiply())
    image.show
'''


