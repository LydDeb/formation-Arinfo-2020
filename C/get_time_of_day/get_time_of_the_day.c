#include "color_print.h"
#include "minunit.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
//
#define VERSION_GET_CURRENT_PERIOD 1
//
static const char STR_Morning[] = "Morning";
static const char STR_Night[] = "Night";
static const char STR_Afternoon[] = "Afternoon";
static const char STR_Evening[] = "Evening";
static const char STR_ERROR[] = "ERROR";

//
uint8_t get_current_hour(void) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return (uint8_t)timeinfo->tm_hour;
}
//
void get_current_period_v1(uint8_t hour, char *period) {

    if ((22 <= hour && hour < 24) || (0 <= hour && hour <= 7)) {
        strcpy(period, STR_Night);
    } else if (8 <= hour && hour <= 12) {
        strcpy(period, STR_Morning);
    } else if (13 <= hour && hour <= 18) {
        strcpy(period, STR_Afternoon);
    } else if (19 <= hour && hour <= 21) {
        strcpy(period, STR_Evening);
    } else {
        strcpy(period, STR_ERROR);
    }
}
//
void get_current_period_v2(uint8_t hour, char *period) {

    switch (hour) {
    case 22:
    case 23:
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        strcpy(period, STR_Night);
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
        strcpy(period, STR_Morning);
        break;
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        strcpy(period, STR_Afternoon);
        break;
    case 19:
    case 20:
    case 21:
        strcpy(period, STR_Evening);
        break;

    default:
        strcpy(period, STR_ERROR);
        break;
    }
}
//
void get_current_period(uint8_t hour, char *period) {
    switch (VERSION_GET_CURRENT_PERIOD) {
    case 1:
        get_current_period_v1(hour, period);
        break;
    case 2:
        get_current_period_v2(hour, period);
        break;
    default:
        break;
    }
};
//
void test_setup(void) {}

void test_teardown(void) { /* Nothing */
}

MU_TEST(test_string_eq_8) {
    char period[10];
    get_current_period((uint8_t)8, period);
    mu_assert_string_eq(STR_Morning, period);
}
MU_TEST(test_string_eq_9) {
    char period[10];
    get_current_period((uint8_t)9, period);
    mu_assert_string_eq(STR_Morning, period);
}
MU_TEST(test_string_eq_10) {
    char period[10];
    get_current_period((uint8_t)10, period);
    mu_assert_string_eq(STR_Morning, period);
}
MU_TEST(test_string_eq_11) {
    char period[10];
    get_current_period((uint8_t)11, period);
    mu_assert_string_eq(STR_Morning, period);
}
MU_TEST(test_string_eq_12) {
    char period[10];
    get_current_period((uint8_t)12, period);
    mu_assert_string_eq(STR_Morning, period);
}

MU_TEST_SUITE(test_suite_morning) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_string_eq_8);
    MU_RUN_TEST(test_string_eq_9);
    MU_RUN_TEST(test_string_eq_10);
    MU_RUN_TEST(test_string_eq_11);
    MU_RUN_TEST(test_string_eq_12);
    // MU_RUN_TEST(test_string_eq_fail);
}

MU_TEST(test_string_eq_13) {
    char period[10];
    get_current_period((uint8_t)13, period);
    mu_assert_string_eq(STR_Afternoon, period);
}
MU_TEST(test_string_eq_14) {
    char period[10];
    get_current_period((uint8_t)14, period);
    mu_assert_string_eq(STR_Afternoon, period);
}
MU_TEST(test_string_eq_15) {
    char period[10];
    get_current_period((uint8_t)15, period);
    mu_assert_string_eq(STR_Afternoon, period);
}
MU_TEST(test_string_eq_16) {
    char period[10];
    get_current_period((uint8_t)16, period);
    mu_assert_string_eq(STR_Afternoon, period);
}
MU_TEST(test_string_eq_17) {
    char period[10];
    get_current_period((uint8_t)17, period);
    mu_assert_string_eq(STR_Afternoon, period);
}
MU_TEST(test_string_eq_18) {
    char period[10];
    get_current_period((uint8_t)18, period);
    mu_assert_string_eq(STR_Afternoon, period);
}

