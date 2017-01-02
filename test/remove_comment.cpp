#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

#define BUFSIZE (1024*100)/*UL*/
// this solution is not completely right
void remove_comment(char* buf, size_t size) {
  char *p, *end, c;
  char *sq_start, *dq_start;
  char *lc_start, *bc_start;
  size_t len;
  p = buf;
  end = p + size;
  sq_start = NULL;
  dq_start = NULL;
  lc_start = NULL;
  bc_start = NULL;

  while (p < end) {
    c = *p;
    switch(c) {
    case '\'':
      if (dq_start || lc_start || bc_start) {
        p++;
        continue;
      }
      if (sq_start = NULL) {
        sq_start = p++;
      } else {
        len = p++ - sq_start;
        if (len == 2 && *(sq_start + 1) == '\\')
          continue;
        sq_start = NULL;
      }
      break;
    case '\"':
      if (sq_start || lc_start || bc_start) {
        p++;
        continue;
      }
      if (dq_start == NULL) {
        dq_start = p++;
      } else {
        if (*(p++ - 1) == '\\')
          continue;
        dq_start = NULL;
      }
      break;
    case '/':
      if (sq_start || dq_start || lc_start || bc_start) {
        p++;
        continue;
      }
      c = *(p+1);
      if (c == '/') {
        lc_start = p;
        p += 2;
      } else if (c == '*') {
        bc_start = p;
        p += 2;
      } else {
        p++;
      }
      break;
    case '*':
      if (sq_start || dq_start || lc_start || bc_start == NULL) {
        p++;
        continue;
      }
      if (*(p+1) != '/') {
        p++;
        continue;
      }
      p += 2;
      memset(bc_start, ' ', p - bc_start);
      bc_start = NULL;
      break;
    case '\n':
      if (lc_start == NULL) {
        p++;
        continue;
      }
      c = *(p - 1);
      memset(lc_start, ' ', (c == '\r' ? (p++ - 1) : p++) - lc_start);
      lc_start = NULL;
      break;
    default:
      p++;
      break;
    }
  }
  if (lc_start) {
    memset(lc_start, ' ', p - lc_start);
  }
}

int main(int argc, char* argv[])
{
  int fd, n;
  char buf[BUFSIZE];
  fd = open("uuu.txt", O_RDONLY, 0);
  if (fd == -1) {
    return -1;
  }
  n = read(fd, buf, sizeof(buf));
  if (n == -1 || n == 0) {
    close(fd);
    return -1;
  }
  printf(buf);
  printf("=========\n");
  remove_comment(buf, n);
  *(buf+n) = '\0';
  printf(buf);
  close(fd);

  return 0;
}
