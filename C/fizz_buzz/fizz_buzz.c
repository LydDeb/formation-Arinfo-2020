#include "minunit.h"
#include "color_print.h"
#include <stdio.h>
#include <stdlib.h>

/*
1 <= n <= 100
n%3 == 0 --> Fizz
n%5 == 0 --> Buzz
n%3 == 0 && n%5 == 0 --> FizzBuzz
*/
//
/*
const char STR_Fizz[] = "Fizz";
const char STR_Buzz[] = "Buzz";
const char STR_FizzBuzz[] = "FizzBuzz";
const char STR_ERROR[] = "ERROR";
*/
// const char STR_NOT_A_FIZZBUZZ[] = "NOT_A_FIZZBUZZ";
//
char *int_to_FizzBuzz(int n) {
    char *char_n = malloc(sizeof(int));
    if (1 <= n && n <= 100) {
        if (n % 3 == 0 && n % 5 == 0) {
            free(char_n);
            return "FizzBuzz";
        } else if (n % 3 == 0) {
            free(char_n);
            return "Fizz";
        } else if (n % 5 == 0) {
            free(char_n);
            return "Buzz";
        } else {
            sprintf(char_n, "%d", n);
            return char_n;
        }
    } else {
        free(char_n);
        return "ERROR";
    }
}

//
void test_setup(void) {}

void test_teardown(void) {}

MU_TEST(test_3_Fizz) { mu_assert_string_eq("Fizz", int_to_FizzBuzz(3)); }
MU_TEST(test_5_Buzz) { mu_assert_string_eq("Buzz", int_to_FizzBuzz(5)); }
MU_TEST(test_15_FizzBuzz) {
    mu_assert_string_eq("FizzBuzz", int_to_FizzBuzz(15));
}
MU_TEST(test_1) { mu_assert_string_eq("1", int_to_FizzBuzz(1)); }
MU_TEST(test_100_Buzz) { mu_assert_string_eq("Buzz", int_to_FizzBuzz(100)); }
MU_TEST(test_fail_neg_1) { mu_assert_string_eq("ERROR", int_to_FizzBuzz(-1)); }
MU_TEST(test_fail_101) { mu_assert_string_eq("ERROR", int_to_FizzBuzz(101)); }

MU_TEST_SUITE(test_suite) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_3_Fizz);
    MU_RUN_TEST(test_5_Buzz);
    MU_RUN_TEST(test_15_FizzBuzz);
    MU_RUN_TEST(test_1);
    MU_RUN_TEST(test_100_Buzz);
    MU_RUN_TEST(test_fail_neg_1);
    MU_RUN_TEST(test_fail_101);
}
//
int main(int argc, char *argv[]) {

    for(int i = 1; i<=100; i ++){
        printf("%03d ", i);
        if(i%3 == 0){
            CP_SET_RED;CP_SET_BOLD;
            printf("%03d ", i%3);
            CP_RESET;
        }
        else{
            printf("%03d ", i%3);
        }
        if(i%5 == 0){
            CP_SET_GREEN;CP_SET_BOLD;
            printf("%03d ", i%5);
            CP_RESET;
        }
        else{
            printf("%03d ", i%5);
        }
        printf("%s\n", int_to_FizzBuzz(i));
    }
    MU_RUN_SUITE(test_suite);
    MU_REPORT();
    return MU_EXIT_CODE;
}