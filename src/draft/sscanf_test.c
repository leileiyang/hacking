#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256

struct GCodeLine {
  double x;
  double y;
  double f;
};

struct GCodeArc {
  int cw_ccw;
  double x;
  double y;
  double i;
  double j;
  double r;
  double f;
};

void ParseArguments(const char *content, double *arg1, const char *arg1_format,
                                         double *arg2, const char *arg2_format,
                                         double *arg3, const char *arg3_format) {

  char format[LINE_LENGTH] = {0};
  sprintf(format, "%s%s%s", arg1_format, arg2_format, arg3_format);
  int match_num = sscanf(content, format, arg1, arg2, arg3);
  if (match_num == 0) {
    memset(format, 0, LINE_LENGTH);
    sprintf(format, "%s%s", arg2_format, arg3_format);
    sscanf(content, format, arg2, arg3);
  } else if (match_num == 1) {
    memset(format, 0, LINE_LENGTH);
    sprintf(format, "%s%s", arg1_format, arg3_format);
    sscanf(content, format, arg1, arg3);
  }
}

void ParseLine(const char *content, struct GCodeLine *line) {
  ParseArguments(content, &line->x, "%*[ XU]%lf", &line->y, "%*[ YV]%lf",
      &line->f, "%*[ F]%lf");

}

void ParseArc(const char *content, struct GCodeArc *arc) {
}

// %*[ XU]%lf%*[ YV]%lf*[ F]%lf
// %*[ YV]%lf%*[ F]%lf


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

  const char *g_order = "G01Y3F500";
  double x, y;
  int cmd_index;
  char cmd_type;
  char content[256] = {0};
  //sscanf(g_order, "%c%d%*[ X]%d%*[ Y]%d", &cmd_type, &cmd_index, &x, &y);
  sscanf(g_order, "%c%d%255[^\001]", &cmd_type, &cmd_index, content);
  printf("cmd_type:%d cmd_index:%d, cmd_content:%s\n", cmd_type, cmd_index, content);
  int match_num = 0;
  double f = 0.0;
  struct GCodeLine line = {0, 0, 0};
  if (cmd_type == 'G' || cmd_type == 'g') {
    switch (cmd_index) {
      case 0:
      case 1:
        ParseLine(content, &line);
        break;
      case 2:
      case 3:
        
        break;
    }
  } else if (cmd_type == 'M' || cmd_type == 'm') {
    switch (cmd_index) {
      case 0:
      case 1:
      case 2:
        break;
    }
  } else if (cmd_type == 'N' || cmd_type == 'n') {
  } else {
  }
  return 0;
}
