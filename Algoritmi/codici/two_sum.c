#include<stdio.h>
#include<stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize);

int main(int argc, char const *argv[])
{
    int* array = (int *) malloc(5*sizeof(int));
    for (int i = 0; i < 5; i++)
    {
        array[i]= rand() % 10+1;
        printf("%d ",array[i]);
    }
    
    int num = 5;
    int target = 10;
    int* solution = (int *) calloc(2, sizeof(int));
    

    solution = twoSum(array, num, target, solution); 
    printf("[%d, %d]", solution[0],solution[1]);
    return 0;
}


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    
    for(int i = 0; i < numsSize; i++)       //L'attuale complessività è data da n*n e quindi n^2, possiamo fare di meglio? Si con la programmazione dinamica.
    { for(int j = i+1; j < numsSize ; j++)
        {
            int sum = nums[i] + nums[j];
            if(sum == target) {
                printf("Somma trovata!\n");
                returnSize[0] = nums[i];
                returnSize[1] = nums[j];
                return returnSize;
            }
        }
    }
    printf("Somma non trovata\n");
    return 0;
}
