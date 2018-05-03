#ifndef XML_PARSER_LASERXMLPARSER_H_
#define XML_PARSER_LASERXMLPARSER_H_
#include "XmlParser.h"

class LaserXmlParser: public XmlParser {
 public:
  bool AddCraftDataNodes(int num);
  bool AddCraftDataAttributes(pugi::xml_node craftdata_node);
  void CraftDataAttributesComplement(pugi::xml_node craftdata_node);
  void CraftDataAttributesComplement(pugi::xpath_node_set craftdata_nodes);
  pugi::xpath_node_set CraftDataNodes();

};

#endif // XML_PARSER_LASERXMLPARSER_H_
