#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct subArray
{
    int size;
    int start;
    int end;
    int sum;
    double runtime;
    int * array;
};

#define N0 110

struct subArray * maxSubArraySumBrute(struct subArray * a)
{
    for (int i = 0; i < a->size; i++)
    {
        int tempSum = 0;

        for (int j = i; j < a->size; j++)
        {
            tempSum += a->array[j];

            if (tempSum > a->sum)
            {
                a->sum = tempSum;
                a->start = i;
                a->end = j;
            }
        }
    }

    return a;
}

int maximum(int left, int right)
{
    if (left > right)
    {
        return left;
    }

    return right;
}

int max(int left, int right, int mid)
{
    int temp = maximum(left, right);
    return maximum(mid, temp);
}

int maxSubArraySumCrossingMid(struct subArray * b, int low, int middle, int high)
{
    int leftSum = INT_MIN;
    int sum = 0;
    for (int i = middle; i >= low; i--)
    {
        sum += b->array[i];

        if (sum > leftSum)
        {
            leftSum = sum;
        }
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (int i = middle + 1; i <= high; i++)
    {
        sum += b->array[i];

        if (sum > rightSum)
        {
            rightSum = sum;
        }
    }

    return leftSum + rightSum;
}

int maxSubArraySumRecursive(struct subArray * b, int low, int high)
{
    /**
    if (b->size < N0)
    {
        b = maxSubArrayBrute(b);
        return;
    }
    **/

    if (high == low)
    {
        return b->array[high];
    }

    int middle = (high + low) / 2;

    int left = maxSubArraySumRecursive(b, low, middle);
    int right = maxSubArraySumRecursive(b, middle + 1, high);
    int mid = maxSubArraySumCrossingMid(b, low, middle, high);

    b->runtime = (double)clock();
    return max(left, right, mid);
}

int main()
{
    struct subArray * a = malloc(sizeof(struct subArray));
    struct subArray * b = malloc(sizeof(struct subArray));

    int size = 1;
    while (1)
    {
        int array[size];
        for (int i = 0; i < size; i++)
        {
            int num = (2 * rand() % size) - (rand() % size);
            array[i] = num;
        }

        a->start = 0;
        a->end = 0;
        a->sum = INT_MIN;
        a->size = size;
        a->array = array;
        a->runtime = 0;

        b->start = 0;
        b->end = 0;
        b->sum = INT_MIN;
        b->size = size;
        b->array = array;
        b->runtime = 0;

        clock_t startTime = clock();
        a = maxSubArraySumBrute(a);
        clock_t endTime = clock();
        a->runtime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

        startTime = clock();
        b->sum = maxSubArraySumRecursive(b, 0, size - 1);
        endTime = clock();
        b->runtime = (double)(endTime - startTime) /  CLOCKS_PER_SEC;

        printf("%d %f %f\n", size, a->runtime, b->runtime);

        if (b->runtime < a->runtime)
        {
            break;
        }

        size++;
    }

    free(a);
    free(b);

    return 0;
}
