HUFF = compression/hufftree.h compression/hufftree.c
FREQUENCY = compression/frequency.h compression/frequency.c
HASH = compression/hash_table.h compression/hash_table.c
HEADER = compression/header.h compression/header.c
COMPRESS = compression/compress.h compression/compress.c
DECOMPRESS = decompression/decompress.h decompression/decompress.c
MAIN = ./main.c

compile_huff:
	gcc $(HUFF) $(FREQUENCY) $(HASH) $(HEADER) $(COMPRESS) $(DECOMPRESS) $(MAIN)  -o huffman -g