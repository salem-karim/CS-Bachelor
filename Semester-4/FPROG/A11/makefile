all: immutability loop join compare functionalSum

.outDir:
	mkdir -p cppout
	mkdir -p hsout

immutability: .outDir
	g++ -std=c++17 -lstdc++ immutability.cpp -o cppout/immutability
	./cppout/immutability
	ghc immutability.hs -o hsout/immutability
	./hsout/immutability
	

loop: .outDir
	g++ -std=c++17 -lstdc++ loop.cpp -o cppout/loop	
	./cppout/loop
	ghc loop.hs -o hsout/loop
	./hsout/loop

join: .outDir
	g++ -std=c++17 -lstdc++ join.cpp -o cppout/join
	./cppout/join
	ghc join.hs -o hsout/join
	./hsout/join
	
compare: .outDir
	g++ -std=c++17 -lstdc++ compare.cpp -o cppout/compare
	./cppout/compare
	ghc compare.hs -o hsout/compare
	./hsout/compare

functionalSum: .outDir
	g++ -std=c++17 -lstdc++ functionalSum.cpp -o cppout/functionalSum
	./cppout/functionalSum
	ghc functionalSum.hs -o hsout/functionalSum
	./hsout/functionalSum