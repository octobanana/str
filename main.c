#include "str.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void print_title(const char *title);
void print_str(str_t *str);

void test_new();
void test_append();
void test_clear();
void test_reserve();
void test_set();
void test_insert();
void test_resize();
void test_compare();
void test_move();
void test_erase();
void test_escape();

void print_title(const char *title)
{
  printf("\n----------------\n");
  printf("%s", title);
  printf("\n----------------\n");
}

void print_str(str_t *str)
{
  printf("str: %s\n", str->str);
  printf("len: %d\n", str->len);
  printf("cap: %d\n", str->cap);
}

void test_new()
{
  print_title("new");

  str_t str;
  str_new(&str);

  print_str(&str);

  assert(strcmp(str.str, "") == 0);
  assert(str.len == 0);
  assert(str.cap == 1);

  str_delete(&str);

  str_t *strp = malloc(sizeof(str_t));
  str_new(strp);

  print_str(strp);

  assert(strcmp(strp->str, "") == 0);
  assert(strp->len == 0);
  assert(strp->cap == 1);

  str_delete(strp);
  free(strp);
}

void test_append()
{
  print_title("append");

  str_t *str = malloc(sizeof(str_t));
  str_new(str);

  str_t str2;
  str_new(&str2);

  str_cappend(str, "Hello, World!", 8);
  print_str(str);

  assert(strcmp(str->str, "Hello, W") == 0);
  assert(str->len == 8);
  assert(str->cap == 9);

  str_cset(&str2, "orld!", 5);

  str_append(str, &str2);

  print_str(str);
  assert(strcmp(str->str, "Hello, World!") == 0);

  str_delete(str);
  free(str);
  str_delete(&str2);
}

void test_clear()
{
  print_title("clear");

  str_t str;
  str_new(&str);

  str_cappend(&str, "Hello, World!", 13);
  print_str(&str);
  str_clear(&str);
  print_str(&str);

  assert(strcmp(str.str, "") == 0);
  assert(str.len == 0);
  assert(str.cap == 14);

  str_delete(&str);
}

void test_reserve()
{
  print_title("reserve");

  str_t str;
  str_new(&str);

  str_reserve(&str, 64);
  print_str(&str);

  assert(strcmp(str.str, "") == 0);
  assert(str.len == 0);
  assert(str.cap == 65);

  str_delete(&str);
}

void test_set()
{
  print_title("set");

  str_t str;
  str_new(&str);

  str_cappend(&str, "test", 4);
  str_cset(&str, "Hello, World!", 13);
  print_str(&str);

  assert(strcmp(str.str, "Hello, World!") == 0);
  assert(str.len == 13);
  assert(str.cap == 14);

  str_delete(&str);
}

void test_insert()
{
  print_title("insert");

  str_t *str = malloc(sizeof(str_t));
  str_new(str);

  str_cappend(str, "Hello, World!", 13);
  assert(str_insert(str, "Great Big ", 7, 10) == 0);
  print_str(str);

  assert(strcmp(str->str, "Hello, Great Big World!") == 0);
  assert(str->len == 23);
  assert(str->cap == 24);

  str_delete(str);
  free(str);
}

void test_resize()
{
  print_title("resize");

  str_t str;
  str_new(&str);

  str_cappend(&str, "Hello, World!", 13);
  print_str(&str);
  str_resize(&str, 5);
  print_str(&str);

  assert(strcmp(str.str, "Hello") == 0);
  assert(str.len == 5);
  assert(str.cap == 6);

  str_delete(&str);
}

void test_compare()
{
  print_title("compare");

  str_t str1;
  str_new(&str1);

  str_cappend(&str1, "Hello, World!", 13);
  print_str(&str1);

  str_t str2;
  str_new(&str2);

  str_cappend(&str2, "Hello, World!", 13);
  print_str(&str2);

  assert(str_compare(&str1, &str2) == 0);
  assert(str_ccompare(&str1, "Hello, World!", 13) == 0);

  str_insert(&str1, "Great Big ", 7, 10);
  print_str(&str1);
  print_str(&str2);
  assert(str_compare(&str1, &str2) != 0);
  assert(str_ccompare(&str1, "Hello, World!", 13) != 0);

  str_delete(&str1);
  str_delete(&str2);
}

void test_move()
{
  print_title("move");

  str_t str1;
  str_new(&str1);

  str_cappend(&str1, "Hello, World!", 13);
  print_str(&str1);

  str_t str2;
  str_new(&str2);

  str_cappend(&str2, "Tiny Elephants", 14);
  print_str(&str2);

  str_move(&str1, &str2);
  print_str(&str1);
  assert(strcmp(str1.str, "Tiny Elephants") == 0);

  str_delete(&str2);
}

void test_erase()
{
  print_title("erase");

  str_t str;
  str_new(&str);

  str_cappend(&str, "Hello, Great Big World!", 23);
  print_str(&str);
  str_erase(&str, 6, 10);
  print_str(&str);

  assert(strcmp(str.str, "Hello, World!") == 0);
  assert(str.len == 13);
  assert(str.cap == 24);

  str_delete(&str);
}

void test_escape()
{
  print_title("escape");

  str_t str;
  str_new(&str);

  char json[] = "{\"key\":\"value\n\"}";
  str_cappend(&str, json, strlen(json));
  print_str(&str);
  str_escape(&str);
  print_str(&str);

  assert(strcmp(str.str, "{\\\"key\\\":\\\"value\\n\\\"}") == 0);

  str_delete(&str);
}

int main()
{
  test_new();
  test_append();
  test_clear();
  test_reserve();
  test_set();
  test_insert();
  test_resize();
  test_compare();
  test_move();
  test_erase();
  test_escape();

  return 0;
}
