obj-files = build/main.o build/Document.o build/Layer.o build/Record.o build/LayerGroup.o build/TextFormatter.o build/XmlFormatter.o build/PsdParser.o build/JsonFormatter.o

psdump: build_dir build/libpsd-0.9.a $(obj-files)
	g++ -arch x86_64 -Lbuild -lpsd-0.9 $(obj-files) -o build/psdump

build/libpsd-0.9.a:
	gcc-4.2 -x c -arch x86_64 -fmessage-length=0 -pipe -std=gnu99 -Wno-trigraphs -fpascal-strings -fasm-blocks -O0 -Wreturn-type -Wunused-variable -mfix-and-continue -gdwarf-2 -Ilibpsd-0.9/include -c libpsd-0.9/src/*.c
	libtool -static -arch_only x86_64 *.o -o build/libpsd-0.9.a
	rm *.o

build_dir:
	mkdir -p build

build/main.o: src/main.cpp src/Document.h src/formatter/TextFormatter.h src/formatter/XmlFormatter.h src/formatter/JsonFormatter.h src/parser/PsdParser.h
	g++ -c -Ilibpsd-0.9/include src/main.cpp -o build/main.o
build/Document.o: src/Document.cpp src/Document.h
	g++ -c src/Document.cpp -o build/Document.o
build/Layer.o: src/Layer.cpp src/Layer.h
	g++ -c src/Layer.cpp -o build/Layer.o
build/Record.o: src/Record.cpp src/Record.h
	g++ -c src/Record.cpp -o build/Record.o
build/LayerGroup.o: src/LayerGroup.cpp src/LayerGroup.h
	g++ -c src/LayerGroup.cpp -o build/LayerGroup.o
build/TextFormatter.o: src/formatter/TextFormatter.cpp src/formatter/TextFormatter.h
	g++ -c src/formatter/TextFormatter.cpp -o build/TextFormatter.o
build/XmlFormatter.o: src/formatter/XmlFormatter.cpp src/formatter/XmlFormatter.h
	g++ -c src/formatter/XmlFormatter.cpp -o build/XmlFormatter.o
build/JsonFormatter.o: src/formatter/JsonFormatter.cpp src/formatter/JsonFormatter.h
	g++ -c src/formatter/JsonFormatter.cpp -o build/JsonFormatter.o
build/PsdParser.o: src/parser/PsdParser.cpp src/parser/PsdParser.h
	g++ -c -Ilibpsd-0.9/include src/parser/PsdParser.cpp -o build/PsdParser.o


.PHONY: clean, tidyup
tidyup:
	rm -f build/*.o
clean:
	rm -rf build