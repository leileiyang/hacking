#include "LaserXmlParser.h"

bool LaserXmlParser::AddCraftDataNodes(int num) {
  pugi::xml_node parent_node = FindNodeByPath("LaserParam/PlcParam");
  if (!parent_node) {
    return false;
  }
  for (int i = 0; i < num; i++) {
    pugi::xml_node node = parent_node.append_child("CraftData");
    AddCraftDataAttributes(node);
  }
  return true;
}

bool LaserXmlParser::AddCraftDataAttributes(pugi::xml_node craftdata_node) {
  craftdata_node.append_attribute("enable_incr") = "false";
  craftdata_node.append_attribute("incr_time") = 300;
  craftdata_node.append_attribute("lift") = 10;
  craftdata_node.append_attribute("gas") = 0;
  craftdata_node.append_attribute("pressure") = 10;
  craftdata_node.append_attribute("power") = 1;
  craftdata_node.append_attribute("ratio") = 1;
  craftdata_node.append_attribute("frequency") = 50;
  craftdata_node.append_attribute("focus") = 3;
  craftdata_node.append_attribute("stay") = 3000;
  craftdata_node.append_attribute("enable_blow") = "false";
  craftdata_node.append_attribute("blow_time") = 3000;
  return true;
}


void LaserXmlParser::CraftDataAttributesComplement(\
    pugi::xpath_node_set craftdata_nodes) {

  for (int i = 0; i < craftdata_nodes.size(); i++) {
    CraftDataAttributesComplement(craftdata_nodes[i].node());
  }
}

void LaserXmlParser::CraftDataAttributesComplement(
    pugi::xml_node craftdata_node) {

  pugi::xml_attribute attr = pugi::xml_attribute();

#define AddIfNotExist(NAME, VALUE) do { \
  attr = craftdata_node.attribute(NAME); \
  if (!attr) { \
    craftdata_node.append_attribute(NAME) = VALUE; \
  } \
} while (0)

  AddIfNotExist("enable_incr", "false");
  AddIfNotExist("incr_time", 300);
  AddIfNotExist("lift", 10);
  AddIfNotExist("gas", 0);
  AddIfNotExist("pressure", 10);
  AddIfNotExist("power", 1);
  AddIfNotExist("ratio", 1);
  AddIfNotExist("frequency", 50);
  AddIfNotExist("focus", 3);
  AddIfNotExist("stay", 3000);
  AddIfNotExist("enable_blow", "false");
  AddIfNotExist("blow_time", 3000);
}


pugi::xpath_node_set LaserXmlParser::CraftDataNodes() {
  return SelectNodes("LaserParam/PlcParam/CraftData");
}
