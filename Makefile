# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schetty <schetty@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/04 16:52:35 by schetty           #+#    #+#              #
#    Updated: 2021/10/08 17:46:16 by schetty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and Linker
CC			:=	gcc

# Target Binary Program
NAME		:=	minitalk

# Directories
OBJDIR		:=	obj/
FTPRINTFDIR	:=	ft_printf/
FTPRINTF	:=	ft_printf/libftprintf.a

# Flags, Libraries and Includes
CFLAGS		:=	-Wall -Wextra -Werror

# Functions
ARCHIVE		:=	ar rc
INDEXER		:=	ranlib
DELETE		:=	rm -f
CREATEDIR	:=	mkdir -p
DELETEDIR	:=	rm -Rf

# Colors
RED			:=	"\033[1;31m"
GRN			:=	"\033[1;32m"
YLW			:=	"\033[1;33m"
CLR			:=	"\033[0m"

# Source, Objects and Resources
CLIENTSOURCE:=	client.c		utils.c
SERVERSOURCE:=	server.c

# Defauilt Make
all			:	outdir $(NAME)

outdir		:
				@ $(CREATEDIR) $(OBJDIR)

server		:	$(FTPRINTF)
				@ $(CC) $(CFLAGS) $(SERVERSOURCE) $(FTPRINTF) -o server

client		:	$(FTPRINTF)
				@ $(CC) $(CFLAGS) $(CLIENTSOURCE) $(FTPRINTF) -o client

bonus		:	outdir $(NAME)

# Link
$(NAME)		:	server	client
				@ echo $(GRN)$(NAME)$(CLR) Generated Successfully!

$(FTPRINTF)	:
				@ $(MAKE) -C $(FTPRINTFDIR) --no-print-directory

# Clean Objects
clean		:
ifneq ($(wildcard $(OBJDIR)),)
	@ $(MAKE) clean -C $(FTPRINTFDIR) --no-print-directory
	@ $(DELETEDIR) $(OBJDIR)
	@ echo $(YLW)$(basename $(NAME))$(CLR) Object Files Deleted!
else
	@ echo No $(RED)$(basename $(NAME))$(CLR)Object Files To Remove..
endif

# Full Clean
fclean		:
ifneq ($(wildcard server)$(wildcard client),)
	@ $(MAKE) fclean -C $(FTPRINTFDIR) --no-print-directory
	@ $(DELETE) server client
	@ $(DELETEDIR) $(OBJDIR)
	@ echo $(YLW)$(basename $(NAME))$(CLR) Binary \& Object Files Deleted!
else
	@ echo No $(RED)$(basename $(NAME))$(CLR) Binary Or Object Files To Removed..
endif

# Recompile
re			:	fclean all

# Non-File Targets
.PHONY		:	all clean fclean re server client bonus
