obj-files = main.o Document.o Layer.o Record.o LayerGroup.o TextFormatter.o XmlFormatter.o PsdParser.o JsonFormatter.o

psdump: $(obj-files)
	g++ -arch x86_64 -L. -lpsd-0.9 $(obj-files) -o psdump

libpsd: adjustment.o
	gcc-4.2 -x c -arch x86_64 -fmessage-length=0 -pipe -std=gnu99 -Wno-trigraphs -fpascal-strings -fasm-blocks -O0 -Wreturn-type -Wunused-variable -mfix-and-continue -gdwarf-2 -Ilibpsd-0.9/include -c libpsd-0.9/src/*.c
	libtool -static -arch_only x86_64 *.o -o libpsd-0.9.a

adjustment.o: libpsd-0.9/src/adjustment.c


main.o: src/main.cpp src/Document.h src/formatter/TextFormatter.h src/formatter/XmlFormatter.h src/formatter/JsonFormatter.h src/parser/PsdParser.h
	g++ -c -Ilibpsd-0.9/include src/main.cpp
Document.o: src/Document.cpp src/Document.h
	g++ -c src/Document.cpp
Layer.o: src/Layer.cpp src/Layer.h
	g++ -c src/Layer.cpp
Record.o: src/Record.cpp src/Record.h
	g++ -c src/Record.cpp
LayerGroup.o: src/LayerGroup.cpp src/LayerGroup.h
	g++ -c src/LayerGroup.cpp
TextFormatter.o: src/formatter/TextFormatter.cpp src/formatter/TextFormatter.h
	g++ -c src/formatter/TextFormatter.cpp
XmlFormatter.o: src/formatter/XmlFormatter.cpp src/formatter/XmlFormatter.h
	g++ -c src/formatter/XmlFormatter.cpp
JsonFormatter.o: src/formatter/JsonFormatter.cpp src/formatter/JsonFormatter.h
	g++ -c src/formatter/JsonFormatter.cpp
PsdParser.o: src/parser/PsdParser.cpp src/parser/PsdParser.h
	g++ -c -Ilibpsd-0.9/include src/parser/PsdParser.cpp


.PHONY: clean
clean:
	rm *.o