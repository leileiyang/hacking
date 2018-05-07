#include "LaserXmlParser.h"

#include "PlcCfg.h"

bool LaserXmlParser::AddLayerNodes(int num) {
  pugi::xml_node parent_node = FindNodeByPath("LaserParam/PlcParam");
  if (!parent_node) {
    return false;
  }
  for (int i = 0; i < num; i++) {
    pugi::xml_node node = parent_node.append_child("Layer");
    AddLayerContents(node);
  }
  return true;
}

bool LaserXmlParser::AddLayerContents(pugi::xml_node layer_node) {
  AddProcessCfgNode(layer_node);
  AddCraftDataNodes(CRAFT_LEVELS, layer_node);
}

bool LaserXmlParser::AddProcessCfgNode(pugi::xml_node parent_node) {
  if (!parent_node) {
    return false;
  }
  pugi::xml_node node = parent_node.append_child("ProcessCfg");
  AddProcessCfgAttributes(node);
  return true;
}

bool LaserXmlParser::AddProcessCfgAttributes(pugi::xml_node processcfg_node) {
  processcfg_node.append_attribute("no_lift") = "false";
  processcfg_node.append_attribute("pre_pierce") = "false";
  processcfg_node.append_attribute("striping") = "false";
  processcfg_node.append_attribute("cooling") = "false";
  processcfg_node.append_attribute("cutting") = 0;
  processcfg_node.append_attribute("no_follow") = "false";
  processcfg_node.append_attribute("keep_air") = "false";
  processcfg_node.append_attribute("skip") = "false";
  processcfg_node.append_attribute("craft_level") = 0;
}

bool LaserXmlParser::AddCraftDataNodes(int num, pugi::xml_node parent_node) {
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

void LaserXmlParser::LayerNodeComplement(pugi::xml_node layer_node) {
  pugi::xml_node processcfg_node = layer_node.child("ProcessCfg");
  if (processcfg_node) {
    ProcessCfgAttributesComplement(processcfg_node);
  } else {
    AddProcessCfgNode(layer_node);
  }
  pugi::xml_node craftdata_node = layer_node.child("CraftData");
  if (!craftdata_node) {
    AddCraftDataNodes(CRAFT_LEVELS, layer_node);
  } else {
    int n = 0;
    for (pugi::xml_node node = craftdata_node; node;
        node = node.next_sibling("CraftData")) {
      
      CraftDataAttributesComplement(node);
      n++;
    }
    AddCraftDataNodes(CRAFT_LEVELS-n, layer_node);
  }
}

void LaserXmlParser::LayerNodesComplement(\
    pugi::xpath_node_set layer_nodes) {

  for (int i = 0; i < layer_nodes.size(); i++) {
    LayerNodeComplement(layer_nodes[i].node());
  }
}

void LaserXmlParser::CraftDataAttributesComplement(\
    pugi::xpath_node_set craftdata_nodes) {

  for (int i = 0; i < craftdata_nodes.size(); i++) {
    CraftDataAttributesComplement(craftdata_nodes[i].node());
  }
}

#define AddIfNotExist(NAME, VALUE) do { \
  attr = node.attribute(NAME); \
  if (!attr) { \
    node.append_attribute(NAME) = VALUE; \
  } \
} while (0)

void LaserXmlParser::ProcessCfgAttributesComplement(\
    pugi::xml_node node) {

  pugi::xml_attribute attr = pugi::xml_attribute();
  AddIfNotExist("no_lift", "false");
  AddIfNotExist("pre_pierce", "false");
  AddIfNotExist("striping", "false");
  AddIfNotExist("cooling", "false");
  AddIfNotExist("cutting", 0);
  AddIfNotExist("no_follow", "false");
  AddIfNotExist("keep_air", "false");
  AddIfNotExist("skip", "false");
  AddIfNotExist("craft_level", 0);
}

void LaserXmlParser::CraftDataAttributesComplement(\
    pugi::xml_node node) {

  pugi::xml_attribute attr = pugi::xml_attribute();
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

pugi::xpath_node_set LaserXmlParser::LayerNodes() {
  return SelectNodes("LaserParam/PlcParam/Layer");
}
