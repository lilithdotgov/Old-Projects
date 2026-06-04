from graphics import *
import numpy as np
import scipy as sci
import scipy.optimize as opt
import os


#functions to try it out on
#(2 * (x ** 3)) - (2 * (x ** 1))
#x **(1 / 3)


def f(x):
    try:
        return (x**3)-x-1
    except ZeroDivisionError:
        return 2 ** 32
    except ValueError:
        return 0

#Below is code for derivative of any function
#f(x) is used as an example
dx = 0.000000001 #This is delta x
def df(x):
    try:
        return (f(x + dx) - f(x)) / dx
    except ZeroDivisionError:
        return 2 ** 32
    except ValueError:
        return 0

#Distance function and parameters below
h = 0
k = 1.00
def D(x):
    return np.sqrt(((x - h) ** 2) + ((f(x) - k) ** 2))
#All of this mess below is the root finding algorithm
#Note: The lower and upper guess ranges aren't the ranges of the roots
#It may find a root outside that range and include it in the final array
#For this project this is ok, and a good thing perhaps
#Just keep in mind in the future if you reuse this code for a root finder

#class All_Roots:
    

def root_finder(y):
    roots = np.array([], dtype=float)
    lowerGuess = -5
    upperGuess = 5
    step = 5

    i = 0
    while i < (abs(lowerGuess - upperGuess)) * step:
        Root = opt.fsolve(y, (lowerGuess + (i / step)))
        roots = np.append(roots, Root[0])
        i = i + 1

    #print ("Before Refining:", roots)

    i = 0
    i2 = 0
    roots = np.sort(roots)
    while i < (abs(lowerGuess - upperGuess) * step) - 1:
        if abs(roots[0 + i2] - roots[1 + i2]) < 0.001:
            roots = np.delete(roots, 1 + i2)
            i = i + 1
        else:
            i = i + 1
            i2 = i2 + 1
            
    #print("After Duplicates Are Deleted:", roots)

    listsize = np.size(roots)
    i = 0
    i2 = 0
    while i < listsize - 1:
        if -0.000001 < y(roots[i2]) and y(roots[i2]) < 0.000001:
            i = i + 1
            i2 = i2 + 1
        else:
            roots = np.delete(roots, i2)
            i = i + 1
                
    print("Finale Roots of",y.__name__,"(x):", roots)
    return roots

#root_finder()
#plug in function to use

def dD(x):
    return (D(x + dx) - D(x)) / dx
    
#roots_of_dD = root_finder(dD)
def intercept(x , i):
  return ((-1 / (df(roots_of_dD[i]))) * (x - roots_of_dD[i])) + f(roots_of_dD[i])


def main():
    win = GraphWin("Graph", 800, 800)
    zoom = 150
    
    x_axisP1 = Point(0,400)
    x_axisP2 = Point(800,400)
    x_axisL = Line(Point(x_axisP1.getX(),x_axisP1.getY()),Point(x_axisP2.getX(),x_axisP2.getY()))
    x_axisL.draw(win)
    
    y_axisP1 = Point(400,0)
    y_axisP2 = Point(400,800)
    y_axisL = Line(Point(y_axisP1.getX(),y_axisP1.getY()),Point(y_axisP2.getX(),y_axisP2.getY()))
    y_axisL.draw(win)
    
   
   
   
    i = -400
    while i < 400:
        win.plot((i * 1) + 400, (-f(i / zoom) * zoom) + 400, "red")
        
        
        dif = abs((f(i / zoom) * zoom) - (f((i - 1) / zoom) * zoom))
        if dif > 1:
            p1 = Point(i - 1 + 400, (-f((i - 1) / zoom) * zoom) + 400)
            p2 = Point (i + 400, (-f(i / zoom) * zoom) + 400)
            linedif = Line(Point(p1.getX(),p1.getY()),Point(p2.getX(),p2.getY()))
            linedif.setOutline("blue")
            linedif.draw(win)
            
        '''
        dif = abs((f(i / zoom) * zoom) - (f((i / zoom) - 1) * zoom))
        if dif > 1:
            p3 = Point(i - 1 + 400, (-f((i / zoom) - 1) * zoom) + 400)
            p4 = Point (i + 400, (-f(i / zoom) * zoom) + 400)
            linedif1 = Line(Point(p3.getX(),p3.getY()),Point(p4.getX(),p4.getY()))
            linedif1.draw(win)        
        '''
        #IDK why, but above code fills in all y-values greater than the function
        #I guess let's keep it for the future?
        i = i + 1
    '''  
    listsize = np.size(roots_of_dD)    
    i = 0
    while i < listsize:
        IntL = Line(Point(0,(-1 * (intercept(-400 / zoom, i) * zoom)) + 400),Point(800,(-1 * (intercept(400 / zoom, i)) * zoom) + 400))
        IntL.draw(win)
        i = i + 1
    '''
    
    x_axisL.undraw()
    y_axisL.undraw()
    x_axisL.draw(win)
    y_axisL.draw(win)
    
    #IntPointImg = Image(Point((-h * zoom) + 400, (-k * zoom) + 400), "red_point15px.png")
    '''
    IntPointImg.draw(win)
    '''
main()

 #todo:
    #Implement Tkinter
    #Add The Functions. DONE
    #Get Way to Find Roots. DONE
    #Draw Polygons With graphics.py
    #Draw The Lines DONE
    #Add More Parameters To Functions (minor)
    #Add A Point That Is Movable And Causes The Lines To Update