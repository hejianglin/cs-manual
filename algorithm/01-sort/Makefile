sort: sort.o main.cpp
	g++ -o $@ $^

sort.o: sort.cpp
	g++ -c $< -o $@

.PHONY: clean
clean:
	rm sort.o sort
