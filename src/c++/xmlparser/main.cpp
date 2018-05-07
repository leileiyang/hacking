#include "LaserXmlParser.h"

#include "PlcCfg.h"

int main() {
  LaserXmlParser xml_parser;
  if (!xml_parser.ParseXml("laser_param.xml")) {
    return -1;
  }
  pugi::xpath_node_set nodes = xml_parser.LayerNodes();
  if (!nodes.empty()) {
    xml_parser.LayerNodesComplement(nodes);
    if (nodes.size() == CRAFT_LAYERS) {
      ;
    } else {
      int n = CRAFT_LAYERS - nodes.size();
      xml_parser.AddLayerNodes(n);
    }
  } else {
    xml_parser.AddLayerNodes(CRAFT_LAYERS);
  }
  if (xml_parser.doc_.save_file("laser_param.xml")) {
    return 0;
  }
  return -1;
}
