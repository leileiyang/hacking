#include <iostream>
#include <string>

#define str(s) #s
#define xstr(s) str(s)
#define foo 4

#define OUTPUT_FIRE_SWITCH 4
#define OUTPUT_FIRE_SWITCH_STR "fire_switch"

struct IODefine {
  std::string name_;
  std::string display_;
  bool units_;
  bool press_;
  int number_;
  std::string address_;
};

#define GENERATE_IODEFINE(io_def, title, units, press, address) \
  define.name_ = io_def##_STR; \
  define.display_ = title; \
  define.units_ = units; \
  define.press_ = press; \
  define.number_ = io_def; \
  define.address_ = address

#define FUNC_DEF(func_name) void on##func_name(int a)
#define FUNC_IMP(class_name, func_name)  void class_name:: on##func_name(int a) { \
  std::cout << a << std::endl; }

class A {
 private:
  int a;
 public:
  FUNC_DEF(Display);
};

class OxyController {
public:
  int a;
};

class NotifyItem {
public:
  explicit NotifyItem(OxyController &mot) {}
  int a;
};

#define NOTIFY_CLASS(NAME) \
class NAME: public NotifyItem{\
 public: \
  explicit NAME(OxyController &mot_ctrl): \
      NotifyItem(mot_ctrl) {} \
\
  virtual ~NAME() {} \
  bool virtual CheckModified(); \
  void virtual NAMESync(); \
  void virtual NAME##Sync(); \
}

int main() {
  //printf(str(p = "foo\n";));
  //printf(str(\n));
  //printf(str(foo));
  //printf(xstr(foo));
  //printf(str(\n));
  IODefine define;
  GENERATE_IODEFINE(OUTPUT_FIRE_SWITCH, "Ignition", \
      true, false, "fire_display_time");

  //std::cout << define.name_ << std::endl;
  //std::cout << define.display_<< std::endl;
  //std::cout << define.units_ << std::endl;
  //std::cout << define.press_ << std::endl;
  //std::cout << define.number_ << std::endl;
  //std::cout << define.address_ << std::endl;
  NOTIFY_CLASS(NotifyLocateLimitSpeed);

  return 0;
}
