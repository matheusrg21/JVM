#include "../hpp/ClassFile.hpp"

ClassFile::ClassFile() {
    //Apenas para inicializar na main
}

ClassFile::ClassFile(FILE * fp) {
    this->setMagic(fp);
    if ((this->getMagic()) == 0xCAFEBABE) {
        this->setMinor(fp);
        this->setMajorVersion(fp);
        this->setConstantPoolCount(fp);
        this->setConstantPool(fp);
        this->setAccessFlags(fp);
        this->setThisClass(fp);
        this->setSuperClass(fp);
        this->setInterfacesCount(fp);
        this->setInterfaces(fp);
        this->setFieldsCount(fp);
        this->setFields(fp);
        this->setMethodsCount(fp);
        this->setMethods(fp);
        this->setAttributesCount(fp);
        this->setAttributes(fp);
    }
    else {
        cout << "O magic number nao eh 0xCAFEBABE! Programa terminado!" << endl;
        exit(0);
    }
}

ClassFile::~ClassFile() {
    // for (auto i : interfaces) {
    //     i->~InterfaceInfo();
    // }

    // // for (auto a : attributes) {
    // //     a->~AttributeInfo();
    // // }

    // for(auto f : fields) {
    //     f->~FieldInfo();
    // }

    // //Isso causa segfault nao sei pq
    // // for(auto m : methods) {
    // //     m->~MethodInfo();
    // // }

    // for(auto cp : constantPool) {
    //     cp->~CPInfo();
    // }
}


void ClassFile::setMagic(FILE * fp) {
    ByteReader<typeof(magic)> magicReader;
    magic = magicReader.byteCatch(fp);
}

void ClassFile::setMajorVersion(FILE * fp) {
    ByteReader<typeof(majorVersion)> majorReader;
    majorVersion = majorReader.byteCatch(fp);
}

void ClassFile::setMinor(FILE * fp) {
    ByteReader<typeof(majorVersion)> minorReader;
    minorVersion = minorReader.byteCatch(fp);
}

void ClassFile::setConstantPoolCount(FILE * fp) {
    ByteReader<typeof(constantPoolCount)> cpCountReader;
    constantPoolCount = cpCountReader.byteCatch(fp);
}

void ClassFile::setConstantPool(FILE * fp) {
    for (int i = 0; i < this->constantPoolCount-1; i++) {
        CPInfo *cpInfo = (CPInfo*)calloc(1, sizeof(CPInfo));
        cpInfo->read(fp);
        this->constantPool.push_back(cpInfo);

        if((cpInfo->getTag() == CPInfo::CONSTANT_Double) || (cpInfo->getTag() == CPInfo::CONSTANT_Long)) {
            CPInfo *emptyCPInfo = (CPInfo *)calloc(1, sizeof(CPInfo));
            emptyCPInfo->setTag(CPInfo::CONSTANT_Empty);
            this->constantPool.push_back(emptyCPInfo);
            i++;
        }
    } 
}

void ClassFile::setAccessFlags(FILE * fp) {
    ByteReader<typeof(accessFlags)> accessFlagsReader;
    accessFlags = accessFlagsReader.byteCatch(fp);
}

void ClassFile::setThisClass(FILE * fp) {
    ByteReader<typeof(thisClass)> thisClassReader;
    thisClass = thisClassReader.byteCatch(fp);
}

void ClassFile::setSuperClass(FILE * fp) {
    ByteReader<typeof(superClass)> superClassReader;
    superClass = superClassReader.byteCatch(fp);
}

void ClassFile::setInterfacesCount(FILE * fp) {
    ByteReader<typeof(interfacesCount)> interfacesCountReader;
    interfacesCount = interfacesCountReader.byteCatch(fp);
}

void ClassFile::setInterfaces(FILE * fp) {
    for (int i = 0; i < this->interfacesCount; i++) {
        InterfaceInfo *interfaceInfo = (InterfaceInfo*)calloc(1, sizeof(InterfaceInfo));
        interfaceInfo->read(fp);
        this->interfaces.push_back(interfaceInfo);
    }
    
}

void ClassFile::setFieldsCount(FILE * fp) {
    ByteReader<typeof(fieldsCount)> fieldsCountReader;
    fieldsCount = fieldsCountReader.byteCatch(fp);
}

void ClassFile::setFields(FILE * fp) {
    for(int i = 0; i < this->fieldsCount; i++) {
        FieldInfo* field = (FieldInfo *)calloc(1, sizeof(FieldInfo));
        field->read(fp, this->constantPool);
        this->fields.push_back(field);
    }
}

void ClassFile::setMethodsCount(FILE * fp) {
    ByteReader<typeof(methodsCount)> methodsCountReader;
    methodsCount = methodsCountReader.byteCatch(fp);
}

void ClassFile::setMethods(FILE * fp) {
    for (int i = 0; i < this->methodsCount; i++) {
        MethodInfo *methodInfo = (MethodInfo *)calloc(1, sizeof(MethodInfo));
        methodInfo->read(fp,this->constantPool);
        this->methods.push_back(methodInfo);
    }
}

void ClassFile::setAttributesCount(FILE * fp) {
    ByteReader<typeof(attributesCount)> attributesCountReader;
    attributesCount = attributesCountReader.byteCatch(fp);
}

void ClassFile::setAttributes(FILE * fp) {
    this->attributes = (AttributeInfo*)calloc(this->attributesCount, sizeof(AttributeInfo));

    for(int i = 0; i < this->attributesCount; i++) {
        AttributeInfo *attribute = (AttributeInfo *)calloc(1, sizeof(AttributeInfo));
        attribute->read(fp, this->constantPool);
        attributes[i] = *attribute;
    }
}