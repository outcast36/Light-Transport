make:
	g++ -g -Wall -Wextra src/main/*.cpp -o render

clean:
	rm -f render
