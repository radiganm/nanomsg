#!/usr/bin/make -f
## makefile (for nanomsg)
## Mac Radigan

.PHONY: bootstrap bulid clean clobber install update
.DEFAULT_GOAL := bootstrap

bootstrap: build

build:
	rm -f CMakeCache.txt
	cmake -DNN_STATIC_LIB=ON -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true .
	$(MAKE) -f Makefile

update:
	git submodule init && git submodule update --recursive --remote

install:
	sudo $(MAKE) install

clean:
	$(MAKE) $@

clobber: clean

## *EOF*
