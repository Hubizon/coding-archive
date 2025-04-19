# Hubert Jastrzębski | Makefile | 2024-12-18
# https://srodowisko.tcs.uj.edu.pl/lab/makefile-cw.pdf

CC := g++
srcdir := ./
builddir := build
headerdir := $(builddir)/include
objdir := $(builddir)/obj
libdir := $(builddir)/lib
predir := $(builddir)/pre
asmdir := $(builddir)/asm
outdir := build
outdyndir := $(outdir)/dynamic
outstadir := $(outdir)/static

STATIC_LIB := $(libdir)/libmy.a
DYNAMIC_LIB := $(libdir)/libmy.so
h_files := power.h
SOURCES := $(wildcard $(srcdir)/*.c)
MAIN_OBJ = $(objdir)/main.o
OBJS := $(SOURCES:$(srcdir)/%.c=$(objdir)/%.o) # zmienia kazdy element w SOURCES z srcdir/cos.c na objdir/cos.o
OBJS_NOT_MAIN := $(filter-out $(MAIN_OBJ), $(OBJS))
ASMS := $(SOURCES:$(srcdir)/%.c=$(asmdir)/%.s)
PRES := $(SOURCES:$(srcdir)/%.c=$(predir)/%.e)
TARGET := $(outdir)/main
DYNAMIC_TARGET := $(outdyndir)/main
STATIC_TARGET := $(outstadir)/main

.PHONY: all clean clean-all pre asm libs clean-libs copy-headers normal static dynamic test test-static test-dynamic

.SECONDARY: $(OBJS) # zeby nie usuwac plikow obiektowych

all: copy-headers normal static dynamic

normal: $(TARGET)

$(STATIC_TARGET): $(MAIN_OBJ) $(STATIC_LIB)
        @mkdir -p $(outstadir)
        $(CC) $^ -o $(STATIC_TARGET)

static: $(STATIC_TARGET)

$(DYNAMIC_TARGET): $(MAIN_OBJ) $(DYNAMIC_LIB)
        @mkdir -p $(outdyndir)
        $(CC) $^ -o $@ -Wl,-rpath=$(dir $(DYNAMIC_LIB))

dynamic: $(DYNAMIC_TARGET)

$(headerdir)/%.h: $(srcdir)/%.h
        @mkdir -p $(headerdir)
        cp $^ $(headerdir)

copy-headers: $(h_files:$(src)%.h=$(headerdir)/%.h)

clean:
        @rm -rf $(TARGET) $(STATIC_TARGET) $(DYNAMIC_TARGET) $(OBJS) $(ASMS) $(PRES) $(STATIC_LIB) $(DYNAMIC_LIB) $(h_f>        -@rmdir $(objdir) $(headerdir) $(libdir) $(predir) $(asmdir) $(outdyndir) $(outstadir) $(outdir) 2> /dev/null |>        -@rmdir $(builddir) 2> /dev/null || true # - ignoruje bledy, 2> przekierowuje strumien bledow do niczego, || tr>
clean-all:
        @rm -rf $(builddir) $(outdir)

$(predir)/%.e: $(srcdir)/%.c $(h_files)
        @mkdir -p $(predir)
        $(CC) $< -E -o $@ # -E preprocessing

pre: $(PRES)

$(asmdir)/%.s: $(srcdir)/%.c $(h_files)
        @mkdir -p $(asmdir)
        $(CC) $< -S -o $@ # -S kompiluje do assemblera, $< bierze pierwszy argument, czyli np ./main.c, a $@ to np buil>
asm: $(ASMS)

$(libdir)/%.a: $(OBJS_NOT_MAIN) $(MAIN_OBJ)
        @mkdir -p $(libdir)
        ar rcs $@ $(OBJS_NOT_MAIN) # ar rcs - tworzy biblioteke statyczna $@ to target, czyli nazwa biblioteki, a $^ to>
$(libdir)/%.so: $(OBJS_NOT_MAIN)
        @mkdir -p $(libdir)
        $(CC) -shared $(OBJS_NOT_MAIN) -o $@

libs: $(STATIC_LIB) $(DYNAMIC_LIB)

clean-libs:
        @rm -f $(STATIC_LIB) $(DYNAMIC_LIB)

$(TARGET): $(OBJS)
        @mkdir -p $(dir $(TARGET)) # dir $(TARGET) zwraca tylko katalog TARGETa
        $(CC) $+ -o $@ # $+ reprezentuje wszystkie zaleznosci, a $@ to target

$(objdir)/%.o: $(srcdir)/%.c $(h_files) # tutaj ten drugi %.c dopasowuje sie do tego pierwszego %, czyli jak mamy targe>        @mkdir -p $(objdir)
        $(CC) $< -c -fPIC -o $@ # $<, czyli nazwa pierwszego niezbednika   -c, czyli sama kompilacja bez linkowania

test: all
        $(TARGET) 3 5
        $(TARGET) 2 10

test-static: static
        $(STATIC_TARGET) 3 5
        $(STATIC_TARGET) 2 10

test-dynamic: dynamic
        $(DYNAMIC_TARGET) 3 5
        $(DYNAMIC_TARGET) 2 10