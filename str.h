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

#ifndef STR_H
#define STR_H

// str object
typedef struct str_t
{
  char *str; // string
  int len; // length
  int cap; // capacity
} str_t;

// str new
int str_new(str_t *str);

// str delete
void str_delete(str_t *str);

// str functions
int str_set(str_t *str1, str_t *str2);
int str_move(str_t *str1, str_t *str2);
int str_reserve(str_t *str, int len);
int str_append(str_t *str1, str_t *str2);
int str_insert(str_t *str, int i, char *s, int len);
int str_compare(str_t *str1, str_t *str2);
int str_resize(str_t *str, int len);
int str_erase(str_t *str, int index, int len);
int str_clear(str_t *str);
int str_escape(str_t *str);

// str c functions
int str_cset(str_t *str, char *s, int len);
int str_cappend(str_t *str, char *s, int len);
int str_ccompare(str_t *str, char *s, int len);

#endif
