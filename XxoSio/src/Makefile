# .PHONY: clean

# CFLAGS=-Wall -g

# driver: driver.o rbtree.o

# clean:
# 	rm -f driver *.o

CC=gcc
CFLAGS=-I -Wall -g -DSENTINEL
OBJS=test-rbtree.o ../src/new_rbtree.o ../src/delete_rbtree.o ../src/rbtree_erase.o ../src/rbtree_find.o ../src/rbtree_insert.o ../src/rbtree_max.o ../src/rbtree_min.o ../src/rbtree_to_array.o ../src/rotate.o
TARGET=test-rbtree
$(TARGET): $(OBJS)
        $(CC) -o $@ $(OBJS)
        valgrind ./test-rbtree

# test: test-rbtree
#       ./test-rbtree
#       valgrind ./test-rbtree

test-rbtree.o: test-rbtree.c ../src/rbtree.h
../src/new_rbtree.o: ../src/new_rbtree.c
../src/rbtree_erase.o: ../src/rbtree_erase.c ../src/rotate.h
../src/rbtree_find.o: ../src/rbtree_find.c
../src/rbtree_insert.o: ../src/rbtree_insert.c ../src/rotate.h
../src/rbtree_max.o: ../src/rbtree_max.c
../src/rbtree_min.o: ../src/rbtree_min.c
../src/rbtree_to_array.o: ../src/rbtree_to_array.c
../src/rotate.o: ../src/rotate.c ../src/rotate.h
../src/delete_rbtree.o: ../src/delete_rbtree.c