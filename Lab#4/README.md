The flickering problem is solved using double buffering. 
This assume that the drawing is done in memory and then copied to the screen, so the screen gets updated from the old image. 
We create a temporary HBITMAP in memory of the same size of the area we are going to draw.
 After drawing we just copy the whole thing in one shot to our window.