import os
import time

# Do crappy animation
WIDTH = 30
offset = 0
loop = True
height = 10
while loop:
    os.system("cls")
    
    if offset > (WIDTH*2/3):
         print("\n" * height + " " * offset + "\\")
         height = height + 1
    elif offset > (WIDTH/3):
        print("\n"*height + " " * offset + "-")
    else:
         print("\n"*height + " " * offset + "/")
         height = height - 1
         
    #move the message a little to the left.
    offset +=1
    #if the entire message has moved 'through' the display then
    #break
    if offset >=WIDTH:
        loop = False
    #take out or change this line to speed up / slow down the display
    time.sleep(0.05)
	
os.system("cls")
time.sleep(0.1)
height = height - 1
print("\n" * height + " " * offset + "\|/")
time.sleep(2)