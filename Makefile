PWD=$(shell pwd)
-include $(SDK_CONFIG_CONFIG)

#[major].[minor].[revision].[build]
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_REVISION = 0
VERSION_FULL = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_REVISION)
LIBNAME = xxx

BLUEZ_VERSION=5.56
BLUEZ=bluez-$(BLUEZ_VERSION)
BLUEZX=
BLUEZX_DIR=$(PWD)
BLUEZ_DIR=$(BLUEZX_DIR)/$(BLUEZ)

#** CFLAGS & LDFLAGS **
CFLAGS += $(CFLAGS_CUSTOMER)

CFLAGS += \
					-include $(SDK_INC_DIR)/utilx9.h \
					-include $(BLUEZX_DIR)/bluezx.h \
					-DVERSION="\"$(BLUEZ_VERSION)\"" \
					-DBLUEZX

CFLAGS += \
					-I./ \
					-I$(BLUEZX_DIR)/ \
					-I$(BLUEZ_DIR) -I$(BLUEZ_DIR)/client -I$(BLUEZ_DIR)/lib
LDFLAGS += \
					-L./
ARFLAGS = rcs

#** LIBXXX_OBJS **
LIBXXX_OBJS += \
							$(BLUEZ_DIR)/gdbus/client.o \
							$(BLUEZ_DIR)/gdbus/mainloop.o \
							$(BLUEZ_DIR)/gdbus/object.o \
							$(BLUEZ_DIR)/gdbus/polkit.o \
							$(BLUEZ_DIR)/gdbus/watch.o \
							$(BLUEZ_DIR)/src/shared/ad.o \
							$(BLUEZ_DIR)/src/shared/att.o \
							$(BLUEZ_DIR)/src/shared/btsnoop.o \
							$(BLUEZ_DIR)/src/shared/crypto.o \
							$(BLUEZ_DIR)/src/shared/ecc.o \
							$(BLUEZ_DIR)/src/shared/gap.o \
							$(BLUEZ_DIR)/src/shared/gatt-client.o \
							$(BLUEZ_DIR)/src/shared/gatt-db.o \
							$(BLUEZ_DIR)/src/shared/gatt-helpers.o \
							$(BLUEZ_DIR)/src/shared/gatt-server.o \
							$(BLUEZ_DIR)/src/shared/hci-crypto.o \
							$(BLUEZ_DIR)/src/shared/hci.o \
							$(BLUEZ_DIR)/src/shared/hfp.o \
							$(BLUEZ_DIR)/src/shared/io-glib.o \
							$(BLUEZ_DIR)/src/shared/io-mainloop.o \
							$(BLUEZ_DIR)/src/shared/log.o \
							$(BLUEZ_DIR)/src/shared/mainloop-notify.o \
							$(BLUEZ_DIR)/src/shared/mainloop-glib.o \
							$(BLUEZ_DIR)/src/shared/mgmt.o \
							$(BLUEZ_DIR)/src/shared/pcap.o \
							$(BLUEZ_DIR)/src/shared/queue.o \
							$(BLUEZ_DIR)/src/shared/ringbuf.o \
							$(BLUEZ_DIR)/src/shared/shell.o \
							$(BLUEZ_DIR)/src/shared/timeout-glib.o \
							$(BLUEZ_DIR)/src/shared/timeout-mainloop.o \
							$(BLUEZ_DIR)/src/shared/util.o \
							$(BLUEZ_DIR)/src/shared/uhid.o \
							$(BLUEZ_DIR)/client/adv_monitor.o \
							$(BLUEZ_DIR)/client/advertising.o \
							$(BLUEZ_DIR)/client/agent.o \
							$(BLUEZ_DIR)/client/display.o \
							$(BLUEZ_DIR)/client/gatt.o \
							$(BLUEZX_DIR)/bluetoothctl_api.o \
							$(BLUEZX_DIR)/bluezx.o

#** LIBXXX_yes **
LIBXXX_A = lib$(LIBNAME).a
#LIBXXX_A += libgdbus-internal.a
#LIBXXX_A += libshared-glib.a
#LIBXXX_SO = lib$(LIBNAME).so
#LIBXXXS_$(PJ_HAS_STATIC_LIB) += $(LIBXXX_A)
#LIBXXXS_$(PJ_HAS_SHARE_LIB) += -l$(LIBNAME)
LIBXXXS_yes += $(LIBXXX_A)

#** HEADER_FILES **
HEADER_FILES = \

#** librarys **
LIBS_yes = $(LIBXXXS_yes)
#** LIBS_yes, CLEAN_BINS, DUMMY_BINS  **
-include $(PJ_MK_USER_LIB)

