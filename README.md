# SegFault


## Running the Program

In order to run this program, you need to use the given Makefile by simply typing "make" into the terminal. From there, you need to make sure you are running on an external lab machine using the: ssh stolafusername@rns202-<InsertNumber>.cs.stolaf.edu command. Then nagivate to the SegFault directory and run /usr/local/cs/cs251/bridge.py file.

## The Program
The program is able to create accounts, store account information, retrieve it, create images using the draw function, store the image data, convert image data from ppm to png, traverse and write to text files, create and change user information and display it all properly in the yaml files.

## Functionality
With this program you are able to create images through drawing them on a square pixel board and save them and then view them once you are finished as they are tied to your account. You can change your password, customize your user profile, view your saved images, title your images, and create accounts.

The only parts of the program that have not been implimented are the Searching, Generating, and browsing of images. 

## Potential Errors
The only potential error that you can encouter is with image data storage, where it won't index properly. While it works properly on some computers, when pushed and compiled on other computers, it would index the images wrong, resulting in the misreading of image information when returning to view images. 

We have all pulled and pushed and are all up to date, but the inconsistancy persists with no clear pathway on how to solve it. In order to manually fix it, you need to go into your actual account txt file in Accounts/ and move the image ids to after the user information line with the date, with a space and a newline inbetween each image.
