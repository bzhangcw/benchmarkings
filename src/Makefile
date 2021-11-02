CC     = clang
CFLAGS = -std=c99 -O2 -DNDEBUG

C_INCS = -I$(COPT_HOME)/include
C_LIBS = -L$(COPT_HOME)/lib -lcopt



all: load_pd

load_pd: load_pd.c
	$(CC) $(CFLAGS) $(C_INCS) -o load_pd load_pd.c $(C_LIBS)
clean:
	rm -f load_pd
