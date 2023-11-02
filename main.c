#include <stdio.h>
#include <sys/queue.h>
#include <stdlib.h>
#include "radix-tree.h"

typedef struct nvmed_cache {
	unsigned int lpaddr;
} NVMED_CACHE;


struct radix_tree_root cache_root;

static void pre_data_init()
{
    printf("pre_data_init \r\n");
    for(int i = 5; i < 10; i++) {
        NVMED_CACHE* cache = (NVMED_CACHE*)malloc(sizeof(NVMED_CACHE));
        cache->lpaddr = i;
        radix_tree_insert(&cache_root, cache->lpaddr, cache);
    }

    for(int i = 14; i < 18; i++) {
        NVMED_CACHE* cache = (NVMED_CACHE*)malloc(sizeof(NVMED_CACHE));
        cache->lpaddr = i;
        radix_tree_insert(&cache_root, cache->lpaddr, cache);
    }
}

void main()
{
    int find_blocks = 0;
    int start_block = 0, io_blocks = 20;
    INIT_RADIX_TREE(&cache_root);
	radix_tree_init();
    pre_data_init();
    NVMED_CACHE **cacheP, *cache;
    cacheP = calloc(io_blocks, sizeof(NVMED_CACHE*));
    find_blocks = radix_tree_gang_lookup(&cache_root, (void **)cacheP, start_block, io_blocks);
    printf("find_blocks = %d \r\n", find_blocks);
    if(find_blocks) {
        for(int i = 0; i < find_blocks; i++) {
            if(cacheP[i]) {
                printf("[%d] : %d \r\n", i, cacheP[i]->lpaddr);
            }
        }
    }

    start_block = 3, io_blocks = 6;
    find_blocks = 0;
    find_blocks = radix_tree_gang_lookup(&cache_root, (void **)cacheP, start_block, io_blocks);
    printf("find_blocks = %d \r\n", find_blocks);
    if(find_blocks) {
        for(int i = 0; i < find_blocks; i++) {
            if(cacheP[i]) {
                printf("[%d] : %d \r\n", i, cacheP[i]->lpaddr);
            }
        }
    }
    return;
}