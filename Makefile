CC = g++
CFLAGS = -std=c++11
DEPS = Game.h Player.h Common.h AI.h GobangAI.h
OBJ = main.o Platform.o Human.o Gobang.o GobangAI.o AI.o Reversi.o

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp %.h $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o main
