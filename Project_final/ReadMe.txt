Download all the files in this directory.
Open them in your VSCode by "open folder" (or use other IDE).
Then input below command in the terminal. You should make sure that you are in the correct working directory.
>>>  g++ -shared -o mylib.dll -fPIC CrimeRecord.cpp Criminal.cpp Person.cpp System.cpp

Then you will get a mylib.dll file, this file make c++ connect to python.

Then run the CrimeManager.py to start the manage system.
