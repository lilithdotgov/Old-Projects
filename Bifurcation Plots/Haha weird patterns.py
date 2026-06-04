from graphics import *
import numpy as np
import scipy as sci
import scipy.optimize as opt
import os

#functions to try it out on
#(2 * (x ** 3)) - (2 * (x ** 1))
#x **(1 / 3)

'''
def f(x):
    
    try:
        return x
    except ZeroDivisionError:
        return 2 ** 32
    except ValueError:
        return 0

    return roots
''' 
P = 2
def f(x):
    global P
    try:
        P = (x * (x - P))/(P * x)
        return P
    except ZeroDivisionError:
        P = 2 ** 32
        return P
    except ValueError:
        P = 0
        return P
    except OverflowError:
        P = 2 ** 32
        return P





def main():
    win = GraphWin("Graph", 800, 800)
    zoom = 10
    fake_zoom = 1
    starting = 400 + 0
    #make starting better later lol
    x_axisP1 = Point(0,400)
    x_axisP2 = Point(800,400)
    x_axisL = Line(Point(x_axisP1.getX(),x_axisP1.getY()),Point(x_axisP2.getX(),x_axisP2.getY()))
    x_axisL.draw(win)
    
    y_axisP1 = Point(400,0)
    y_axisP2 = Point(400,800)
    y_axisL = Line(Point(y_axisP1.getX(),y_axisP1.getY()),Point(y_axisP2.getX(),y_axisP2.getY()))
    y_axisL.draw(win)
    
    def graph(f):
        i = -400 + starting
        while i < 400:
            win.plot((i * 1) + 400, (-f(i / zoom) * zoom * fake_zoom) + 400, "red")

            
            dif = abs((f(i / zoom) * zoom * fake_zoom) - (f((i - 1) / zoom) * zoom * fake_zoom))
            if dif > 1:
                p1 = Point(i - 1 + 400, (-f((i - 1) / zoom) * zoom * fake_zoom) + 400)
                p2 = Point (i + 400, (-f(i / zoom) * zoom * fake_zoom) + 400)
                linedif = Line(Point(p1.getX(),p1.getY()),Point(p2.getX(),p2.getY()))
                linedif.setOutline("blue")
                linedif.draw(win)

            i = i + 1

    starting = 0
    graph(f)
    

    x_axisL.undraw()
    y_axisL.undraw()
    x_axisL.draw(win)
    y_axisL.draw(win)
main()


 #todo:
    #Implement Tkinter
    #Add The Functions. DONE
    #Get Way to Find Roots. DONE
    #Draw Polygons With graphics.py
    #Draw The Lines DONE
    #Add More Parameters To Functions (minor)
    #Add A Point That Is Movable And Causes The Lines To Update