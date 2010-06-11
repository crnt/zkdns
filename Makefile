DIRS = lib-c lib-cpp src
all: $(DIRS)

.PHONY: clean $(DIRS)

lib-c:
	$(MAKE) -C $@
lib-cpp: lib-c
	$(MAKE) -C $@
src: lib-cpp
	$(MAKE) -C $@

clean:
	for DIR in $(DIRS); do $(MAKE) -C $$DIR clean; done
