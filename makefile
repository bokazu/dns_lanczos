gcc_options = -std=c++17 -Wall --pedantic-errors
l_b = -llapacke -lblas

program : main.o printmat.o function_v2.o gso.o make_mat.o
	g++ -o $@ $^ $(l_b)

main.o : main.cpp
	g++ -c $< $(l_b)

printmat.o : printmat.cpp
	g++ -c $< $(l_b)

function_v2.o : function_v2.cpp
	g++ -c $< $(l_b)

gso.o : gso.cpp
	g++ -c $< $(l_b)

make_mat.o : make_mat.cpp
	g++ -c $< $(l_b)

run : program
	./program

clean:
	rm -f ./program

.PHONY : run clean