MU_TEST_SUITE(test_suite_afternoon) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_string_eq_13);
    MU_RUN_TEST(test_string_eq_14);
    MU_RUN_TEST(test_string_eq_15);
    MU_RUN_TEST(test_string_eq_16);
    MU_RUN_TEST(test_string_eq_17);
    MU_RUN_TEST(test_string_eq_18);
    // MU_RUN_TEST(test_string_eq_fail);
}

MU_TEST(test_string_eq_19) {
    char period[10];
    get_current_period((uint8_t)19, period);
    mu_assert_string_eq(STR_Evening, period);
}
MU_TEST(test_string_eq_20) {
    char period[10];
    get_current_period((uint8_t)20, period);
    mu_assert_string_eq(STR_Evening, period);
}
MU_TEST(test_string_eq_21) {
    char period[10];
    get_current_period((uint8_t)21, period);
    mu_assert_string_eq(STR_Evening, period);
}

MU_TEST_SUITE(test_suite_evening) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_string_eq_19);
    MU_RUN_TEST(test_string_eq_20);
    MU_RUN_TEST(test_string_eq_21);
    // MU_RUN_TEST(test_string_eq_fail);
}

MU_TEST(test_string_eq_22) {
    char period[10];
    get_current_period((uint8_t)22, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_23) {
    char period[10];
    get_current_period((uint8_t)23, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_0) {
    char period[10];
    get_current_period((uint8_t)0, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_1) {
    char period[10];
    get_current_period((uint8_t)1, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_2) {
    char period[10];
    get_current_period((uint8_t)2, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_3) {
    char period[10];
    get_current_period((uint8_t)3, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_4) {
    char period[10];
    get_current_period((uint8_t)4, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_5) {
    char period[10];
    get_current_period((uint8_t)5, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_6) {
    char period[10];
    get_current_period((uint8_t)6, period);
    mu_assert_string_eq(STR_Night, period);
}
MU_TEST(test_string_eq_7) {
    char period[10];
    get_current_period((uint8_t)7, period);
    mu_assert_string_eq(STR_Night, period);
}

MU_TEST_SUITE(test_suite_night) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_string_eq_22);
    MU_RUN_TEST(test_string_eq_23);
    MU_RUN_TEST(test_string_eq_0);
    MU_RUN_TEST(test_string_eq_1);
    MU_RUN_TEST(test_string_eq_2);
    MU_RUN_TEST(test_string_eq_3);
    MU_RUN_TEST(test_string_eq_4);
    MU_RUN_TEST(test_string_eq_5);
    MU_RUN_TEST(test_string_eq_6);
    MU_RUN_TEST(test_string_eq_7);

    // MU_RUN_TEST(test_string_eq_fail);
}

MU_TEST(test_string_24_error) {
    char period[10];
    get_current_period((uint8_t)24, period);
    mu_assert_string_eq(STR_ERROR, period);
}
MU_TEST(test_string_neg_error) {
    char period[10];
    get_current_period((uint8_t)-1, period);
    mu_assert_string_eq(STR_ERROR, period);
}
MU_TEST(test_string_ffff_error) {
    char period[10];
    get_current_period((uint8_t)0xffff, period);
    mu_assert_string_eq(STR_ERROR, period);
}

MU_TEST_SUITE(test_suite_error) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
    MU_RUN_TEST(test_string_24_error);
    MU_RUN_TEST(test_string_neg_error);
    MU_RUN_TEST(test_string_ffff_error);
}
//
int main(int argc, char *argv[]) {
    /*
       uint8_t hour = get_current_hour();
       CP_SET_BOLD;
       printf("It is %u h\n", hour);
       CP_RESET;
       char period[10];
       get_current_period(hour, period);
       printf("%s\n",period);
       return 0;
   */
    MU_RUN_SUITE(test_suite_morning);
    MU_RUN_SUITE(test_suite_afternoon);
    MU_RUN_SUITE(test_suite_evening);
    MU_RUN_SUITE(test_suite_night);
    MU_RUN_SUITE(test_suite_error);
    MU_REPORT();
    return MU_EXIT_CODE;
}
