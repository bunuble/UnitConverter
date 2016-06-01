compile:
	gcc -Wall -O2 UnitConversionGTK2.c -o UnitConversionGTK2 `pkg-config --libs --cflags gtk+-2.0`

run:
	./UnitConversionGTK2

clean:
	rm UnitConversionGTK2

