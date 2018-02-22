//
// MIT License
//
// Copyright (c) 2018 Brett Robinson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "str.h"

#include <stdlib.h>

int str_new(str_t *str)
{
  char *tmp = malloc(sizeof(char) * 1);
  if (tmp == NULL)
  {
    return -1;
  }
  str->str = tmp;
  str->str[0] = '\0';
  str->len = 0;
  str->cap = 1;
  return 0;
}

void str_delete(str_t *str)
{
  free(str->str);
}

int str_set(str_t *str1, str_t *str2)
{
  if (str_clear(str1) == -1) return -1;
  if (str_append(str1, str2) == -1) return -1;
  return 0;
}

int str_move(str_t *str1, str_t *str2)
{
  str_delete(str1);
  *str1 = *str2;
  return 0;
}

int str_reserve(str_t *str, size_t len)
{
  char *tmp = realloc(str->str, sizeof(char) * (len + str->len + 1));
  if (tmp == NULL)
  {
    return -1;
  }
  str->str = tmp;
  str->cap = len + str->len + 1;
  return str->cap;
}

int str_append(str_t *str1, str_t *str2)
{
  if (str1->len + str2->len + 1 > str1->cap)
  {
    char *tmp = realloc(str1->str, sizeof(char) * (str1->len + str2->len + 1));
    if (tmp == NULL)
    {
      return -1;
    }
    str1->str = tmp;
    str1->cap = str1->len + str2->len + 1;
  }

  char *dest = str1->str;
  char *s_ptr = str2->str;
  dest += str1->len;
  while ((*dest++ = *s_ptr++));

  str1->len += str2->len;
  return 0;
}

int str_insert(str_t *str, char *s, size_t i, size_t len)
{
  if (i >= str->len) return -1;

  str_t strf;
  if (i == 0)
  {
    if (str_new(&strf) == -1) goto err;
    if (str_reserve(&strf, str->len + len) == -1) goto err;

    if (str_cappend(&strf, s, len) == -1) goto err;
    if (str_cappend(&strf, str->str, str->len) == -1) goto err;

    if (str_move(str, &strf) == -1) goto err;
  }
  else if (i == str->len)
  {
    if (str_cappend(str, s, len) == -1) return -1;
  }
  else
  {
    if (str_new(&strf) == -1) goto err;
    if (str_reserve(&strf, str->len + len) == -1) goto err;

    if (str_cappend(&strf, str->str, i) == -1) goto err;
    if (str_cappend(&strf, s, len) == -1) goto err;
    if (str_cappend(&strf, str->str + i, str->len - i) == -1) goto err;

    if (str_move(str, &strf) == -1) goto err;
  }

  return 0;

err:
  str_delete(&strf);
  return -1;
}

int str_compare(str_t *str1, str_t *str2)
{
  char *s1 = str1->str;
  char *s2 = str2->str;
  while (*s1 && (*s1 == *s2))
  {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int str_resize(str_t *str, size_t len)
{
  char *tmp = realloc(str->str, (sizeof(char) * (len + 1)));
  if (tmp == NULL)
  {
    return -1;
  }
  str->str = tmp;
  str->cap = len + 1;
  if (str->len > len)
  {
    str->len = len;
    str->str[str->len] = '\0';
  }
  str->str[str->cap - 1] = '\0';
  return 0;
}

int str_erase(str_t *str, size_t index, size_t len)
{
  if (index > str->len) return -1;
  if (index + len > str->len) return -1;

  char *s = str->str + index;
  char *p = str->str + index + len;
  while ((*s++ = *p++));
  str->len -= len;
  return str->len;
}

int str_clear(str_t *str)
{
  *str->str = '\0';
  str->len = 0;
  return 0;
}

int str_escape(str_t *str)
{
  str_t tmp;
  if (str_new(&tmp) == -1) goto err;
  if (str_reserve(&tmp, str->len + 64) == -1) goto err;

  char *tok = str->str;
  char *tok_start = str->str;
  int count = 0;

  for (size_t i = 0; i <= str->len; ++i)
  {
    switch(tok[i])
    {
    case '\n':
      if (str_cappend(&tmp, tok_start, &tok[i] - tok_start) == -1) goto err;
      if (str_cappend(&tmp, "\\n", 2) == -1) goto err;
      tok_start = &tok[i] + 1;
      ++count;
      break;

    case '\t':
      if (str_cappend(&tmp, tok_start, &tok[i] - tok_start) == -1) goto err;
      if (str_cappend(&tmp, "\\t", 2) == -1) goto err;
      tok_start = &tok[i] + 1;
      ++count;
      break;

    case '\r':
      if (str_cappend(&tmp, tok_start, &tok[i] - tok_start) == -1) goto err;
      if (str_cappend(&tmp, "\\r", 2) == -1) goto err;
      tok_start = &tok[i] + 1;
      ++count;
      break;

    case '\'':
      if (str_cappend(&tmp, tok_start, &tok[i] - tok_start) == -1) goto err;
      if (str_cappend(&tmp, "\\\'", 2) == -1) goto err;
      tok_start = &tok[i] + 1;
      ++count;
      break;

    case '\"':
      if (str_cappend(&tmp, tok_start, &tok[i] - tok_start) == -1) goto err;
      if (str_cappend(&tmp, "\\\"", 2) == -1) goto err;
      tok_start = &tok[i] + 1;
      ++count;
      break;

    case '\0':
      if (str_cappend(&tmp, tok_start, 1) == -1) goto err;
      break;

    default:
      break;
    }
  }

  if (str_move(str, &tmp) == -1) goto err;
  return count;

  err:
    str_delete(&tmp);
    return -1;
}

int str_cset(str_t *str, char *s, size_t len)
{
  if (str_clear(str) == -1) return -1;
  if (str_cappend(str, s, len) == -1) return -1;
  return 0;
}

int str_cappend(str_t *str, char *s, size_t len)
{
  size_t s_len = 0;
  {
    char *p = s;
    while (*p)
    {
      p++;
      s_len++;
    }
  }
  if (s_len < len) return -1;

  if (str->len + len + 1 > str->cap)
  {
    char *tmp = realloc(str->str, sizeof(char) * (str->len + len + 1));
    if (tmp == NULL)
    {
      return -1;
    }
    str->str = tmp;
    str->cap = str->len + len + 1;
  }

  size_t count = 0;
  {
    char *dest = str->str;
    char *s_ptr = s;
    dest += str->len;
    while ((count < len) && (*dest = *s_ptr))
    {
      dest++;
      s_ptr++;
      count++;
    }
  }

  str->len += len;
  str->str[str->len] = '\0';

  return 0;
}

int str_ccompare(str_t *str, char *s, size_t len)
{
  size_t count = 0;
  char *s1 = str->str;
  char *s2 = s;
  while (*s1 && (*s1 == *s2) && (++count < len))
  {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}
