#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message)
{
        if(errno) {
            perror(message);
        } else {
            printf("ERROR: %s\n", message);
        }

        exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef int *(*sort_cb)(int *numbers, int count, compare_cb cmp);

int *merge_sort(int *numbers, int count, compare_cb cmp)
{
    if(count == 0) {
        return (&numbers[0]);
    }
    //Find midpoint
    //This will return the floor when casting to int
    int mid = count/2;
	int i = 0;
	int j = 0;
    //sort left
    if(mid == 0) {
        return (&numbers[0]);
    }
    int *left = malloc(mid * sizeof(int));
    memcpy(left, numbers, mid * sizeof(int));
    int *left_sorted = merge_sort(left, mid, cmp);

    //sort right
    int *right = malloc((count - mid) * sizeof(int));
    for(i = mid; i<count; i++, j++) {
        right[j] = numbers[i];
    }
    int *right_sorted = merge_sort(right, count-mid, cmp);

    //merge
    int *sorted = malloc(count * sizeof(int));
    int left_length = mid;
    int right_length = count-mid;
    int counter = 0;
	i = 0;
	j = 0;
	while (left_length > 0 || right_length > 0) {
		if(left_length > 0 && right_length > 0) {
			if(cmp(left_sorted[i], right_sorted[j]) < 0) {
				sorted[counter] = left_sorted[i];
				counter++; 
				left_length--;
				i++;
			} else {
				sorted[counter] = right_sorted[j];
				counter++;
				right_length--;
				j++;
			}
		} else if(right_length > 0) {
			//Always pull from the right
			sorted[counter] = right_sorted[j];
			counter++;
			right_length--;
			j++;
		} else if (left_length > 0) {
			//Always pull from the left
			sorted[counter] = left_sorted[i];
			counter++;
			left_length--;
			i++;
		}
	}

    return sorted;
}



//Bubble sort
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory Error.");

    memcpy(target, numbers, count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j < count - 1; j++) {
            if(cmp(target[j], target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

int sorted_order(int a, int b)
{
    return a-b;
}

int reverse_order(int a, int b)
{
    return b-a;
}

int strange_order(int a, int b) 
{
    if(a == 0 || b == 0) {
        return 0;
    } else {
        return a%b;
    }
}

void test_sorting(int *numbers, int count, sort_cb sort, compare_cb cmp)
{
    int i = 0;
    int *sorted = sort(numbers, count, cmp);
    if(!sorted) die("Failed to sort as requested.");

    for(i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    free(sorted);
}

int main(int argc, char *argv[]) 
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char **inputs = argv + 1;

    int *numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error.");

    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    test_sorting(numbers, count, bubble_sort, sorted_order);
    test_sorting(numbers, count, merge_sort, sorted_order);
    test_sorting(numbers, count, bubble_sort, reverse_order);
    test_sorting(numbers, count, merge_sort, reverse_order);
    //test_sorting(numbers, count, bubble_sort, strange_order);

    free(numbers);
    return 0;
}
