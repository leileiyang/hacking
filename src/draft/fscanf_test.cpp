#include <stdio.h>
#include <string.h>

typedef enum _CardType {
  HARD_INFO_DEMO,
  HARD_INFO_PRU,
  HARD_INFO_FPGA,
} CardType;

typedef enum _AxisControlType {
  PULSE_MOTION_CARD,
  ANALOG_CLOSED_LOOP_MOTION_CARD,
} AxisControlType;

typedef struct _CardHardInfo {
  CardType stepgen_type_;
  int axis_count_;
  AxisControlType axis_control_type_;
  int encoder_count_;
  int input_count_;
  int output_count_;
  int ad_count_;
  int da_count_;
} CardHardInfo;

void ParseCardInfo(const char *key, const char *value, CardHardInfo &card) {
  if (strcmp(key,"ONECUT_STEPGEN_TYPE") == 0) {
    // Stepgen type.
    CardType stepgen_type = HARD_INFO_DEMO;
    if (strcmp("HARD_INFO_DEMO", value) == 0) {
      stepgen_type = HARD_INFO_DEMO;
    } else if (strcmp("HARD_INFO_PRU", value) == 0) {
      stepgen_type = HARD_INFO_PRU;
    } else if (strcmp("HARD_INFO_FPGA", value) == 0) {
      stepgen_type = HARD_INFO_FPGA;
    }
    card.stepgen_type_ = stepgen_type;
  } else if (strcmp(key, "ONECUT_AXIS_COUNT") == 0) {
    sscanf(value, "%d", &card.axis_count_);
  } else if (strcmp(key, "ONECUT_AXIS_CONTROL_TYPE") == 0) {
    AxisControlType axis_control_type = PULSE_MOTION_CARD;
    if (strcmp("PULSE_MOTTION_CARD", value) == 0) {
      axis_control_type = PULSE_MOTION_CARD;
    } else if (strcmp("ANALOG_CLOSED_LOOP_MOTION_CARD", value) == 0) {
      axis_control_type = ANALOG_CLOSED_LOOP_MOTION_CARD;
    }
    card.axis_control_type_ = axis_control_type;
  } else if (strcmp(key, "ONECUT_ENCODER_COUNT") == 0) {
    sscanf(value, "%d", &card.encoder_count_);
  } else if (strcmp(key, "ONECUT_INPUT_COUNT") == 0) {
    sscanf(value, "%d", &card.input_count_);
  } else if (strcmp(key, "ONECUT_OUTPUT_COUNT") == 0) {
    sscanf(value, "%d", &card.output_count_);
  } else if (strcmp(key, "ONECUT_AD_COUNT") == 0) {
    sscanf(value, "%d", &card.ad_count_);
  } else if (strcmp(key, "ONECUT_DA_COUNT") == 0) {
    sscanf(value, "%d", &card.da_count_);
  }
}

int main() {
  char value[30] = {0};
  char key[30] = {0};
  CardHardInfo card_hard_info;
  FILE *fp = fopen("/home/debian/fangling/mk/HardInfo.info", "r");
  if (fp) {
    while (fscanf(fp, "%[^=]=%s ", key, value) != EOF) {
      ParseCardInfo(key, value, card_hard_info);
      memset(value, 0, 30);
      memset(key, 0, 30);
    }
    fclose(fp);
  }
  return 0;
}
