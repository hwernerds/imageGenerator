# imageGenerator


## Description:

The Image Generator project is a versatile application that allows users to create, store, and manage digital images tied to user accounts. This program provides features for drawing images on a pixel board, storing account information, and converting image data from PPM to PNG format. It also supports account management, including creating and modifying user profiles.

## Running the Program

To run this program, follow the steps below:

1. Compile with Makefile:

    I) Open the terminal and navigate to the project directory.
    II)Compile the program by typing:

       make
   
2. Connect to the Lab Machine:

    Use the following command to SSH into the external lab machine:

        ssh stolafusername@rns202-.cs.stolaf.edu
   
3. Navigate to the Project Directory:

    Go to the SegFault directory.
   
4. Run the Program:

    Execute the bridge file by running:

        /usr/local/cs/cs251/bridge.py

## Features

Account Management:

- Create new user accounts.
- Store and retrieve account information securely.
- Customize user profiles, including passwords and personal information.
  
Image Creation & Storage:

- Draw images on a square pixel board.
- Save images and tie them to user accounts for future retrieval.
- Convert image data from PPM to PNG format.
  
Data Management:

- Traverse and write data to text files.
- Manage image metadata and user profiles.
- Display stored information in YAML files for easy reading.
  
User Interaction:

- View saved images tied to your account.
- Title images for easy identification and management.

## Potential Errors

### Image Data Storage Error:
- The program may incorrectly index image data on some systems, leading to misreading when viewing saved images.
- This inconsistency appears during compilation on different machines and may cause issues with image retrieval.
  
### Manual Fix:
To manually correct image data indexing:

- Navigate to the Accounts/ directory.
- Open the user account text file corresponding to your profile.
- Adjust the image IDs so they appear after the user information line (with the date).
- Ensure there is a space and a newline between each image entry.
