CXXFLAGS=-fno-omit-frame-pointer -g -D_GNU_SOURCE

gperftools-demo : gperftools-demo.cpp
	g++ gperftools-demo.cpp -o $@ $(CXXFLAGS) `pkg-config --cflags --libs libprofiler`
test :
	./gperftools-demo
clean :
	-@rm gperftools-demo *.prof
