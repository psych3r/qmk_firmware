SRC += abdalrahman-ali.c

ifdef TAP_DANCE_ENABLE
    SRC += tap_dance.c
endif

ifeq ($(strip $(IDLE_TIMEOUT_ENABLE)), yes)
    OPT_DEFS += -DIDLE_TIMEOUT_ENABLE
endif

TAP_DANCE_ENABLE = yes
BOOTMAGIC_ENABLE = yes
VIA_ENABLE = no
LTO_ENABLE = yes
