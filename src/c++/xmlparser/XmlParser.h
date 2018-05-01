#ifndef XMLPARSER_XMLPARSER_H_ 
#define XMLPARSER_XMLPARSER_H_ 

#include "pugixml.hpp"

struct CraftData {
  bool enable_incr;
  double incr_time;
  int gas;
  double pressure;
  double height;
  double power;
  double ratio;
  double frequency;
  double focus;
  double stay;
  bool enable_blow;
  bool blow_time;
};

class XmlParser {
 public:
  bool ParseXml(const char* file);

  pugi::xml_document doc_;

};

#endif // XMLPARSER_XMLPARSER_H_ 
