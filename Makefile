psdump: main.o Document.o Layer.o Record.o LayerGroup.o TextFormatter.o PsdParser.o
	g++ -arch x86_64 -L. -lpsd-0.9 main.o Document.o Layer.o Record.o LayerGroup.o TextFormatter.o PsdParser.o -o psdump

libpsd: adjustment.o
	gcc-4.2 -x c -arch x86_64 -fmessage-length=0 -pipe -std=gnu99 -Wno-trigraphs -fpascal-strings -fasm-blocks -O0 -Wreturn-type -Wunused-variable -mfix-and-continue -gdwarf-2 -Ilibpsd-0.9/include -c libpsd-0.9/src/*.c
	libtool -static -arch_only x86_64 *.o -o libpsd-0.9.a

adjustment.o: libpsd-0.9/src/adjustment.c


main.o: src/main.cpp
	g++ -c -Ilibpsd-0.9/include src/main.cpp
Document.o: src/Document.cpp
	g++ -c src/Document.cpp
Layer.o: src/Layer.cpp
	g++ -c src/Layer.cpp
Record.o: src/Record.cpp
	g++ -c src/Record.cpp
LayerGroup.o: src/LayerGroup.cpp
	g++ -c src/LayerGroup.cpp
TextFormatter.o: src/formatter/TextFormatter.cpp
	g++ -c src/formatter/TextFormatter.cpp
PsdParser.o: src/parser/PsdParser.cpp
	g++ -c -Ilibpsd-0.9/include src/parser/PsdParser.cpp


.PHONY: clean
clean:
	rm *.o