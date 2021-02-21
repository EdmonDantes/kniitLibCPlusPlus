import lldb

namespace = 'kniit_library'

def fullName(shortName):
    return namespace + '::' + shortName

def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand('command script add -f module.helloWorld hello')
    addSummary(debugger, 'Number')
    addSummary(debugger, 'String')
    addSyntheticForClass(debugger, 'List<', 'ListSyntheticChildrenProvider')
    print('Loaded')


def addSummary(debugger, className):
    debugger.HandleCommand('type summary add -F {0}.{1}Summary {2}'.format(__name__, className, fullName(className)))

def addSyntheticForClass(debugger, str_class, python_class):
    debugger.HandleCommand('type synthetic add -l {0}.{1} -x {2}'.format(__name__, python_class, fullName(str_class)))
    # for cls in findClasses(debugger, str_class):  # debugger.GetSelectedTarget().FindTypes(str_class):
    #     print("find class '{0}'".format(cls))

def normalizeValue(value):
    if value and (value.GetType().IsPointerType() or value.GetType().IsReferenceType()):
        return value.Dereference()
    else:
        return value

def printFields(value):
    fields = []
    for field in value.GetType().get_fields_array():
        fields.append(field.name)
    print("Fields for class '{0}' = {1}".format(value.GetType(), fields))

def findField(_value, fieldName):
     value = normalizeValue(_value)
     # print('Find field ' + fieldName)
     # printFields(value)
     member = next((x for x in value.GetType().get_fields_array() if x.name == fieldName), None)
     if member:
        return value.CreateChildAtOffset(fieldName, member.byte_offset, member.type)
     else:
         return None

def helloWorld(debugger, command, result, internal_dict):
    print('Hello, world!')


def checkMask(number, mask):
    return (number & mask) == mask


def getNumberAndTypeFromNumberClass(_value):
    value = normalizeValue(_value)
    status = findField(value, 'status').GetValueAsUnsigned(0)
    numberData = findField(value, 'number').GetData()
    isFixed = checkMask(status, 1)
    isFloat = checkMask(status, 64)
    isDouble = checkMask(status, 128)
    isSigned = checkMask(status, 32)

    is8Bit = checkMask(status, 2)
    is16Bit = checkMask(status, 4)
    is32Bit = checkMask(status, 8)
    is64Bit = checkMask(status, 16)

    error = lldb.SBError()

    if isDouble:
        number = numberData.GetDouble(error, 0)
    elif isFloat:
        number = numberData.GetFloat(error, 4)
    else:
        if is8Bit:
            if isSigned:
                number = numberData.GetSignedInt8(error, 7)
            else:
                number = numberData.GetUnsignedInt8(error, 7)
        elif is16Bit:
            if isSigned:
                number = numberData.GetSignedInt16(error, 6)
            else:
                number = numberData.GetUnsignedInt16(error, 6)
        elif is32Bit:
            if isSigned:
                number = numberData.GetSignedInt32(error, 4)
            else:
                number = numberData.GetUnsignedInt32(error, 4)
        elif is64Bit:
            if isSigned:
                number = numberData.GetSignedInt64(error, 0)
            else:
                number = numberData.GetUnsignedInt64(error, 0)

    if error.fail:
        print("Error on print get number from class Number")
        print(error)
        return None

    result = {}
    result['value'] = number if number else None
    result['fixed'] = isFixed
    return result

class ListClassList:
    def __init__(self, _value, internal_dict):
        value = normalizeValue(_value)
        self.size = findField(value, '_size').GetValueAsUnsigned(0)
        self.array = findField(value,   'value')
        if self.array.GetType().IsPointerType():
            self.data_type = self.array.GetType().GetPointeeType()
        else:
            self.data_type = self.array.GetType()
        self.data_size = self.data_type.GetByteSize()

    def get(self, index):
        if index < 0:
            return None
        if index >= self.size:
            return None
        try:
            offset = index * self.data_size
            return self.array.CreateChildAtOffset('[' + str(index) + ']', offset, self.data_type)
        except BaseException as e:
            print(e)
            return None

# -------------- Summaries --------------------


def NumberSummary(value, internal_dict):
    if (value):
        pair = getNumberAndTypeFromNumberClass(value)
        return ('const ' if pair['fixed'] else '') + str(pair['value'])
    else:
        return None

def StringSummary(_value, internal_dict):
    result = ""
    if (_value):
        value = normalizeValue(_value)
        _list = ListClassList(findField(value, 'value'), internal_dict)

        for i in range(0, _list.size):
            result = result + chr(getNumberAndTypeFromNumberClass(_list.get(i))['value'])
        return result
    else:
        return None

# -------------- Synthetic providers --------------------

class ListSyntheticChildrenProvider:
    def __init__(self, value, internal_dict):
        self.value = value
        self.dict = internal_dict
        self.list = ListClassList(value, internal_dict)

    def num_children(self):
        return self.list.size

    def get_child_index(self, name):
        try:
            return int(name.lstrip('[').rstrip(']'))
        except:
            return -1

    def get_child_at_index(self, index):
        if index < 0:
            return None
        if index >= self.list.size:
            return None

        return self.list.get(index)

    def update(self):
        self.list = ListClassList(self.value, self.dict)

    def has_children(self):
        return self.list.size > 0
