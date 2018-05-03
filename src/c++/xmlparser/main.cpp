#include "LaserXmlParser.h"

int main() {
  LaserXmlParser xml_parser;
  if (!xml_parser.ParseXml("laser_param.xml")) {
    return -1;
  }
  pugi::xpath_node_set nodes = xml_parser.CraftDataNodes();
  if (!nodes.empty()) {
    xml_parser.CraftDataAttributesComplement(nodes);
    if (nodes.size() == 4) {
      ;
    } else {
      int n = 4 - nodes.size();
      xml_parser.AddCraftDataNodes(n);
    }
  } else {
    xml_parser.AddCraftDataNodes(4);
  }
  if (xml_parser.doc_.save_file("laser_param.xml")) {
    return 0;
  }
  return -1;
}
