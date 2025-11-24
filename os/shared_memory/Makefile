ALL: broker consumer producer shm_helper

broker: shm_helper broker.c
	gcc -c broker.c
	gcc broker.o shm_helper.o -o broker
	rm broker.o

consumer: shm_helper consumer.c
	gcc -c consumer.c
	gcc consumer.o shm_helper.o -o consumer
	rm consumer.o

producer: shm_helper producer.c
	gcc -c producer.c
	gcc producer.o shm_helper.o -o producer
	rm producer.o

shm_helper: shm_helper.c
	gcc -c shm_helper.c

clean:
	rm shm_helper.o consumer producer broker 
