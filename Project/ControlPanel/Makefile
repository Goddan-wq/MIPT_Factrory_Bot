FQBN = arduino:avr:uno
PORT = COM13

all:
	arduino-cli compile -b $(FQBN)

program:
	arduino-cli upload -b $(FQBN) -p $(PORT)

clean:
	rm "build" -r
