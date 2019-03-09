/**
 * Note: The returned array must be malloced, assume caller calls free().
*/
#include <stdio.h>
#include <stdlib.h>

#define INT_MIN -1

typedef struct{
    int key;
    int val;
}DataType;

typedef struct abc{
    DataType data;
    struct abc *next;
}HashNode;

typedef struct{
    int size;
    HashNode *table;
}HashMap;

//f1_createHashMap
HashMap *CreateHashMap(int *nums,int size){
    HashNode* node;
    HashMap *map=(HashMap*)malloc(sizeof(HashMap));
    map->size=2*size;
    map->table=(HashNode *)malloc(sizeof(HashNode)*map->size);

    int j;
    for(j=0;j<map->size;j++){
        map->table[j].data.val=INT_MIN;
        map->table[j].next=NULL;
    }

    int i=0;
    while(i<size){
        int pos=abs(nums[i])%map->size;
        if(map->table[pos].data.val==INT_MIN)
        {
            map->table[pos].data.key=i;
            map->table[pos].data.val=nums[i];
        }
        else /*hash collision*/
        {
            HashNode *lnode=(HashNode*)malloc(sizeof(HashNode));
            lnode->data.key=i;
            lnode->data.val=nums[i];
            lnode->next=NULL;
            node = &(map->table[pos]);
            while(node->next!=NULL){
                node=node->next;
            }
            node->next=lnode;
        }
        i++;
    }
    return map;
}


int Put(int key,int value,HashMap map){
     int pos=abs(value)%map.size;
     HashNode *pointer=&(map.table[pos]);
     if(pointer->data.val==INT_MIN)
        {
         pointer->data.val=value;
         pointer->data.key=key;
        }
    else{
        while(pointer->next!=NULL)
             pointer=pointer->next;
        HashNode *hnode=(HashNode *)malloc(sizeof(HashNode));
        hnode->data.key=key;
        hnode->data.val=value;
        hnode->next=NULL;
        pointer->next=hnode;
   }
   return 1;
}

//f3_GetHashNode
int Get(int value,HashMap map){
    int pos=abs(value)%map.size;
    HashNode *pointer=&(map.table[pos]);
    while(pointer!=NULL){
            if(pointer->data.val==value)
                return pointer->data.key;
            else
                pointer=pointer->next;

        }
    return -1;
}

int* twoSum(int* nums, int numsSize, int target)
{
    int *ret = (int*)malloc(sizeof(int) * 2);
    HashMap *map = CreateHashMap(nums, numsSize);
    int i;
    for(i = 0; i < numsSize; i++){
        Put(i, nums[i], *map);
    }

    for(i = 0; i < numsSize; i++)
    {
        int val = target - nums[i];
        int key = Get(val, *map);

        if (-1 != key && key != i)
        {
            ret[0] = i;
            ret[1] = Get(val, *map);
            return ret;
        }
    }
    return NULL;
}

int main(void)
{	
	int nums[] = {7,11,15,16,17};
	int target = 26;
	int* ret = twoSum(nums, sizeof(nums), target);
	for (int i = 0; i < 2; i++){
		printf("%d, %d\n", ret[0], ret[1]);
	}
	return 0;
}
