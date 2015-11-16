all:
	clear
	g++ -o teste imageloader.cpp Cube.cpp main.cpp -lGL -lGLU -lglut -lm
	./teste
run:
	./teste
clean:
	rm -rf *o trabalhocg
