#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Test Person";

void scope_demo(int count)
{
	log_info("count is: %d", count);

	if(count > 10) {
		int count = 100; //THIS IS DUMB

		log_info("count in if statement scope is %d", count);
	}

	log_info("count is at exit: %d", count);

	count = 3000;
	
	log_info("count after assign: %d", count);
}

int main(int argc, char *argv[]) 
{
	//test accessors
	log_info("My name: %s, age: %d", MY_NAME, get_age());

	int new_age = 100;
	set_age_by_val(new_age);
	log_info("Age is now: %d, new_age is: %d", get_age(), new_age);
	new_age = 103;
	debug("wut: %d", get_age());
	set_age_by_ref(&new_age);
	log_info("Age is now: %d, new_age is %d", get_age(), new_age);

	log_info("THE_SIZE: %d", *(THE_SIZE));
	print_size();

	int THE_SIZE_VAL = 9;
	THE_SIZE = &THE_SIZE_VAL;

	log_info("THE_SIZE after assign: %d", *(THE_SIZE));
	print_size();

	log_info("Ratio at first: %f", update_ratio(2.0));
	log_info("Ratio 2nd: %f", update_ratio(10.0));
	log_info("Ratio 3rd: %f", update_ratio(300.0));

	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	log_info("Count after calling demo: %d", count);

	return 0;
}
