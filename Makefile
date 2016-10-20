all:
	cd src; make
	cd test; make

clean:
	cd test; make clean
	cd src; make clean