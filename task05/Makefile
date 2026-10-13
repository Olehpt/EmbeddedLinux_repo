CROSS_COMPILE ?= 0

ifeq ($(CROSS_COMPILE),1)
    CC = aarch64-linux-gnu-gcc
else
    CC = gcc
endif


CFLAGS = -Wall -Wextra -std=gnu11 -static
TARGET ?= main
SRC = main.c

RPI_USER ?= host
RPI_HOST ?= RaspPi5.local
RPI_DIR ?= /home/host

.PHONY: all clean deploy

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

deploy: all
	scp $(TARGET) $(RPI_USER)@$(RPI_HOST):$(RPI_DIR)/
