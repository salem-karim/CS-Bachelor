all: exampleBasedTests propertyBasedTests 

.outputFolder:
	mkdir -p out

exampleBasedTests: .outputFolder
	g++ -std=c++17 -lstdc++ -lm -O3 exampleBasedTests.cpp -Wall -Wextra -Werror -o out/exampleBasedTests
	# ./out/exampleBasedTests

propertyBasedTests: .outputFolder
	g++ -std=c++17 -lstdc++ -lm propertyBasedTests.cpp -o out/propertyBasedTests
	# ./out/propertyBasedTests
