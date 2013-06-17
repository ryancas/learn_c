#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void test_debug() 
{
	//no newline needed
	debug("I have brown hair.");
	debug("I am %d years old.", 30);
}

void test_log_err()
{
	log_err("It's broken.");
	log_err("There are %d problems in %s.", 20, "my code");
}

void test_log_warn() 
{
	log_warn("You can ignore this.");
	log_warn("Look here: %s.", "/var/log/broken");
}

void test_log_info()
{
	log_info("Something plain.");
	log_info("Float: %f", 1.3232f);
}

int test_check(char *file_name)
{
	FILE *input = NULL;
	char *block = NULL;

	block = malloc(100);
	check_mem(block); // Should work

	input = fopen(file_name, "r");
	check(input, "Failed to open %s.", file_name);

	free(block);
	fclose(input);
	return 0;

error:
	if(block) free(block);
	if(input) fclose(input);
	return -1;
}

int test_sentinel(int code)
{
	char *temp = malloc(100);
	check_mem(temp);

	switch(code) {
		case 1:
			log_info("Worked.");
			break;
		default:
			sentinel("I shouldn't be here.");
	}

	free(temp);
	return 0;

error: 
	if(temp) free(temp);
	return -1;
}

int test_check_mem()
{
	char *test = NULL;
	check_mem(test);

	free(test);
	return 1;

error: 
	return -1;
}

int test_check_debug() 
{
	int i = 0;
	check_debug(i != 0, "It was zero.");

	return 0;
error:
	return 1;
}

int main(int argc, char *argv[])
{
	check(argc == 2, "Need argument.");

	test_debug();
	test_log_err();
	test_log_warn();
	test_log_info();

	check(test_check("ex20.c") == 0, "Failed with ex20.c");
	check(test_check(argv[1]) == -1, "Failed with argv");
	check(test_sentinel(1) == 0, "test sentinel failed.");
	check(test_sentinel(100) == -1, "test sentinel failed.");
	check(test_check_mem() == -1, "test check mem failed.");
	check(test_check_debug() == -1, "test check debug failed.");

	return 0;

error:
	return 1;

}

