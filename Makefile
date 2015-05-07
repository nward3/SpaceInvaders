CMP = gcc
MAIN = final
FUNC1 = gfx3
FUNC2 = finalfn
EXEC = $(MAIN)
FLAGS = -lm -lX11

$(EXEC): $(MAIN).o $(FUNC1).o $(FUNC2).o
	$(CMP) $(MAIN).o $(FUNC1).o $(FUNC2).o $(FLAGS) -o $(EXEC)

$(MAIN).o: $(MAIN).c $(FUNC1).h $(FUNC2).h
	$(CMP) -c $(MAIN).c

$(FUNC1).o: $(FUNC1).c
	$(CMP) -c $(FUNC1).c

$(FUNC2).o: $(FUNC2).c
	$(CMP) -c $(FUNC2).c

clean:
	rm *.o $(EXEC) *~
