#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <vector>
#include <map>

enum JOB_MODE {
  UNPROCESS = -1,
  STRIPING = 0,
  PRE_PIERCE = 1,
  CUTTING = 2,
  COOLING = 3,
};

struct LayerJobs {
  int striping;
  int prepierce;
  int cutting;
  int cooling;
};

struct Position {
  double x;
  double y;
};

class JobParser {
 public:
  virtual bool Parse(const char* in_file, const char* out_file,
      std::vector<LayerJobs> jobs) = 0;

 protected:
  FILE *fin_;
  FILE *fout_;

};

class LaserJobParser: public JobParser {
 public:
  virtual bool Parse(const char* in_file, const char* out_file,
      std::vector<LayerJobs> jobs);

 private:
  Position mode_pos_;
  Position cur_pos_;
  int mode_;
  int mode_start_;
  int mode_end_;
  int cur_layer_;

  void ModeLoop(int start, int end, int mode, int count);
  void ModeSwitch(const LayerJobs &jobs);
  void ModeJump(int mode, const LayerJobs &jobs);

  bool IsM07(char *buf);
  bool IsM08(char *buf);
  void UpdatePos(char *buf);
  int GetLayer(char *buf);

  static std::map<int, int> mode_layer;
  static std::map<int, int> MakeModeLayerMap() {
    static std::map<int, int> temp;
    temp[STRIPING] = 19;
    temp[COOLING] = 20;
    return temp;
  }

};

std::map<int, int> LaserJobParser::mode_layer = MakeModeLayerMap();


bool LaserJobParser::IsM07(char *buf) {
  if (strlen(buf) < 3) {
    return false;
  }
  return buf[0] == 'M' && buf[1] == '0' && buf[2] == '7';
}

bool LaserJobParser::IsM08(char *buf) {
  if (strlen(buf) < 3) {
    return false;
  }
  return buf[0] == 'M' && buf[1] == '0' && buf[2] == '8';
}

void LaserJobParser::UpdatePos(char *buf) {
  char g[20] = {0};
  char x[20] = {0};
  char y[20] = {0};
  sscanf(buf, "%s %s %s", g, x, y);
  int g_type = atoi(&g[1]);
  if (g_type == 0 || g_type == 1 || g_type == 2 || g_type == 3) {
    cur_pos_.x = atof(&x[1]);
    cur_pos_.y = atof(&y[1]);
  }
}

int LaserJobParser::GetLayer(char *buf) {
  char m[20] = {0};
  char u[20] = {0};
  sscanf(buf, "%s %s", m, u);
  return atoi(&u[1]);
}

void LaserJobParser::ModeLoop(int start, int end, int mode, int count) {
  char buf[256];
  for (int i = 0; i < count; i++) {
    if (mode != PRE_PIERCE) { // striping, cutting, cooling 
      fseek(fin_, start, SEEK_SET);
      fprintf(fout_, "G00 X%.4f Y%.4f\n", mode_pos_.x, mode_pos_.y);
      while (ftell(fin_) != end) {
        memset(buf, 0, 256);
        fgets(buf, 256, fin_);
        if (IsM07(buf)) { // M07
          fprintf(fout_, "M00\n");
          if (mode == STRIPING || mode == COOLING) {
            fprintf(fout_, "M07 U%d\n", mode_layer[mode]);
          } else {
            fprintf(fout_, "%s", buf);
          }
        } else if (IsM08(buf)) { // M08
          fprintf(fout_, "M00\n");
          fprintf(fout_, "%s", buf);
        } else {
          fprintf(fout_, "%s", buf);
        }
      }
    } else { // pre-pierce
      fseek(fin_, start, SEEK_SET);
      cur_pos_ = mode_pos_;
      while (ftell(fin_) != end) {
        memset(buf, 0, 256);
        fgets(buf, 256, fin_);
        if (IsM07(buf)) { // M07
          fprintf(fout_, "G00 X%.4f Y%.4f\n", cur_pos_.x, cur_pos_.y);
          fprintf(fout_, "M00\n");
          fprintf(fout_, "%s", buf);
        } else if (IsM08(buf)) { // M08
          fprintf(fout_, "M00\n");
          fprintf(fout_, "%s", buf);
        } else {
          UpdatePos(buf);
        }
      }
    }
  }
}

void LaserJobParser::ModeSwitch(const LayerJobs &jobs) {
  switch (mode_) {
    case UNPROCESS:
      if (jobs.striping) {
        mode_ = STRIPING;
      } else if (jobs.prepierce) {
        mode_ = PRE_PIERCE;
      } else if (jobs.cutting) {
        mode_ = CUTTING;
      } else if (jobs.cooling) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case STRIPING:
      if (jobs.prepierce) {
        mode_ = PRE_PIERCE;
      } else if (jobs.cutting) {
        mode_ = CUTTING;
      } else if (jobs.cooling) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case PRE_PIERCE:
      if (jobs.cutting) {
        mode_ = CUTTING;
      } else if (jobs.cooling) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case CUTTING:
      if (jobs.cooling) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case COOLING:
      if (jobs.cutting) {
        mode_ = CUTTING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    default:
      mode_ = UNPROCESS;
      break;
  }
}

void LaserJobParser::ModeJump(int mode, const LayerJobs &jobs) {
  if (mode == STRIPING) {
    if (jobs.prepierce || jobs.cutting || jobs.cooling) {
      fseek(fin_, mode_start_, SEEK_SET);
      cur_pos_ = mode_pos_;
      mode_start_ = -1;
    } 
  } else if (mode == PRE_PIERCE) {
    if (jobs.cutting || jobs.cooling) {
      fseek(fin_, mode_start_, SEEK_SET);
      cur_pos_ = mode_pos_;
      mode_start_ = -1;
    }
  } else if (mode == CUTTING) {
    if (jobs.cooling) {
      fseek(fin_, mode_start_, SEEK_SET);
      cur_pos_ = mode_pos_;
      mode_start_ = -1;
    }
  } else if (mode == COOLING) {
    mode_start_ = -1;
  }
}

bool LaserJobParser::Parse(const char* in_file, const char* out_file,
    std::vector<LayerJobs> jobs) {

  fin_ = fopen("demo.ngc", "r");
  fout_ = fopen("result2.ngc", "w");
  if (!fin_ || !fout_) {
    return false;
  }
  char line[256];
  while (fgets(line, 256, fin_)) {
    if (IsM07(line)) {
      if (mode_start_ == -1) {
        mode_pos_ = cur_pos_;
        mode_start_ = ftell(fin_) - strlen(line);
        int layer = GetLayer(line);
        if (layer != cur_layer_) {
          cur_layer_ = layer;
          mode_ = UNPROCESS;
        }
        ModeSwitch(jobs[cur_layer_]);
      } else {
        if (mode_ == STRIPING) {
          if (GetLayer(line) != cur_layer_) {
            mode_end_ = ftell(fin_) - strlen(line);
            ModeLoop(mode_start_, mode_end_, mode_, jobs[cur_layer_].
          }
        }
      }
    }
  }
}
