CC = gcc

primes: forkprimes.o primes_driver.o
	gcc -ansi -o primes forkprimes.o primes_driver.o
