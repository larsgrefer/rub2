all: clean build

build:
	mkdir -p target
	gcc philosoph.c -lpthread -o target/philosoph

clean:
	rm -f target/philosoph
	rm -fd target