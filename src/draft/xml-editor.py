
all_suffixex = ['__Type', '__DisplayName', '__Length', '__EditAble', '__SelectType', 
            '__UnitName', '__Min', '__Max', '__Custom', '__Privilege', '__Map', '__Enum',
            '__Translate']

class ElementNode:
	def __init__(self):
		self.name = None
		self.level = 0            
		self.type = 0             // 0 attr, 1 node
		self.attributes = []
		self.values = []
		self.prev = None

    def prev(self):
    	return self.prev

    def add_child(self, ElementNode child):
    	pass




