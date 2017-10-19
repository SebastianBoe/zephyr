obj-$(CONFIG_OPENTHREAD_PLAT) += platform/alarm.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/flash.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/logging.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/misc.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/platform.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/radio.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/random.o
obj-$(CONFIG_OPENTHREAD_PLAT) += platform/spi.o

obj-$(CONFIG_OPENTHREAD_SHELL) += platform/shell.o

ifdef CONFIG_OPENTHREAD_PLAT

ZEPHYRINCLUDE += -I$(O)/openthread/include
LIB_INCLUDE_DIR += -L$(O)/openthread/zephyr/lib

ifdef CONFIG_OPENTHREAD_FTD
OT_LIB = openthread-ftd
OT_CLI_LIB = openthread-cli-ftd
endif

ifdef CONFIG_OPENTHREAD_MTD
OT_LIB = openthread-mtd
OT_CLI_LIB = openthread-cli-mtd
endif

ifdef CONFIG_OPENTHREAD_SHELL
ALL_LIBS += $(OT_CLI_LIB)
endif

ALL_LIBS += $(OT_LIB) openthread-platform-utils mbedcrypto

all: lib-openthread

lib-openthread: outputexports
	$(MAKE) -f $(srctree)/ext/lib/openthread/Makefile.library O=$(O)

endif
