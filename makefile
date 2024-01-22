CC = g++
CFLAGS = -c -Wall -DRAPIDJSON_HAS_STDSTRING=1
LDFLAGS = -lm -lpthread -lcrypt -lrt
UTILS = Utils
CONTAINERS = Containers
OPENCV = opencv
INCLUDES = -I ..


$(CC) $(LDFLAGS) opencv-saveimage.o -o opencv-saveimage -lopencv_core -lopencv_highgui
