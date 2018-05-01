#include "XmlParser.h"

int main() {
  XmlParser xml_parser;
  if (!xml_parser.ParseXml("laser_param.xml")) {
    return -1;
  }
  pugi::xml_node node = xml_parser.doc_.child("LaserParam").child("PlcParam").child("CraftData");
  node.append_attribute("enable_incr") = "true";
  node.append_attribute("incr_time") = "300";
  node.append_attribute("lift") = "10";
  node.append_attribute("gas") = "0";
  node.append_attribute("pressure") = "10";
  node.append_attribute("power") = "1";
  node.append_attribute("ratio") = "1";
  node.append_attribute("frequency") = "50";
  node.append_attribute("stay") = "3000";
  node.append_attribute("enable_blow") = "false";
  node.append_attribute("blow_time") = "3000";
  if (xml_parser.doc_.save_file("laser_param.xml")) {
    return 0;
  }
  //pugi::xml_node node1 = node.child("PlcParam");
  return -1;
}
