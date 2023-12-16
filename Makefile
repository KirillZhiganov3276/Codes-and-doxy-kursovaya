all:
	g++ main.cpp ServerClientInterface.cpp Errors.cpp DataReader.cpp User.cpp ./md5/md5.cpp -o server -lcryptopp

unit:
	g++ unit.cpp ServerClientInterface.cpp Errors.cpp DataReader.cpp User.cpp ./md5/md5.cpp -o unittest -lcryptopp -lUnitTest++ 

clean:
	rm -f server
