# Model compilation options
TARGET=lsd
FUN=fun_micro_macro_v.3.8
FUN_EXTRA= fun_time_step.h fun_init.h fun_analysis.h fun_macro.h fun_classes.h fun_external_sector.h fun_government.h fun_financial.h fun_banks.h fun_sector_external.h fun_sector_aggregates.h fun_sector_demand.h fun_entry_exit.h fun_firm_capital.h fun_firm_finance.h fun_firm_investment.h fun_firm_price.h fun_firm_production.h fun_firm_profit.h fun_firm_rnd.h fun_firm_sales.h fun_firm_inputs.h fun_capital_goods.h   fun_sector_analysis.h  fun_financial_analysis.h
SWITCH_CC=-Og -ggdb3
SWITCH_CC_LNK=


# System compilation options
LSDROOT=C:/Lsd-7.2-stable
SRC=src
EXT=.exe

# Libraries options
TCL_VERSION=86
PATH_TCL_HEADER=$(LSDROOT)/gnu64/include
PATH_TK_HEADER=$(LSDROOT)/gnu64/include
PATH_HEADER=$(LSDROOT)/gnu64/include
PATH_TCL_LIB=$(LSDROOT)/gnu64/lib
PATH_TK_LIB=$(LSDROOT)/gnu64/lib
PATH_LIB=$(LSDROOT)/gnu64/lib
TCL_LIB=-ltcl$(TCL_VERSION)
TK_LIB=-ltk$(TCL_VERSION)
LIBS=-lz

# Compiler options
CC=x86_64-w64-mingw32-g++
CC_CROSS=x86_64-w64-mingw32-
GLOBAL_CC=-march=native -std=gnu++14 -w
SSWITCH_CC=-mthreads -mwindows -O3
LSDROOT=C:/Lsd-7.2-stable

# Body of makefile (from src/makefile_base.txt)
# specify where are the sources of LSD
SRC_DIR=$(LSDROOT)/$(SRC)/

# location of tcl/tk and other headers
INCLUDE=-I$(PATH_TCL_HEADER) -I$(PATH_TK_HEADER) -I$(PATH_HEADER) -I$(LSDROOT)/$(SRC)

# link executable
$(TARGET)$(EXT): $(FUN).o $(SRC_DIR)main.o $(SRC_DIR)lsdmain.o \
$(SRC_DIR)analysis.o $(SRC_DIR)debug.o $(SRC_DIR)draw.o $(SRC_DIR)edit.o \
$(SRC_DIR)edit_dat.o $(SRC_DIR)file.o $(SRC_DIR)interf.o $(SRC_DIR)nets.o \
$(SRC_DIR)object.o $(SRC_DIR)report.o $(SRC_DIR)runtime.o $(SRC_DIR)set_all.o \
$(SRC_DIR)show_eq.o $(SRC_DIR)util.o $(SRC_DIR)variab.o
	$(CC) $(GLOBAL_CC) $(SWITCH_CC) $(FUN).o $(SRC_DIR)main.o $(SRC_DIR)lsdmain.o \
	$(SRC_DIR)analysis.o $(SRC_DIR)debug.o $(SRC_DIR)draw.o $(SRC_DIR)edit.o \
	$(SRC_DIR)edit_dat.o $(SRC_DIR)file.o $(SRC_DIR)interf.o $(SRC_DIR)nets.o \
	$(SRC_DIR)object.o $(SRC_DIR)report.o $(SRC_DIR)runtime.o $(SRC_DIR)set_all.o \
	$(SRC_DIR)show_eq.o $(SRC_DIR)util.o $(SRC_DIR)variab.o \
	$(SWITCH_CC_LNK) -L$(PATH_TCL_LIB) $(TCL_LIB) -L$(PATH_TK_LIB) $(TK_LIB) \
	-L$(PATH_LIB) $(LIBS) -o $(TARGET)

# compile modules
$(FUN).o: $(FUN).cpp $(FUN_EXTRA) model_options.txt \
$(SRC_DIR)check.h $(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch \
$(SRC_DIR)fun_head.h $(SRC_DIR)fun_head_fast.h
	$(CC) $(GLOBAL_CC) $(SWITCH_CC) $(INCLUDE) \
	-c $(FUN).cpp -o $(FUN).o
	
$(SRC_DIR)main.o: $(SRC_DIR)main.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)main.cpp -o $(SRC_DIR)main.o

$(SRC_DIR)lsdmain.o: $(SRC_DIR)lsdmain.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)lsdmain.cpp -o $(SRC_DIR)lsdmain.o

$(SRC_DIR)analysis.o: $(SRC_DIR)analysis.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)analysis.cpp -o $(SRC_DIR)analysis.o

$(SRC_DIR)debug.o: $(SRC_DIR)debug.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)debug.cpp -o $(SRC_DIR)debug.o

$(SRC_DIR)draw.o: $(SRC_DIR)draw.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)draw.cpp -o $(SRC_DIR)draw.o

$(SRC_DIR)edit.o: $(SRC_DIR)edit.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)edit.cpp -o $(SRC_DIR)edit.o

$(SRC_DIR)edit_dat.o: $(SRC_DIR)edit_dat.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)edit_dat.cpp -o $(SRC_DIR)edit_dat.o

$(SRC_DIR)file.o: $(SRC_DIR)file.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)file.cpp -o $(SRC_DIR)file.o

$(SRC_DIR)interf.o: $(SRC_DIR)interf.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)interf.cpp -o $(SRC_DIR)interf.o

$(SRC_DIR)nets.o: $(SRC_DIR)nets.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)nets.cpp -o $(SRC_DIR)nets.o

$(SRC_DIR)object.o: $(SRC_DIR)object.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)object.cpp -o $(SRC_DIR)object.o

$(SRC_DIR)report.o: $(SRC_DIR)report.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)report.cpp -o $(SRC_DIR)report.o

$(SRC_DIR)runtime.o: $(SRC_DIR)runtime.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)runtime.cpp -o $(SRC_DIR)runtime.o

$(SRC_DIR)set_all.o: $(SRC_DIR)set_all.cpp $(SRC_DIR)nolh.h \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)set_all.cpp -o $(SRC_DIR)set_all.o

$(SRC_DIR)show_eq.o: $(SRC_DIR)show_eq.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)show_eq.cpp -o $(SRC_DIR)show_eq.o

$(SRC_DIR)util.o: $(SRC_DIR)util.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)util.cpp -o $(SRC_DIR)util.o

$(SRC_DIR)variab.o: $(SRC_DIR)variab.cpp \
$(SRC_DIR)choose.h $(SRC_DIR)decl.h.gch $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)variab.cpp -o $(SRC_DIR)variab.o

# pre-compile headers
$(SRC_DIR)decl.h.gch: $(SRC_DIR)decl.h \
$(SRC_DIR)choose.h $(SRC_DIR)system_options.txt
	$(CC) $(GLOBAL_CC) $(SSWITCH_CC) $(INCLUDE) \
	-c $(SRC_DIR)decl.h -o $(SRC_DIR)decl.h.gch

clean:
	rm $(SRC_DIR)*.o $(SRC_DIR)*.gch $(FUN).o $(TARGET)*