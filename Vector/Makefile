.SUFFIXES : .cpp .o

OBJECTS = vector_main.o 	# object file
SRCS = vector_main.cpp		# source file

CXX = g++# compile command
CPPFLAGS = -g -c# Option
HEADERS = Vector.hh

TARGET = test# Target file name

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

clean :
	rm -rf $(OBJECTS) $(TARGET) core

$(OBJECTS) : $(HEADERS) $(SRCS)
	$(CXX) $(CPPFLAGS) $(SRCS)
