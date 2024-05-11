compile :
				g++ -c *.cpp

run :
				g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

start : 
				./sfml-app


r :
				make compile;make run; make start

testc : 
		g++ -c test.cpp

testr :
	  g++ test.o -o test-app -lsfml-graphics -lsfml-window -lsfml-system

tests : 
		./test-app

t : 
	make testc;make testr;make tests


