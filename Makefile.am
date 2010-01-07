bin_PROGRAMS = beep
beep_SOURCES = beep.c

installed_beep = $(DESTDIR)$(bindir)/`echo beep|sed '$(transform)'`
setuid_root_mode = a=rx,u+s

INSTALL_BEEP = \
	p=beep; \
	echo $(INSTALL_PROGRAM) $$p $(installed_beep); \
	$(INSTALL_PROGRAM) $$p $(installed_beep); \
	echo chown root $(install_beep); \
	chown root $(install_beep); \
	echo chmod $(setuid_root_mode) $(installed_beep); \
	chmod $(setuid_root_mode) $(installed_beep); 

install-root: beep$(EXEEXT)
	@$(INSTALL_BEEP)

install-exec-local: beep$(EXEEXT)
	@$(INSTALL_BEEP)

