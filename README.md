# Project3

(a) This project includes 3 .txt files (anna_karenina.txt, dante.txt and lorem__ipsum.txt). These  are all included so as
to serve as paramters when calling the text-client.c function (which in the terminal would have an executable form of
text-server. While on that front, the file contains two .c files (text-server.c and text-client.c) as well as a Makefile.

(b) As mentioned above, the .txt files should be called used as one of the paramters when calling the text-client executable (in the form of './text-client dante.txt (Search-string)'. The function will not operate unless it can see that three arguments have been called. 
Text-client should be the first function called as it sets up the shared memory for text-server. To get the functions to work most effectively, after text-client is called, it will sleep for 10 seconds, where the user must make their call to text-server during this time. Failing to do so may result in the shared memory failing. 
The MakeFile serves to create the executables for the .c files as well as crerate a quick 'clean' function to erase the executables from your computer.

(c) In text-client.c, the function will create a shared memory instance containing the name and path of a .txt file and then pass that to text-server.c while it is sleeping. After this period, text-server.c will obtain the File contents and assign them to a local storage instance in the form of a char pointer. It will then go through this pointer to see if the data within contains the search string that was entered as a command line argument, at which point it will print that to the screen.
Conversely, text-server.c will accept the shared memory instance (the .txt file) and attempt to open it. Upon completion, it will write the contents of the file to the shared memory instance. After compleiting this, it will close the shared memory instance.
