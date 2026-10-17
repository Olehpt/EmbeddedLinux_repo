CROSS_COMPILE ?= 0

ifeq ($(CROSS_COMPILE),1)
    CC = aarch64-linux-gnu-gcc
else
    CC = gcc
endif


CFLAGS = -Wall -Wextra -std=gnu11 -static
TARGET ?= uart_test
SRC = main.c

RPI_USER ?= host
RPI_HOST ?= RaspPi5.local
RPI_REMOTE := $(RPI_USER)@$(RPI_HOST)

UNIT_FILE ?= unit_uart_test.service
RPI_SERVICE_DIR = /etc/systemd/system
RPI_BIN_DIR = /usr/local/bin

.PHONY: build clean deploy install

build: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

deploy: build
	scp $(TARGET) $(RPI_REMOTE):/home/$(RPI_USER)
	
install: build
	scp $(TARGET) $(RPI_REMOTE):/tmp/$(TARGET)
	scp $(UNIT_FILE) $(RPI_REMOTE):/tmp/$(UNIT_FILE)
	ssh -t $(RPI_REMOTE) "\
		sudo systemctl stop $(UNIT_FILE) || true; \
		sudo install -m 755 /tmp/$(TARGET) $(RPI_BIN_DIR)/$(TARGET) && \
		sudo install -m 644 /tmp/$(UNIT_FILE) $(RPI_SERVICE_DIR)/$(UNIT_FILE) && \
		sudo systemctl daemon-reload && \
		sudo systemctl enable $(UNIT_FILE) && \
		sudo systemctl restart $(UNIT_FILE)"
