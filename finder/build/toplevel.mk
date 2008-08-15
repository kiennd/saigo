all: $(PROGRAM) $(EXTRA)

$(PROGRAM) : $(MODULES)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.a: c_% include
	make -C $<
	cp $</$@ .

.PHONY: clean distclean fullclean

clean: 
	$(RM) $(TRASH)

distclean: clean
	$(RM) $(MODULES) $(PROGRAM)
 
fullclean: distclean 
	for m in $(SUBDIRS) ; do make -C $$m distclean ; done	
