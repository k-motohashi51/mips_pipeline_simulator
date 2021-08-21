CC	=	gcc
CFLAGS	=	-g -Wall -O2

VPATH	=	./src:\
				./src/cpu/alu:\
				./src/cpu/ctrl:\
				./src/cpu/reg:\
				./src/mem:\
				./src/pipeline:\
				./src/tool:\
				./src/etc

TARGET	=	main
EXEDIR	=	./bin
EXES	=	$(addprefix $(EXEDIR)/,$(TARGET))

SRCROOT	=	./src
SRCDIRS	=	$(shell find $(SRCROOT) -type d)
SRCS	=	$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))

OBJDIR	=	./obj
OBJS	=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

INCDIR	=	./inc
INCS	=	$(wildcard $(INCDIR)/*.h)

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $(EXEDIR)/$@

$(OBJDIR)/%.o:	%.c
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

.PHONY:	clean
clean:
	$(RM) $(OBJS) $(EXES)
