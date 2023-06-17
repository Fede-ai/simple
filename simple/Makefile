all: compile link run

compile:
	g++ -c Main.cpp Player.cpp Player.h Game.cpp Game.h Enemy.cpp Enemy.h -IC:/SFML-2.5.1/include

link:
	g++ Main.o Player.o Game.o Enemy.o -o app -LC:/SFML-2.5.1/build/lib -lsfml-graphics -lsfml-window -lsfml-system

run:
	./app