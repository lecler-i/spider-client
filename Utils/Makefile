##
## Makefile for sana_c in /home/sana_c/dev/lib
## 
## Made by Cedric
## Login   <sana_c@epitech.net>
## 
## Started on  Wed Apr  9 15:27:22 2014 Cedric
## Last update Mon Sep 22 14:39:21 2014 Cedric
##

NAME		= libUtils.a

CC		= g++

RM		= rm -f

DIR_UNIX_SRC	= ./Unix/Sources/

DIR_UNIX_INC	= ./Unix/Includes/

DIR_COMMON_SRC	= ./Common/Sources/

DIR_COMMON_INC	= ./Common/Includes/

UNIX_FILES	= ThreadUnix.cpp \
		  MutexUnix.cpp \
		  DynamicLibraryUnix.cpp \
		  TCPClientUnix.cpp \
		  TCPServerUnix.cpp

COMMON_FILES	= Exceptions.cpp \
		  EventManager.cpp \
		  ScopedMutex.cpp \
		  Ini.cpp \
		  Vector2.cpp \
		  Vector3.cpp \
		  Vector4.cpp

CXXFLAGS	= -Wall -Wextra -I$(DIR_COMMON_INC) -I.

UNIX_SRC	= $(addprefix $(DIR_UNIX_SRC),$(UNIX_FILES))

COMMON_SRC	= $(addprefix $(DIR_COMMON_SRC),$(COMMON_FILES))

UNIX_OBJ	= $(UNIX_SRC:.cpp=.o)

COMMON_OBJ	= $(COMMON_SRC:.cpp=.o)

ifeq ($(DEBUG), 1)
	CXXFLAGS += -g3
endif

all:		$(NAME)

$(NAME):	$(UNIX_OBJ) $(COMMON_OBJ)
		ar rc $(NAME) $(UNIX_OBJ) $(COMMON_OBJ)
		ranlib $(NAME)

debug_init:
		$(eval CXXFLAGS += -g3)

debug:		debug_init re

clean:
		$(RM) $(UNIX_OBJ) $(COMMON_OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		re all fclean clean debug_init debug