LIBS += $(LIBS_yes) -lreadline -lncurses #-ltinfo
#-lgobject-2.0 -lgio-2.0 -lglib-2.0
#-lz -ldl -lpthread -lm

#** Clean **
CLEAN_OBJS = $(LIBXXX_OBJS)
CLEAN_LIBS = $(LIBXXX_A) $(LIBXXX_SO)

#** Target (CLEAN_BINS) **
CLEAN_BINS += \
						$(BLUEZX_DIR)/bluetoothctl_clone

#** Target (DUMMY_BINS) **
DUMMY_BINS += \
						$(BLUEZX_DIR)/bluezx_123

CLEAN_BINS += $(DUMMY_BINS)
CLEAN_OBJS += $(addsuffix .o, $(CLEAN_BINS))

#** Target (SHELL_SBINS) **
SHELL_SBINS = \

DUMMY_SBINS = $(SHELL_SBINS)

#** Target (CONFS) **
CONFS = \
				$(wildcard conf/*.conf)

TO_FOLDER =

#** include *.mk **
-include define.mk

.DEFAULT_GOAL = all
.SUFFIXES: .c .o

.PHONY: all clean distclean install romfs
all: $(CLEAN_BINS) $(CLEAN_LIBS)

%.o: %.c $(HEADER_FILES)
	@echo 'Compiling file: $<'
	$(CC) $(CFLAGS) -c -o"$@" "$<"
	@echo 'Finished compiling: $<'
	@echo ' '

$(CLEAN_BINS): $(CLEAN_OBJS) $(CLEAN_LIBS)
	@echo 'Building target: $@'
	$(CC) -o $@ $@.o $(LDFLAGS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	$(PJ_SH_RM) Makefile.bak $(CLEAN_BINS) $(CLEAN_BINS:=.elf) $(CLEAN_BINS:=.gdb)
	$(PJ_SH_RM) .configured .patched $(addsuffix *, $(CLEAN_LIBS)) $(CLEAN_OBJS) $(CLEAN_OBJS:%.o=%.c.bak) $(CLEAN_OBJS:%.o=%.h.bak)
	@for subbin in $(CLEAN_BINS); do \
		($(PJ_SH_RM) $(SDK_BIN_DIR)/$$subbin;); \
	done
	@for sublib in $(CLEAN_LIBS); do \
		($(PJ_SH_RM) $(SDK_LIB_DIR)/$$sublib*;); \
	done
	@for subheader in $(HEADER_FILES); do \
		($(PJ_SH_RM) $(SDK_INC_DIR)/$$subheader;); \
	done
	@for subshell in $(SHELL_SBINS); do \
		($(PJ_SH_RM) $(SDK_SBIN_DIR)/$$subshell;); \
	done
	@$(PJ_SH_RMDIR) build_xxx .meson_config build.meson meson_options.txt meson_public

distclean: clean

%.a: $(LIBXXX_OBJS)
	@echo 'Building lib (static): $@'
	$(AR) $(ARFLAGS) $@ $(LIBXXX_OBJS)
	@echo 'Finished building lib (static): $@'
	@echo ' '

%.so: $(LIBXXX_OBJS)
	@echo 'Building lib (shared): $@'
	$(CC) -shared $(LDFLAGS) -Wl,-soname,$@.$(VERSION_MAJOR) -o $@.$(VERSION_FULL) $(LIBXXX_OBJS)
	ln -sf $@.$(VERSION_FULL) $@.$(VERSION_MAJOR)
	ln -sf $@.$(VERSION_MAJOR) $@
	@echo 'Finished building lib (shared): $@'
	@echo ' '

install: all
	@for subbin in $(CLEAN_BINS); do \
		$(PJ_SH_CP) $$subbin $(SDK_BIN_DIR); \
		$(STRIP) $(SDK_BIN_DIR)/`basename $$subbin`; \
	done
	@for subshell in $(SHELL_SBINS); do \
		$(PJ_SH_CP) $$subshell $(SDK_SBIN_DIR); \
	done

romfs: install
ifneq ("$(HOMEX_ROOT_DIR)", "")
	@for subbin in $(DUMMY_BINS); do \
		$(PJ_SH_CP) $$subbin $(HOMEX_BIN_DIR); \
		$(STRIP) $(HOMEX_BIN_DIR)/`basename $$subbin`; \
	done
	@for subshell in $(DUMMY_SBINS); do \
		$(PJ_SH_CP) $$subshell $(HOMEX_SBIN_DIR); \
	done
endif
