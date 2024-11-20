all: compile link run

compile:
	@echo * Compiling
	@g++ -c src/main.cpp -I"C:/SFML-2.6.1/include" -I"C:/glm" -I"C:/glad/include" -I./src -o build/main.o

release:
	@echo * Compiling release build
	@g++ -O3 -DNDEBUG -c src/main.cpp -I"C:/SFML-2.6.1/include" -I"C:/glm" -I"C:/glad/include" -I./src -o build/main.o
	@g++ build/main.o build/glad.o -o build/main -L"C:/SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system -lopengl32

link:
	@echo * Linking
	@g++ build/main.o build/glad.o -o build/main -L"C:/SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system -lopengl32

run:
	@echo * Running main.exe
	@build/main.exe

clean:
	del /f build\main.exe build\main.o

compile-glad: C:/glad/src/glad.c
	@echo * Compiling glad
	@g++ -c C:/glad/src/glad.c -I"C:/glad/include" -o build/glad.o