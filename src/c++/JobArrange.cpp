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

struct Position {
  double x;
  double y;
};

class JobArrange {
 public:
  JobArrange(): fin_(NULL), fout_(NULL) {}
  virtual bool Arrange(const char* in_file, const char* out_file,
      std::vector<std::vector<int> > jobs) = 0;

 protected:
  FILE *fin_;
  FILE *fout_;

};

class LaserJob: public JobArrange {
 public:
  LaserJob(): mode_(UNPROCESS), mode_start_(-1), mode_end_(-1),
      cur_layer_(-1) {}

  virtual bool Arrange(const char* in_file, const char* out_file,
      std::vector<std::vector<int> > jobs);

 private:
  Position mode_pos_;
  Position cur_pos_;
  int mode_;
  int mode_start_;
  int mode_end_;
  int cur_layer_;

  void ModeLoop(int start, int end, int mode, int count);
  void ModeSwitch(const std::vector<int> &job);
  void ModeJump(int mode, const std::vector<int> &job);
  void JumpToModeStart();

  bool IsM07(char *buf);
  bool IsM08(char *buf);
  bool IsM02(char *buf);
  bool IsMCommand(char *buf, char c);
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

std::map<int, int> LaserJob::mode_layer = MakeModeLayerMap();


bool LaserJob::IsMCommand(char *buf, char c) {
  if (strlen(buf) < 3) {
    return false;
  }
  return buf[0] == 'M' && buf[1] == '0' && buf[2] == c;
}

bool LaserJob::IsM07(char *buf) {
  return IsMCommand(buf, '7');
}

bool LaserJob::IsM08(char *buf) {
  return IsMCommand(buf, '8');
}

bool LaserJob::IsM02(char *buf) {
  return IsMCommand(buf, '2');
}

void LaserJob::UpdatePos(char *buf) {
  // g command: G01 X5 Y10
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

int LaserJob::GetLayer(char *buf) {
  // m command: M07 U1
  char m[20] = {0};
  char u[20] = {0};
  sscanf(buf, "%s %s", m, u);
  return atoi(&u[1]);
}

void LaserJob::ModeLoop(int start, int end, int mode, int count) {
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

void LaserJob::ModeSwitch(const std::vector<int> &job) {
  switch (mode_) {
    case UNPROCESS:
      if (job[STRIPING]) {
        mode_ = STRIPING;
      } else if (job[PRE_PIERCE]) {
        mode_ = PRE_PIERCE;
      } else if (job[CUTTING]) {
        mode_ = CUTTING;
      } else if (job[COOLING]) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case STRIPING:
      if (job[PRE_PIERCE]) {
        mode_ = PRE_PIERCE;
      } else if (job[CUTTING]) {
        mode_ = CUTTING;
      } else if (job[COOLING]) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case PRE_PIERCE:
      if (job[CUTTING]) {
        mode_ = CUTTING;
      } else if (job[COOLING]) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case CUTTING:
      if (job[COOLING]) {
        mode_ = COOLING;
      } else {
        mode_ = UNPROCESS;
      }
      break;
    case COOLING:
      if (job[CUTTING]) {
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

void LaserJob::JumpToModeStart() {
  fseek(fin_, mode_start_, SEEK_SET);
  cur_pos_ = mode_pos_;
  mode_start_ = -1;
}

void LaserJob::ModeJump(int mode, const std::vector<int> &job) {
  if (mode == STRIPING) {
    if (job[PRE_PIERCE] || job[CUTTING] || job[COOLING]) {
      JumpToModeStart();
    } 
  } else if (mode == PRE_PIERCE) {
    if (job[CUTTING] || job[COOLING]) {
      JumpToModeStart();
    }
  } else if (mode == CUTTING) {
    if (job[COOLING]) {
      JumpToModeStart();
    }
  } else if (mode == COOLING) {
    mode_start_ = -1;
  }
}

bool LaserJob::Arrange(const char* in_file, const char* out_file,
    std::vector<std::vector<int> > jobs) {

  fin_ = fopen("demo.ngc", "r");
  fout_ = fopen("result2.ngc", "w");
  if (!fin_ || !fout_) {
    return false;
  }
  char line[256];
  while (fgets(line, 256, fin_)) {
    if (IsM07(line)) { // M07
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
        if (mode_ == STRIPING || mode_ == PRE_PIERCE) {
          if (GetLayer(line) != cur_layer_) {
            mode_end_ = ftell(fin_) - strlen(line);
            ModeLoop(mode_start_, mode_end_, mode_, jobs[cur_layer_][mode_]);
            ModeJump(mode_, jobs[cur_layer_]);
          }
        } else if (mode_ == CUTTING || mode_ == COOLING) {
          mode_end_ = ftell(fin_) - strlen(line);
          ModeLoop(mode_start_, mode_end_, mode_, jobs[cur_layer_][mode_]);
          ModeJump(mode_, jobs[cur_layer_]);
        }
      }
    } else if (IsM02(line)) {
      if (mode_start_ == -1) {
        fprintf(fout_, "%s", line);
      } else {
        mode_end_ = ftell(fin_) - strlen(line);
        ModeLoop(mode_start_, mode_end_, mode_, jobs[cur_layer_][mode_]);
        ModeJump(mode_, jobs[cur_layer_]);
      }
    }
    UpdatePos(line);
  }
}

int main () {
  LaserJob laser_job;
  std::vector<int> job(4, 1);
  job[2] = 2;
  std::vector<std::vector<int> >jobs;
  jobs.push_back(job);
  jobs.push_back(job);
  jobs.push_back(job);
  laser_job.Arrange("demo.ngc", "result2.ngc", jobs);
  return 0;
}
