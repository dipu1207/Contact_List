*************************************
VOICE BASED CONTACT LIST
************************************
HOW TO RUN
1)OPEN solution on vs code 2010
2)Press F5 to run
************************************
How to add New Name
->Video demo is also added for same purpose in folder DemoVideo/AddContact/
Steps 
1) Enter name and contact info in respective fields
2) Press Start Rec new contact button
3) say the name 20 times
4) After this, program will generate lambda for the new name and name will be saved in the contact list.
5) Now your name is saved and you can now search it using voice
**********************************
How to search contact by voice
->Video demo is also added in folder DemoVideo/SearchContact
Steps
1)Click "PressToRecord" Button 
2) say the name to search
3)the prgm will calculate probability for all the names in contact list
4) Display name with highest prob in the label
**********************************
How to ReRecord the name (To make better lambda)
Steps
1)Enter the contact name to rerecord(***Make sure the spelling is same as when the contact was entered)
2)Press the button  "Start Recording" 
3)Utter 20 uterrances of the word
4)The prgm will generate new lambda for the name based in new recording
************************************
File Info
1)list.txt ->This will contain all the names and contact number.
2)buff.txt->Will contain log of the program
3)"CONTACTname"obs.txt ->will contain obs sequence of all the 20 training samples
