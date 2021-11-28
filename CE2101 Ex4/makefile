#Objects
ks_src = knapsack.c
u_ks_src = u_knapsack.c

TARGET = ks
TARGET_U = u_ks
CC = gcc

all: $(TARGET) $(TARGET_U)

$(TARGET): $(ks_src)
	$(CC) -o $@ $^

$(TARGET_U): $(u_ks_src)
	$(CC) -o $@ $^

clean:
	rm -f $(TARGET) $(TARGET_U)