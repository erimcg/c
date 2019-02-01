ALL: broker sem_helper consumer producer

consumer: consumer.c sem_helper
	gcc -c consumer.c
	gcc sem_helper.o consumer.o -o consumer
	rm consumer.o

producer: producer.c sem_helper
	gcc -c producer.c
	gcc sem_helper.o producer.o -o producer
	rm producer.o

broker: sem_helper broker.c
	gcc -c broker.c
	gcc broker.o sem_helper.o -o broker
	rm broker.o

sem_helper: sem_helper.c
	gcc -c sem_helper.c

clean:
	rm *.o consumer producer broker
 
