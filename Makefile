SHELL := /bin/sh
SRCDIR := $(shell pwd)
DESTDIR := /usr/local/bin

PROJECT_NAME=greth
PROJECT_VERSION=0.1
BINARY_NAME=${PROJECT_NAME}

all: ${BINARY_NAME}

greth:
	make -C src/
	mv $(SRCDIR)/src/${BINARY_NAME} ./

.PHONY: doc helper check

doc:
	doxygen Doxyfile

install: all
	install ./${BINARY_NAME} $(DESTDIR)/
	@echo "greth has been installed"

uninstall:
	rm -f $(DESTDIR)/${BINARY_NAME}
	@echo "greth has been uninstalled"

tarball:
	git archive --format=tar --prefix=$(PROJECT_NAME)-$(PROJECT_VERSION)/ master > $(PROJECT_NAME)-$(PROJECT_VERSION).tar
	bzip2 $(PROJECT_NAME)-$(PROJECT_VERSION).tar

clean:
	make -C src/ clean
	rm -f ./${BINARY_NAME}
	rm -f ./doc/*