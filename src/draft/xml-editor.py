#!/usr/bin/python3

all_suffixex = ['__Type', '__DisplayName', '__Length', '__EditAble', '__SelectType',
        '__UnitName', '__Min', '__Max', '__Custom', '__Privilege', '__Map', '__Enum',
        '__Translate']

class AttributeNode:
    def __init__(self):
        self.attributes = {}

    def add_attr(self, key, value):
        self.attributes[key] = value

    def format_output(self):
        content = ""
        n = 0
        for key in self.attributes:
            if n == 0:
                content = content + key + '=' + '"' + self.attributes[key] + '"';
            else:
                content = content + ' ' + key + '=' + '"' + self.attributes[key] + '"'

            n = n + 1

        return content

class ElementNode:
    def __init__(self):
        self.name = None
        self.level = 0
        self.type = 0
        self.attr_nodes = []
        self.childs = []

    def add_child(self, child):
        self.childs.append(child)

    def add_attr(self, attr_node):
        self.attr_nodes.append(attr_node);

    def format_output(self, fout):
        fout.write('\t\t' * self.level + '<' + self.name + '\n');
        attrs = len(self.attr_nodes)
        n = 1
        for attr in self.attr_nodes:
            fout.write('\t\t' * (self.level + 1) + attr.format_output())
            if n == attrs:
                if len(self.childs) == 0:
                    fout.write('/>\n')
                else:
                    fout.write('>\n')
            else:
                fout.write('\n')

        for child in self.childs:
            child.format_output(fout)

        if len(self.childs) > 0:
            fout.write('\t\t' * self.level + '</' + self.name + '>\n');

if __name__ == "__main__":
    root = ElementNode()
    root.name = "Home"
    root.level = 0
    attr = AttributeNode()
    attr.add_attr("HomePort", "1")
    attr.add_attr("HomeDir", "True")
    root.add_attr(attr)
    child = ElementNode()
    child.name = "child"
    child.level = 1
    child.add_attr(attr)
    root.add_child(child)

    fout = open("test.xml", 'w')
    root.format_output(fout)

