#!/usr/bin/pyhon3

import xml.etree.cElementTree as ET
import sys

def format_attr(fout, key, node):
    attr_suffix = ''
    for suffix in all_suffixex:
        attr_suffix = key + suffix
        if attr_suffix in node.keys():
            fout.write(' ' + attr_suffix + '=' + '"' + node.get(attr_suffix) + '"')



def format_node(fout, node, level):
    if len(node) == 0 and len(node.keys()) == 0:
        fout.write('\t' * level + '<' + node.tag + '/>\n')
        return
    else:
        pass

    # node attributes
    if len(node.keys()) == 0:
        fout.write('\t' * level + '<' + node.tag + '>\n')
    else:
        special_attr = ''
        if 'CountType' in node.keys():
            special_attr = 'CountType="' + node.get('CountType') + '"'
        elif 'Version' in node.keys():
            special_attr = special_attr + 'Version="' + node.get('Version') + '"'

        fout.write('\t' * level + '<' + node.tag + ' ' + special_attr)
        for key in sorted(node.keys()):
            if key == 'CountType' or key == 'Version':
                continue
            if '_' not in key:
                fout.write('\n')
                fout.write('\t' * (level + 1) + \
                    key + '=' + '"' + node.get(key) + '"')

                format_attr(fout, key, node)

        if len(node) == 0:
            fout.write('/>\n')
        else:
            fout.write('>\n')

    # node text
    if node.text and node.text.strip():
        fout.write('\t' * (level + 1) + node.text.strip() + '\n')

    #node child
    for child in node:
        format_node(fout, child, level + 1)

    if len(node) != 0:
        fout.write('\t' * level + '</' + node.tag + '>\n')


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: format_xml.py input_file outputfile")

    tree = ET.parse(sys.argv[1])
    root = tree.getroot()
    fout = open(sys.argv[2], "w")
    fout.write("""<?xml version="1.0" encoding="utf-8"?>
<!-- edited with XMLSPY v5 rel. 2 U (http://www.xmlspy.com) by 123 (456) -->
<!-- edited with Dawei Zuo-->\n""")

    all_suffixex = ['__Type', '__DisplayName', '__Length', '__EditAble', '__SelectType',
            '__UnitName', '__Min', '__Max', '__Custom', '__Privilege', '__Map', '__Enum',
            '__Translate']

    format_node(fout, root, 0)
    fout.close()
