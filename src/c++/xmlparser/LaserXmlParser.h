#ifndef XML_PARSER_LASERXMLPARSER_H_
#define XML_PARSER_LASERXMLPARSER_H_
#include "XmlParser.h"

class LaserXmlParser: public XmlParser {
 public:
  bool AddLayerNodes(int num);
  bool AddLayerContents(pugi::xml_node layer_node);
  void LayerNodeComplement(pugi::xml_node layer_node);
  void LayerNodesComplement(pugi::xpath_node_set layer_nodes);
  void SetCuttingProcedure();
  void SetPierce1Procedure();
  void SetPierce2Procedure();
  void SetPierce3Procedure();
  void SetStripingProcedure();
  void SetCoolingProcedure();
  void SetLaserOffProcedure();
  void SetLaserOffShortProcedure();

  bool AddProcessCfgNode(pugi::xml_node parent_node);
  bool AddProcessCfgAttributes(pugi::xml_node processcfg_node);
  void ProcessCfgAttributesComplement(pugi::xml_node node);

  bool AddCraftDataNodes(int num, pugi::xml_node parent_node);
  bool AddCraftDataAttributes(pugi::xml_node craftdata_node);
  void CraftDataAttributesComplement(pugi::xml_node craftdata_node);
  void CraftDataAttributesComplement(pugi::xpath_node_set craftdata_nodes);

  pugi::xpath_node_set LayerNodes();

};

#endif // XML_PARSER_LASERXMLPARSER_H_
