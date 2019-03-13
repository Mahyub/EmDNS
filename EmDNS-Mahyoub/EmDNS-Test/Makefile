CONTIKI_PROJECT = mDNS_test
all: $(CONTIKI_PROJECT)
CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"
CONTIKI_WITH_RPL=0
PROJECT_SOURCEFILES +=  EmDNS-log.c simple-energest.c ../platform/wismote/dev/xmem.c
CONTIKI = ../
include $(CONTIKI)/Makefile.include