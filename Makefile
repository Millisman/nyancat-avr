include Makefile.inc

LIBS = app mcu

CFLAGS = $(PRJCFLAGS) -I.

SRCDIR = .
DEPDIR = .dep
OBJDIR = obj

SOURCE = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SOURCE:.c=.o))
DEPS = $(patsubst $(OBJDIR)%, $(DEPDIR)%, $(OBJS:.o=.d))
LIBA = $(patsubst %, $(OBJDIR)/lib%.a, $(LIBS))
LIBL = -L$(OBJDIR) $(patsubst %, -l%, $(LIBS))

TARGET 	= $(notdir $(CURDIR)).hex
ELF 	= $(notdir $(CURDIR)).elf

all: $(TARGET)

upload: $(TARGET)
	@echo [UPL] $<
	@$(AVRDUDE) $(DUDEFLAGS) -U flash:w:$<

fuses:
	@echo [FUS] Settings fuses: $(FUSES)
	@$(AVRDUDE) $(DUDEFLAGS) $(FUSES)

clean:
	-@for lib in $(LIBS); do (cd $$lib; $(MAKE) clean); done
	-@rm -rf obj
	-@rm -rf .dep
	-@rm $(TARGET)

# test: force_look
# 	@cd test ; $(MAKE) ; ./test

$(DEPDIR)/%.d: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MM $< > $@
	@sed -i -e "s,$*.o:,$(OBJDIR)/$*.o $@: ,g" $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo [C++] $(notdir $<)
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.a: force_look
	@cd $(patsubst lib%, %, $(basename $(notdir $@)) ; $(MAKE) $(MFLAGS))

$(OBJDIR)/$(ELF): $(LIBA) $(OBJS)
	@echo [LNK] $(notdir $@)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBL) -o $@
	@echo
	@$(SIZE) $(SIZEFLAGS) $@

%.hex: $(OBJDIR)/%.elf
	@echo [HEX] $@
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

force_look:
	@true

-include $(DEPS)
