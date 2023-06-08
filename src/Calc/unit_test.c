#include "../SmartCalc.h"
#include "check.h"

START_TEST(validation_1) {
  char str[] = "1+2+3-log(6)*sqrt(10)+ln(10)";
  int err = validation(str);
  ck_assert_int_eq(0, err);
}

START_TEST(validation_2) {
  char str[] = "1.123123+2mod4+(3*7)+sqrt(7)";
  int err = validation(str);
  ck_assert_int_eq(0, err);
}

START_TEST(validation_3) {
  char str[] = "1+2mod4+3*(7+1)+acos(1/2)+5^2";
  int err = validation(str);
  ck_assert_int_eq(0, err);
}

START_TEST(validation_4) {
  char str[] = "1+2mod4+3*(7+1)+asin(1/2)";
  int err = validation(str);
  ck_assert_int_eq(0, err);
}

START_TEST(validation_5) {
  char str[] = "^1+2mod4+3*(7+1)+atan(1/2)";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_6) {
  char str[] = "cos(1/2)+2mod4+3*(7+1)+sin(0)";
  int err = validation(str);
  ck_assert_int_eq(0, err);
}

START_TEST(validation_7) {
  char str[] = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";
  int err = validation(str);
  ck_assert_int_eq(0, err);
}

START_TEST(validation_8) {
  char str[] = "123456789+";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_9) {
  char str[] = "1/2+aco(3)-lo(6)+l(8)-asi(5)+at(3)+tcos(213)^";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_10) {
  char str[] = "";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_11) {
  char str[] = "!1+4-f+d/";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_12) {
  char str[] = "1+4/";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_13) {
  char str[] = "1+4*";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_14) {
  char str[] = "1+5-4*)";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_15) {
  char str[] = "1+((5-4)/410";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_16) {
  char str[] = "4mid2+(5-4)";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_17) {
  char str[] = "1+";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_18) {
  char str[] = "2^(2.1+1)-11mid2";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(validation_19) {
  char str[] = "2^(2.1+)-+11mod2";
  int err = validation(str);
  ck_assert_int_eq(1, err);
}

START_TEST(calc_and_pol_not_1) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "-cos(1)+3";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(2.459697, res, 6);
    ck_assert_str_eq("1.0 cos - 3.0 + ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_2) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "-0.1+0.2";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(0.100000, res, 6);
    ck_assert_str_eq("0.1 - 0.2 + ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_3) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "2^(2.1+1)-11mod2";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(7.574187, res, 6);
    ck_assert_str_eq("2.0 2.1 1.0 + ^ 11.0 2.0 mod - ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_4) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(-0.823571, res, 6);
    ck_assert_str_eq(
        "0.5 sin 1.0 cos - 0.5 tan + 0.5 acos + 1.0 asin - 1.0 atan - ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_5) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "sqrt(4.123456789)+3-1.12";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(3.910629, res, 6);
    ck_assert_str_eq("4.1 sqrt 3.0 + 1.1 - ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_6) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "log(+10.2)-ln(10.2)";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(-1.313787, res, 6);
    ck_assert_str_eq("10.2 + log 10.2 ln - ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_7) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "log(+10.2)-ln(10.2)";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(-1.313787, res, 6);
    ck_assert_str_eq("10.2 + log 10.2 ln - ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_8) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "11+(-2)^5";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(-21.000000, res, 6);
    ck_assert_str_eq("11.0 2.0 - 5.0 ^ + ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_9) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "log(+10.2)+ln(10.2)";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(3.330987, res, 6);
    ck_assert_str_eq("10.2 + log 10.2 ln + ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_10) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "sqrt(+4+1)+(-3+1)";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(0.236068, res, 6);
    ck_assert_str_eq("4.0 + 1.0 + sqrt 3.0 - 1.0 + + ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_11) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "sqrt(3+1)-(-3+1)";
  int res = validation(str);
  if (res == 0) {
    double num = 0;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(4.000000, res, 6);
    ck_assert_str_eq("3.0 1.0 + sqrt 3.0 - 1.0 + - ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_12) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "sin(x)";
  int res = validation(str);
  if (res == 0) {
    double num = 1.1;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq_tol(0.891207, res, 6);
    ck_assert_str_eq("x sin ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_13) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "+5/0";
  int res = validation(str);
  if (res == 0) {
    double num = 1.1;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_str_eq("5.0 0.0 / + ", ch);
    ck_assert_double_infinite(res);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_14) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "sqrt(-5.032)";
  int res = validation(str);
  if (res == 0) {
    double num = 1.1;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_nan(res);
    ck_assert_str_eq("5.0 - sqrt ", ch);
  }
  ck_assert_int_eq(0, res);
}

START_TEST(calc_and_pol_not_15) {
  Node_Stack *line = NULL;
  Node_Stack *pol_not = NULL;
  char str[] = "(+5*sqrt(4)-(-5+6))/3";
  int res = validation(str);
  if (res == 0) {
    double num = 1.1;
    char ch[256] = {0};
    line = parcer(str);
    pol_not = polish_notation(line);
    double res = result(pol_not, num);
    pol_not_char(pol_not, ch);
    ck_assert_double_eq(3.000000, res);
    ck_assert_str_eq("5.0 4.0 sqrt * 5.0 - 6.0 + - + 3.0 / ", ch);
  }
  ck_assert_int_eq(0, res);
}

Suite *suite_insert(void) {
  Suite *s = suite_create("Smart_Calc_test");
  TCase *tc = tcase_create("Calc_Test");

  tcase_add_test(tc, validation_1);
  tcase_add_test(tc, validation_2);
  tcase_add_test(tc, validation_3);
  tcase_add_test(tc, validation_4);
  tcase_add_test(tc, validation_5);
  tcase_add_test(tc, validation_6);
  tcase_add_test(tc, validation_7);
  tcase_add_test(tc, validation_8);
  tcase_add_test(tc, validation_9);
  tcase_add_test(tc, validation_10);
  tcase_add_test(tc, validation_11);
  tcase_add_test(tc, validation_12);
  tcase_add_test(tc, validation_13);
  tcase_add_test(tc, validation_14);
  tcase_add_test(tc, validation_15);
  tcase_add_test(tc, validation_16);
  tcase_add_test(tc, validation_17);
  tcase_add_test(tc, validation_18);
  tcase_add_test(tc, validation_19);
  tcase_add_test(tc, calc_and_pol_not_1);
  tcase_add_test(tc, calc_and_pol_not_2);
  tcase_add_test(tc, calc_and_pol_not_3);
  tcase_add_test(tc, calc_and_pol_not_4);
  tcase_add_test(tc, calc_and_pol_not_5);
  tcase_add_test(tc, calc_and_pol_not_6);
  tcase_add_test(tc, calc_and_pol_not_7);
  tcase_add_test(tc, calc_and_pol_not_8);
  tcase_add_test(tc, calc_and_pol_not_9);
  tcase_add_test(tc, calc_and_pol_not_10);
  tcase_add_test(tc, calc_and_pol_not_11);
  tcase_add_test(tc, calc_and_pol_not_12);
  tcase_add_test(tc, calc_and_pol_not_13);
  tcase_add_test(tc, calc_and_pol_not_14);
  tcase_add_test(tc, calc_and_pol_not_15);
  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  // setlocale(LC_ALL, "");
  int nf;
  Suite *s1;
  SRunner *sr;
  s1 = suite_insert();
  sr = srunner_create(s1);

  // srunner_run_all(sr, CK_ENV);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}