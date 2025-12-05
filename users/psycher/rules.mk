SRC += psycher.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tap_dance.c
endif

ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
    SRC += rgb.c
endif

ifeq ($(strip $(IDLE_TIMEOUT_ENABLE)), yes)
    OPT_DEFS += -DIDLE_TIMEOUT_ENABLE
endif

TAP_DANCE_ENABLE = yes
BOOTMAGIC_ENABLE = yes
VIA_ENABLE = no
LTO_ENABLE = yes
