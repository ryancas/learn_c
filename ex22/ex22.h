#ifndef _ex22_h
#define _ex22_h

// Define global variable
extern int *THE_SIZE;

// gets and sets internal variable
int get_age();
void set_age_by_val(int age);
void set_age_by_ref(int *age);

//update a variable
double update_ratio(double ratio);

void print_size();

#endif
