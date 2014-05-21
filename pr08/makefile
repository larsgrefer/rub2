all: build

build: consumer producer server

consumer:
	gcc pv.c consumer.c -o consumer

producer:
	gcc pv.c producer.c -o producer

server:
	gcc pv.c sem_server.c -o server

clean:
	rm consumer
	rm producer
	rm server
