#include "str.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void str_print(str_t *str);

void str_print(str_t *str)
{
  printf("str: %s\n", str->str);
  printf("len: %d\n", str->len);
  printf("cap: %d\n", str->cap);
}

int main()
{
  // new
  printf("new\n");
  str_t str;
  str_new(&str);
  str_print(&str);
  assert(strcmp(str.str, "") == 0);
  assert(str.len == 0);
  assert(str.cap == 1);

  // append
  printf("\nappend\n");
  str_cappend(&str, "hello", 5);
  str_print(&str);
  assert(strcmp(str.str, "hello") == 0);
  assert(str.len == 5);
  assert(str.cap == 6);

  // clear
  printf("\nclear\n");
  str_clear(&str);
  str_print(&str);
  assert(strcmp(str.str, "") == 0);
  assert(str.len == 0);
  assert(str.cap == 6);

  // set
  printf("\nset\n");
  str_cset(&str, "alligator", 9);
  str_print(&str);
  assert(strcmp(str.str, "alligator") == 0);
  assert(str.len == 9);
  assert(str.cap == 10);

  // insert
  printf("\ninsert\n");
  str_insert(&str, 3, "hi", 2);
  str_print(&str);
  assert(strcmp(str.str, "allhiigator") == 0);
  assert(str.len == 11);
  assert(str.cap == 12);

  str_insert(&str, 0, "hello ", 6);
  str_print(&str);
  assert(strcmp(str.str, "hello allhiigator") == 0);
  assert(str.len == 17);
  assert(str.cap == 18);

  str_insert(&str, str.len, " world", 6);
  str_print(&str);
  assert(strcmp(str.str, "hello allhiigator world") == 0);
  assert(str.len == 23);
  assert(str.cap == 24);

  // resize
  printf("\nresize\n");
  str_resize(&str, 3);
  str_print(&str);
  assert(strcmp(str.str, "hel") == 0);
  assert(str.len == 3);
  assert(str.cap == 4);

  str_resize(&str, 11);
  str_print(&str);
  assert(strcmp(str.str, "hel") == 0);
  assert(str.len == 3);
  assert(str.cap == 12);

  str_cappend(&str, "lo world", 7);
  str_print(&str);
  assert(strcmp(str.str, "hello worl") == 0);
  assert(str.len == 10);
  assert(str.cap == 12);
  str_delete(&str);

  // compare
  printf("\ncompare\n");
  int eq = 0;
  char bl[6];
  str_t str1;
  str_new(&str1);
  str_t str2;
  str_new(&str2);
  str_cset(&str1, "hello", 5);
  str_cset(&str2, "hello", 5);
  assert(strcmp(str1.str, "hello") == 0);
  assert(strcmp(str2.str, "hello") == 0);

  eq = str_compare(&str1, &str2);
  printf("str1: %s\n", str1.str);
  printf("str2: %s\n", str2.str);
  if (eq == 0)
  {
    sprintf(bl, "true");
  }
  else
  {
    sprintf(bl, "false");
  }
  printf("eq: %s\n", bl);
  assert(strcmp(str1.str, str2.str) == 0);

  str_cset(&str2, "hi", 2);
  eq = str_compare(&str1, &str2);
  printf("str1: %s\n", str1.str);
  printf("str2: %s\n", str2.str);
  if (eq == 0)
  {
    sprintf(bl, "true");
  }
  else
  {
    sprintf(bl, "false");
  }
  printf("eq: %s\n", bl);
  assert(strcmp(str1.str, str2.str) != 0);

  str_cset(&str2, "hello world", 11);
  eq = str_compare(&str1, &str2);
  printf("str1: %s\n", str1.str);
  printf("str2: %s\n", str2.str);
  if (eq == 0)
  {
    sprintf(bl, "true");
  }
  else
  {
    sprintf(bl, "false");
  }
  printf("eq: %s\n", bl);
  assert(strcmp(str1.str, str2.str) != 0);

  // delete
  printf("\ndelete\n");
  str_delete(&str1);
  str_delete(&str2);

  // move
  printf("\nmove\n");
  str_t m1;
  str_new(&m1);
  str_t m2;
  str_new(&m2);
  str_cset(&m1, "hello", 5);
  str_cset(&m2, "world", 5);
  str_move(&m1, &m2);
  str_print(&m1);
  assert(strcmp(m1.str, "world") == 0);
  str_delete(&m1);

  // escape
  printf("\nescape\n");
  str_t str_e;
  str_new(&str_e);
  str_cset(&str_e, "{\"key\":\"value\n\"}", 16);
  str_escape(&str_e);
  str_print(&str_e);
  assert(strcmp(str_e.str, "{\\\"key\\\":\\\"value\\n\\\"}") == 0);
  str_delete(&str_e);

  // erase
  printf("\nerase\n");
  str_t str3;
  str_new(&str3);
  str_cappend(&str3, "hello", 5);
  str_erase(&str3, 2, 2);
  str_print(&str3);
  assert(strcmp(str3.str, "heo") == 0);
  assert(str3.len == 3);
  assert(str3.cap == 6);

  return 0;
}
