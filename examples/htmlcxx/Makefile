htmlcxx-demo : htmlcxx-demo.cpp
	g++ htmlcxx-demo.cpp -o $@ `pkg-config --cflags --libs htmlcxx`
test :
	./htmlcxx-demo
clean :
	-@rm htmlcxx-demo
