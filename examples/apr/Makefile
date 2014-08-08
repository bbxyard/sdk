apr-demo : apr-demo.cpp
	g++ -o $@ $^ `pkg-config --cflags --libs apr-1`
test:
	./apr-demo "http://www.bbxyard.com"
clean :
	-@rm apr-demo 2>/dev/null
	-@rm -rvf apr-demo.dSYM 2>/dev/null

