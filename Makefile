obj-files = build/main.o build/Document.o build/Layer.o build/Record.o build/LayerGroup.o build/TextFormatter.o build/XmlFormatter.o build/PsdParser.o build/JsonFormatter.o
libpsd-objects = adjustment.o bevel_emboss.o bitmap.o blend.o boundary.o brightness_contrast.o channel_image.o channel_mixer.o color.o color_balance.o color_mode.o color_overlay.o \
curves.o descriptor.o drop_shadow.o effects.o file_header.o fixed.o gaussian_blur.o gradient_blend.o gradient_fill.o gradient_map.o gradient_overlay.o hue_saturation.o image_data.o \
image_resource.o inner_glow.o inner_shadow.o invert.o layer_mask.o levels.o outer_glow.o path.o pattern.o pattern_fill.o pattern_overlay.o photo_filter.o posterize.o psd.o psd_system.o \
psd_zip.o rect.o satin.o selective_color.o solid_color.o stream.o stroke.o threshold.o thumbnail.o type_tool.o


psdump: build_dir build/libpsd-0.9 $(obj-files)
	g++ $(obj-files) $(libpsd-objects) -o build/psdump

build/libpsd-0.9:
	gcc -Ilibpsd-0.9/include -c libpsd-0.9/src/*.c
	touch build/libpsd-0.9

build_dir:
	mkdir -p build

build/main.o: src/main.cpp src/Document.h src/formatter/TextFormatter.h src/formatter/XmlFormatter.h src/formatter/JsonFormatter.h src/parser/PsdParser.h
	g++ -c -Wno-write-strings -Ilibpsd-0.9/include src/main.cpp -o build/main.o
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
	rm -f build/libpsd-0.9
	rm -f *.o
clean:
	rm -rf build
	rm -f *.o
