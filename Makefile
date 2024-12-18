make:
	g++ src/main/*.cpp -o render
verbose: 
	g++ -g -Wall -Wextra src/main/*.cpp -o render
clean:
	rm -f render
	rm -f write_test.pfm
