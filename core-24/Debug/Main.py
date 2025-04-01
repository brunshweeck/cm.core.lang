from abc import ABCMeta, abstractmethod
import re
from gdb import Value, TYPE_CODE_REF,lookup_type,current_objfile,pretty_printers # type: ignore

from typing import Type

class PyIterator:
    def __init__(self, items: list):
        self.items = items
        self.size = len(items)
        self.next = 0
    
    def __iter__(self):
        return self
    
    def __next__(self):
        if self.next >= self.size:
            raise StopIteration
        index = self.next
        self.next = index + 1
        item = self.items[index]
        
        if len(item) == 1:
            assert not isinstance(item, tuple)
            return str(index), item
        
        assert len(item) == 2
        return str(item[0]), item[1]

class PyClass(metaclass=ABCMeta):
    def __init__(self, typename:str, value: Value):
        self.children: list | PyIterator = []
        self.displayString = ''
        self.object: dict[str, str|Value] = {
            'type': typename,
            'value': value
        }
        pass
    
    def to_string(self)-> str:
        return self.displayString
    
    @classmethod
    def toPointer(cls, value: Value, elementType: str) -> Value:
        return value.cast(lookup_type(elementType).pointer())
    
    @classmethod
    def toReference(cls, value: Value, elementType: str) -> Value:
        return value.dynamic_cast(lookup_type(elementType))
    
    @classmethod
    def findPlayer(cls, value: Value):
        player = defaultPrinter.__call__(value)
        if player:
            return player.pyObject
    
    @classmethod
    def pattern(cls) -> str:
        pass

class Display:
    def __init__(self, pyObject: PyClass):
        self.pyObject = pyObject

class Printer:
    def __init__(self, name:str):
        self.printers = []
        self.patterns:list[re.Pattern] = []
        self.name = name
        self.enable = True
        self.visualizers = {}
        
    def createVisualizer(self, pattern: str, pyClass: Type[PyClass]):
        if '*' not in pattern and '^' not in pattern and '$' not in pattern:
            self.visualizers[pattern] = self.Visualiser(pattern, pyClass)
        else:
            self.patterns.append(re.compile(pattern))
            self.printers.append(Printer.Visualiser(pattern, pyClass))
            
    def __call__(self, value: Value):
        type = value.type
        if type.code == TYPE_CODE_REF:
            type = type.target()
            if hasattr(value, 'referenced_value'):
                value = value.referenced_value()
        name = type.unqualified().strip_typedefs()
        if name:
            if value.dynamic_type:
                dtype = value.dynamic_type
                if dtype.code == TYPE_CODE_REF:
                    dtype = dtype.target()
                    if hasattr(value, 'referenced_value'):
                        value = value.referenced_value()
                dname = dtype.tag
                if dname != name and dname is not None:
                    name = dname
                    value = value.address.dynamic_cast(dtype.pointer)
                    if hasattr(value, 'referenced_value'):
                        value = value.referenced_value()
            
            # Search the player of given value with lazy name
            if name in self.visualizers:
                visualiser = self.visualizers[name]
                assert isinstance(visualiser, Printer.Visualiser)
                return visualiser.show(value)
            
            # Search the player of given value with pattern name
            index = -1
            for pattern in self.patterns:
                index += 1
                if pattern.match(name):
                    visualiser = self.printers[index]
                    assert isinstance(visualiser, Printer.Visualiser)
                    if visualiser.enable and visualiser.pyClass:
                        return visualiser.show(value)
                        
                
            

    class Visualiser:
        def __init__(self, pattern: str, pyClass: Type):
            self.pyClass = pyClass
            self.pattern = pattern
            self.enable = True
            
        def show(self, value: Value):
            if value and  value.address != 0 and value.type.code == TYPE_CODE_REF:
                value = value.reference_value()
                pattern = value.dynamic_type.name
                if pattern is not None:
                    if pattern != self.pattern:
                        defaultPrinter.createVisualizer(pattern, self.pyClass)
                    return Printer.wrap(self.pyClass(pattern, value))
    
    class LinearDisplay(Display):
        def __init__(self, pyObject:PyClass):
            super().__init__(pyObject)
    
    class ExpensibleDisplay(Display):
        def __init__(self, pyObject:PyClass):
            super().__init__(pyObject)
        
        def children(self):
            if isinstance(self.pyObject.children, PyIterator):
                return self.pyObject.children
            
            if isinstance(self.pyObject.children, list):
                return PyIterator(self.pyObject.children)
    
    @classmethod
    def wrap(cls, pyObject: PyClass):
        if isinstance(pyObject.children, list):
            if len(pyObject.children) == 0:
                return Printer.LinearDisplay(pyObject)
            return Printer.ExpensibleDisplay(pyObject)
        if isinstance(pyObject.children, PyIterator):
            return Printer.ExpensibleDisplay(pyObject)
        if isinstance(pyObject.children, PyIterator):
            return Printer.LinearDisplay(pyObject)
            

defaultPrinter = Printer('Core-24')

classList: list[Type[PyClass]] = [
    
    # Insert your pyClass version
]

def registration():
    global defaultPrinter
    global classList
    
    classList.extend([
        # Insert your pyClass version
    ])
    
    # Registration of pyClass 
    
    for cclass in classList:
        pattern = cclass.pattern()
        defaultPrinter.createVisualizer(pattern, cclass)
        
    # Registration of Printers
    
    if defaultPrinter:
        defaultGdbFile = current_objfile()
        if defaultGdbFile:
            defaultGdbFile.pretty_printers.append(defaultPrinter)
        else:
            pretty_printers.append(defaultPrinter)


registration()
        
del ABCMeta
del re
del Value 
del TYPE_CODE_REF
del lookup_type
del current_objfile
del pretty_printers
del Type
