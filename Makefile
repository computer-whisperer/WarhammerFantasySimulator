BUILD_DIR = build

.PSEUDO: ALL
ALL: $(BUILD_DIR)/wfs


CC = gcc

CFLAGS =

VPATH = src:inc


CFILES = main.c baddies.c characters.c core.c magick.c melee.c
INCLUDE_DIRS =  inc

OFILES = $(CFILES:%.c=$(BUILD_DIR)/%.o)

#Keep .o files for reuse
.SECONDARY: $OFILES

$(BUILD_DIR)/wfs: $(OFILES)
	$(CC) $(CFLAGS) -lm -o $@ $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS:%=-I%) -c -o $@ $<

	
