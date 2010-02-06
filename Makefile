include config.mk

.PHONY: doc helper check $(BINARY_NAME)

all: $(BINARY_NAME)

$(BINARY_NAME):
	make -C src/
	cp $(SRCDIR)/src/$(BINARY_NAME) ./

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