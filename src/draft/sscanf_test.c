#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char *m_order = "nc_subroutines/M107 P0.111 Q9.111";
  const char *m_order_no_args = "M107";
  char m_buf[30] = {0};
  char p_buf[30] = {0};
  char q_buf[30] = {0};

  //sscanf(m_order, "%s %s %s", m_buf, p_buf, q_buf);
  sscanf(m_order, "%s", m_buf);
  printf("m:%s p:%f q:%f\n", m_buf, atof(&p_buf[1]), atof(&q_buf[1]));

  memset(m_buf, 0, 10);
  memset(p_buf, 0, 30);
  memset(q_buf, 0, 30);
  int index;
  sscanf(m_order_no_args, "%*[M]%d %s %s", &index, p_buf, q_buf);
  printf("m:%d p:%f q:%f\n", index, atof(&p_buf[1]), atof(&q_buf[1]));
}
