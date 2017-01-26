main : main.o BMPLoader.o lib/libglui.a
	g++ -O3  -I/usr/include/GL   main.o BMPLoader.o -Llib -lglui -L/usr/lib -lglut -lGL -lGLU  -lm  -o phase3

main.o : main.cpp lib/libglui.a
	g++ -O3 -c  -I/usr/include/GL -I/glui.h   main.cpp

BMPLoader.o : BMPLoader.cpp lib/libglui.a
	g++ -O3 -c  -I/usr/include/GL -I/glui.h   BMPLoader.cpp

clean:
	rm -f main.o BMPLoader.o

