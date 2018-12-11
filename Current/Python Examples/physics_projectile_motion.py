#-*-coding:utf8;-*-
import time
import os

from math import sin, cos, radians
g = 9.8 #I am defining the value of g so use it when using the Big 3 below

units    = ["in",  "ft",   "miles", "km",   "m", "cm", "mm"]
toMeters = [.0254, 0.3048, 1609.34, 1000.0, 1.0, 0.01, 0.001]

timeunits = ["s", "min", "hr"]
toSeconds = [1.0, 60.0, 3600.0]

#print a greeting message to the user below using the included print() function:
print("Allie Teagle's calculator")

#
# MENU
#
         
loop = True
while loop:
    print(" ")
    for i in range(len(units)):
        print(i,": ",units[i])

    print()
    selection = int(input("Select length units:  "))

    if selection not in range(len(units)):
        print("Please enter valid menu options")
    else:
        loop = False

print()

loop = True
while loop:
    print(" ")
    for i in range(len(timeunits)):
        print(i,": ",timeunits[i])

    print()
    timeselection = int(input("Select time units:  "))

    if timeselection not in range(len(timeunits)):
        print("Please enter valid menu options")
    else:
        loop = False

print()

# Determine lenth scalar and unit string
lenscalar = toMeters[selection]
timescalar = toSeconds[timeselection]
    
print("Velocity will be in (", units[selection], "/", timeunits[timeselection], ")");
#ask the user for the inputs of launch velocity and angle below. I will do the angle for you:
angle = float(input("What is the projectile's angle of launch: "))
inputStr = "What is the projectile's velocity at launch (" + units[selection] + "/" + timeunits[timeselection] + "): "
velocity = float(input(inputStr))


# Do crappy animation
WIDTH = 79
offset = 0
loop = True
while loop:
    os.system("cls")

    if offset > (WIDTH*2/3):
         print(" " * offset + "\\")
    elif offset > (WIDTH/3):
        print(" " * offset + "-")
    else:
         print(" " * offset + "/")
    
         
    #move the message a little to the left.
    offset +=1
    #if the entire message has moved 'through' the display then
    #break
    if offset >=WIDTH:
        loop = False
    #take out or change this line to speed up / slow down the display
    time.sleep(0.005)


#change the angle from degrees into radians below. I will do this for you:
angle = radians(angle)

#break up the velocity vector into x and y parts below using sin() and cos():

velx = (velocity * lenscalar * cos(angle)) / timescalar
vely = (velocity * lenscalar * sin(angle)) / timescalar

#Find the time in air below:
t = vely / g * 2
print(t)
#Find the max height below:
ht = t/2
y = vely * ht - .5 * g * ht**2

#Find the horizontal displacement (call it x) below:
x = velx * t

#Now report your results back to the user below with print() statements.
#You may want to use the round() function to round your answers.
print("--------------------------------------------------------------------")
print("The x component of initial velocity is ", velx / lenscalar * timescalar, " (", units[selection], "/", timeunits[timeselection], ")")
print("The y component of initial velocity is ", vely / lenscalar * timescalar, " (", units[selection], "/", timeunits[timeselection], ")")

print("Time in air is ", t / timescalar, " (", timeunits[timeselection], ")")
print("Maximum height is ", y / lenscalar, " (", units[selection], ")")
print("Horizontal distance is ", x / lenscalar, " (", units[selection], ")")

print("--------------------------------------------------------------------")
