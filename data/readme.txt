Deliverable 1

HOW TO GENERATE RANDOM UDP MESSAGES:

1. Run <bumblebee/generate_messages/main.cpp> once to create a build folder.
2. Move the double_truncnorm_data_i.txt files from <bumblebee/data> to the generate_messages build folder.
3. a) To print to console: Again, run <bumblebee/generate_messages/main.cpp>.
   b) To write to file: Comment in line 16 and comment out line 17 in <bumblebee/generate_messages/main.cpp>, then run the main.

Notes:

-The hiveNumber and date are hardcoded for sake of example in the Simulation default constructor. 
-The activity is 90% entries and exits, with 10% noise.


HOW TO READ AND PROCESS TEXT FILE OF UDP MESSAGES:

1. Run <bumblebee/process_messages/main.cpp> once to create a build folder.
2. Move UDP_messages_data_i.txt files from <bumblebee/data> to the process_messages build folder.
3. Again, run <bumblebee/process_messages/main.cpp> to print event information to the console.

Notes:

-Make sure the UDP text file is full of data. If not, recopy from the data folder.
-The window (in seconds) for entries/exits is defined as the global constant in parse.h, and can be modified there.


----


Deliverable 2

HOW TO CREATE AND TEST DATABASE:

1. Run <bumblebee/process_messages/main.cpp> once to create a build folder.
2. Move the UDP_messages_1weekdata_1.txt file from <bumblebee/data> to the process_messages build folder.
3. Run <bumblebee/process_messages/main.cpp>.
4. Now run <bumblebee/database/main.cpp> to access data from the range specified in selectwhereData(startDate, endDate, hiveNumber) (all parameters are strings). 


Notes:

- We store UDP messages in the dbupd and we store the events in dbevents, both of which are child classes of dbtable. 
- Events include exit and entry data derived from the the stream of UDP messages. 
- Dbtool is used a utility class used by the datable. 


-----------


Deliverable 3

The third deliverable focuses on the GUI. 

1. Run the GUI subdirectory. 
2. The main screen opens, and the navigation through different pages is pretty straightforward.
3. Use the Menu->Back from any page to come back to the homepage.

- The live data is a single page leading nowhere, so use the same menu bar to come back to the main page.
- The Historical Data page has two parts: Single Day Data and Multiple Day Data. You can switch back and forth these pages using the buttons on the top, and return to the main page using the menu bar as described above. 

We have used stack widgets for our GUI in order to make our program more professional. The features of our GUI are:

- All the GUI pages open in the same window. No pop-ups. 
- All the GUI pages have access to the same standard menu bar. 
- All the GUI pages have status bar at the bottom which we intend to use shortly for enhancing our GUI. 
- We have buttons and menu-bar in order to navigate between pages. 
- The Live Data is updated in the background by the use of multi-threading. 

Notes:

We are working on the live and historical data connecting with the database part, which will be one of the last part of this project. For now, you can see the complete structure of our GUI and how it works. 
