include ../config.mk

$(BINARY_NAME): $(OBJECT_FILES)
	@echo -n "(LD)" $@ " "
	@$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@
	@echo OK

%.o: %.c %.h
	@echo -n "(CC)" $@ " "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo OK

clean:
	rm -rf *.[oas] .*.flags *.ko .*.cmd .*.d .*.tmp *.mod.c .tmp_versions Module*.symvers
	rm -f $(BINARY_NAME)
