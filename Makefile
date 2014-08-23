all:
	$(MAKE) -C ./shared all
	$(MAKE) -C ./matcher all
	$(MAKE) -C ./client all

clean:
	$(MAKE) -C ./shared clean
	$(MAKE) -C ./matcher clean
	$(MAKE) -C ./client clean

include trading.build
