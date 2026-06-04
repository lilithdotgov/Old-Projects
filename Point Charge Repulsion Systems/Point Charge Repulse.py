from graphics import *
import numpy as np
import scipy as sci
import scipy.optimize as opt
import os
import time


def Dist(x1,y1,x2,y2):
    return np.lib.scimath.sqrt(((x1-x2)**2)+((y1-y2)**2))
    
def Force(D,q):
    try:
        return q/(D**2)
    except ZeroDivisionError:
        return 2 ** 32
    except ValueError:
        return 0

def main():
    win = GraphWin("Graph", 800, 800)
    zoom = 10
    #make starting better later lol
    x_axisP1 = Point(0,400)
    x_axisP2 = Point(800,400)
    x_axisL = Line(Point(x_axisP1.getX(),x_axisP1.getY()),Point(x_axisP2.getX(),x_axisP2.getY()))
    x_axisL.draw(win)
    
    y_axisP1 = Point(400,0)
    y_axisP2 = Point(400,800)
    y_axisL = Line(Point(y_axisP1.getX(),y_axisP1.getY()),Point(y_axisP2.getX(),y_axisP2.getY()))
    y_axisL.draw(win)

    class Points:
        def __init__(self,x,y,q):
            self.x = x
            self.y = y 
            self.q = q
        def update(self,x,y):
            self.x = x
            self.y = y
        def acs(self,n):
            p = [self.x,self.y,self.q]
            return p[n]

    

    P1 = Points(400,400,1)
    P2 = Points(500,400,-1)

    Point1 = Image(Point(P1.acs(0),P1.acs(1)),"red_point15px.png")
    Point2 = Image(Point(P2.acs(0),P2.acs(1)),"red_point15px.png")
    
    Point1.draw(win)
    Point2.draw(win)
    
    StartCall = win.getKey()
    if StartCall == "m":
        for i in range (0,100):
            time.sleep(0.03)
            
            
main()