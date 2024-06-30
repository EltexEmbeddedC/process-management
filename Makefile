.PHONY: all clean

all:
	$(MAKE) -C Task1
	$(MAKE) -C Task2
	$(MAKE) -C Task3

clean:
	$(MAKE) -C Task1 clean
	$(MAKE) -C Task2 clean
	$(MAKE) -C Task3 clean
