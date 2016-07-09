.SUFFIXES : .cpp .o

OBJECTS = List.o 	# object file
SRCS = List.cpp		# source file

CXX = g++# compile command
CPPFLAGS = -g -c# Option
HEADERS = List.hh

TARGET = test# Target file name

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

clean :
	rm -rf $(OBJECTS) $(TARGET) core

$(OBJECTS) : $(HEADERS) $(SRCS)
	$(CXX) $(CPPFLAGS) $(SRCS)
