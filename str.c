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
  if (str->str != NULL)
  {
    free(str->str);
  }
}

int str_set(str_t *str1, str_t *str2)
{
  if (str_clear(str1) == -1) return -1;
  if (str_append(str1, str2) == -1) return -1;
  return 0;
}

int str_move(str_t *str1, str_t *str2)
{
  if (str1->str != NULL)
  {
    free(str1->str);
  }
  str1->str = str2->str;
  str1->len = str2->len;
  str1->cap = str2->cap;
  return 0;
}

int str_reserve(str_t *str, int len)
{
  char *tmp = realloc(str->str, (sizeof(char) * (len + str->len + 1)));
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

  int count = 0;
  {
    char *dest = str1->str;
    char *s_ptr = str2->str;
    dest += str1->len;
    while ((*dest++ = *s_ptr++) && ++count < str2->len);
    *dest = '\0';
  }

  str1->len += str2->len;
  return count;
}

int str_insert(str_t *str, int i, char *s, int len)
{
  if (i < 0) return -1;
  if (i > str->len) return -1;
  if (i == 0)
  {
    str_t strf;
    if (str_new(&strf) == -1) return -1;
    if (str_reserve(&strf, str->len + len) == -1) return -1;
    if (str_cappend(&strf, s, len) == -1) return -1;
    if (str_cappend(&strf, str->str, str->len) == -1) return -1;
    if (str_move(str, &strf) == -1) return -1;
  }
  else if (i == str->len)
  {
    if (str_cappend(str, s, len) == -1) return -1;
  }
  else
  {
    str_t strf;
    if (str_new(&strf) == -1) return -1;
    if (str_reserve(&strf, str->len + len) == -1) return -1;

    int s_len = str->len;

    if (str_cappend(&strf, str->str, i) == -1) return -1;
    if (str_cappend(&strf, s, len) == -1) return -1;
    if (str_cappend(&strf, str->str + i, s_len - i) == -1) return -1;
    if (str_move(str, &strf) == -1) return -1;
  }

  return 0;
}

int str_compare(str_t *str1, str_t *str2)
{
  char *s1 = str1->str;
  char *s2 = str2->str;
  while (*s1 && (*s1++ == *s2++));
  return *s1 - *s2;
}

int str_resize(str_t *str, int len)
{
  if (len < 0) len = 0;
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
    str->str[str->len + 1] = '\0';
  }
  str->str[str->cap - 1] = '\0';
  return 0;
}

int str_erase(str_t *str, int index, int len)
{
  if (index < 0) return -1;
  if (index > str->len) return -1;
  if (index + len > str->len) return -1;

  int i = 0;
  char *s = str->str + index;
  char *p = str->str + index + len;
  while ((*s++ = *p++) && (++i < len));
  *s = '\0';
  str->len -= len;
  return i;
}

int str_clear(str_t *str)
{
  str->str[0] = '\0';
  str->len = 0;
  return 0;
}

int str_escape(str_t *str)
{
  str_t strf;
  if (str_new(&strf) == -1) return -1;
  if (str_reserve(&strf, str->len) == -1) return -1;
  char *tok = str->str;
  char *tok_start = tok;
  int count = 0;
  for (int i = 0; i <= str->len; ++i)
  {
    if (tok[i] == '\n')
    {
      if (str_cappend(&strf, tok_start, &tok[i] - tok_start) == -1) return -1;
      if (str_cappend(&strf, "\\n", 2) == -1) return -1;
      tok_start = &tok[i] + 1;
      ++count;
    }
    else if (tok[i] == '\t')
    {
      if (str_cappend(&strf, tok_start, &tok[i] - tok_start) == -1) return -1;
      if (str_cappend(&strf, "\\t", 2) == -1) return -1;
      tok_start = &tok[i] + 1;
      ++count;
    }
    else if (tok[i] == '\r')
    {
      if (str_cappend(&strf, tok_start, &tok[i] - tok_start) == -1) return -1;
      if (str_cappend(&strf, "\\r", 2) == -1) return -1;
      tok_start = &tok[i] + 1;
      ++count;
    }
    else if (tok[i] == '\'')
    {
      if (str_cappend(&strf, tok_start, &tok[i] - tok_start) == -1) return -1;
      if (str_cappend(&strf, "\\\'", 2) == -1) return -1;
      tok_start = &tok[i] + 1;
      ++count;
    }
    else if (tok[i] == '\"')
    {
      if (str_cappend(&strf, tok_start, &tok[i] - tok_start) == -1) return -1;
      if (str_cappend(&strf, "\\\"", 2) == -1) return -1;
      tok_start = &tok[i] + 1;
      ++count;
    }
    else if (tok[i] == '\0')
    {
      if (str_cappend(&strf, tok_start, &tok[i] - tok_start) == -1) return -1;
    }
  }
  if (str_move(str, &strf) == -1) return -1;
  return count;
}

int str_cset(str_t *str, char *s, int len)
{
  if (str_clear(str) == -1) return -1;
  if (str_cappend(str, s, len) == -1) return -1;
  return 0;
}

int str_cappend(str_t *str, char *s, int len)
{
  int s_len = 0;
  {
    char *p = s;
    while (*p && s_len < len)
    {
      p++;
      s_len++;
    }
  }

  if (s_len < len) len = s_len;
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

  int count = 0;
  {
    char *dest = str->str;
    char *s_ptr = s;
    dest += str->len;
    while ((*dest++ = *s_ptr++) && ++count < len);
    *dest = '\0';
  }

  str->len += len;
  return count;
}

int str_ccompare(str_t *str, char *s, int len)
{
  int count = 0;
  char *s1 = str->str;
  char *s2 = s;
  while (*s1 && (*s1++ == *s2++) && (++count < len));
  return *s1 - *s2;
}
