#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int THE_SIZE_VAL = 1000;
int *THE_SIZE = &THE_SIZE_VAL;

static int THE_AGE = 37;

int get_age()
{ 
	return THE_AGE;
}

void set_age_by_val(int age) 
{
	//int temp = age;
	debug("Age is %d, setting to %d", THE_AGE, age);
	THE_AGE = age;
}

void set_age_by_ref(int *age)
{
	debug("Age is %d, setting to %d", THE_AGE, *age);
	THE_AGE = *age;
}

double update_ratio(double new_ratio)
{
	static double ratio = 1.0;

	double old_ratio = ratio;
	ratio = new_ratio;

	return old_ratio;
}

void print_size() 
{
	log_info("I think size is: %d", *(THE_SIZE));
}
