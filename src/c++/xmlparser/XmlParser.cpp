#include "XmlParser.h"

bool XmlParser::ParseXml(const char *file) {
  if (doc_.load_file(file)) {
    return true;
  } else {
    return false;
  }
}
