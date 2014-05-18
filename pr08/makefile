all: build

build: consumer producer server

consumer:
	gcc pv.c consumer.c -o Consumer

producer:
	gcc pv.c producer.c -o Producer

server:
	gcc pv.c sem_server.c -o Server

clean:
	rm Consumer
	rm Producer
	rm Server