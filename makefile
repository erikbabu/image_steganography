CC = g++
CFLAGS = -Wall -Werror -pedantic -std=c++11
OBJS = Main.o FileUtils.o PicUtils.o Picture.o Colour.o
OPEN_CV1 = `pkg-config --cflags opencv`
OPEN_CV2 = `pkg-config --libs opencv`

img_steg: $(OBJS)
	$(CC) $(CFLAGS) $(OPEN_CV1) $(OBJS) $(OPEN_CV2) -o img_steg

Main.o: Main.cpp PicUtils.hpp

FileUtils.o: FileUtils.cpp FileUtils.hpp PicUtils.hpp

PicUtils.o: PicUtils.cpp PicUtils.hpp FileUtils.hpp Colour.hpp

Picture.o: Picture.cpp Picture.hpp Colour.hpp PicUtils.hpp

Colour.o: Colour.cpp Colour.hpp

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf img_steg *.o

.PHONY: clean
