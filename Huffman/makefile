HUFF = compression/hufftree.h compression/hufftree.c
PQ = compression/priority_queue.h compression/priority_queue.c
HASH = compression/hash_table.h compression/hash_table.c
HEADER = compression/header.h compression/header.c
COMPRESS = compression/compress.h compression/compress.c
DECOMPRESS = decompression/decompress.h decompression/decompress.c
MAIN = ./main.c
READFILE = readfile/readfile.h readfile/readfile.c

compile_huff:
	gcc $(HUFF) $(PQ) $(HASH) $(HEADER) $(COMPRESS) $(DECOMPRESS) $(READFILE) $(MAIN)  -o huffman -g