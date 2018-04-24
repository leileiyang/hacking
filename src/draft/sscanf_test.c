#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char *m_order = "nc_subroutines/M107 P0.111 Q9.111";
  const char *m_order_no_args = "M107 (101)";
  char m_buf[30] = {0};
  char p_buf[30] = {0};
  char q_buf[30] = {0};

  //sscanf(m_order, "%s %s %s", m_buf, p_buf, q_buf);
  sscanf(m_order, "%s", m_buf);
  printf("m:%s p:%f q:%f\n", m_buf, atof(&p_buf[1]), atof(&q_buf[1]));

  memset(m_buf, 0, 10);
  memset(p_buf, 0, 30);
  memset(q_buf, 0, 30);
  char c;
  int index;
  //sscanf(m_order_no_args, "%c%d %s %s", &c, &index, p_buf, q_buf);
  //sscanf(m_order_no_args, "%*[M]%d %s %s", &index, p_buf, q_buf);
  char a;
  char b;
  int value;
  sscanf(m_order_no_args, "M%d (%d) %s", &index, &value, p_buf);
  //printf("m:%d p:%f q:%f\n", index, atof(&p_buf[1]), atof(&q_buf[1]));
  printf("m:%d p:%d\n", index, value);
}
