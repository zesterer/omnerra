#The name of the program
NAME=omnerra

FINAL=$(NAME)

COMPILER=g++
CPP_SOURCES=\
src/main.cpp \
src/application.cpp \
src/renderer.cpp \
src/loadshader.cpp \

CPP_CFLAGS=-Isrc/ `pkg-config --cflags glfw3` -Iglbinding/
CPP_LIBS=-lm `pkg-config --libs glfw3` -lglbinding

CPP_ADDITIONAL=-std=c++11 -Wall -fsanitize=address

CPP_LINES=`( find src -name '*.*' -print0 | xargs -0 cat ) | wc -l`

default: build

build: $(CPP_SOURCES)
	@echo "Building..."
	$(COMPILER) -o $(FINAL) $(CPP_CFLAGS) $(CPP_LIBS) $(CPP_ADDITIONAL) $(CPP_SOURCES)
	@echo "Built."
	@echo "There are $(CPP_LINES) of code."

run: $(FINAL)
	@echo "Running..."
	@./$(FINAL)

buildrun:
	@make build
	@make run

help:
	@echo "To compile, run 'make build'"
	@echo "To install, run 'sudo make install'"
