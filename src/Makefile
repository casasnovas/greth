include ../config.mk

$(BINARY_NAME): $(OBJECT_FILES)
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.[oas] .*.flags *.ko .*.cmd .*.d .*.tmp *.mod.c .tmp_versions Module*.symvers
	rm -f $(BINARY_NAME)
