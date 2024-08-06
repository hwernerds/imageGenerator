AppTesting: display.o State.o File.o app3.o browse.o User.o FileImage.o /usr/local/cs/cs251/react.o
	g++ -g -Wall display.o State.o File.o app3.o browse.o User.o FileImage.o /usr/local/cs/cs251/react.o -lcurl

TestFile: test_File.o User.o File.o /usr/local/cs/cs251/react.o
	g++ -g -Wall test_File.o User.o File.o /usr/local/cs/cs251/react.o -lcurl



test_File.o: test_File.cpp
	g++ -g -Wall -c test_File.cpp


FileImage.o: FileImage.cpp
	g++ -g -Wall -c FileImage.cpp
display.o: display.cpp
	g++ -g -Wall -c display.cpp
State.o: State.cpp State.h 
	g++ -g -Wall -c State.cpp
File.o: File.cpp File.h
	g++ -g -Wall -c File.cpp
app3.o: app3.cpp
	g++ -g -Wall -c app3.cpp
browse.o: browse.cpp
	g++ -g -Wall -c browse.cpp
User.o: User.cpp User.h
	g++ -g -Wall -c User.cpp