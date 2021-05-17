#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <string>

struct TypeInfo {
    TypeInfo(std::string _name = "")
    {
        name = _name;
    }
    bool operator==(const TypeInfo& other) const
    {
        return name == other.name;
    }
    bool operator!=(const TypeInfo& other) const
    {
        return name != other.name;
    }
    std::string name;
    int GetHash()
    {
        return std::hash<std::string>()(name);
    }
};

static std::map<std::string, TypeInfo> typeInfoForClasses;
static std::map<std::string, std::set< std::string > > baseClasses;
static std::map<std::string, std::set< std::string > > derivedClasses;

struct registrator {
    registrator(std::string derived, std::string base)
    {
        if (baseClasses.find(derived) == baseClasses.end()) {
            baseClasses[derived] = std::set<std::string>();
            baseClasses[derived].insert(derived);
        }
        if (derivedClasses.find(derived) == derivedClasses.end()) {
            derivedClasses[derived] = std::set<std::string>();
            derivedClasses[derived].insert(derived);
        }
        if (baseClasses.find(base) == baseClasses.end()) {
            baseClasses[base] = std::set<std::string>();
            baseClasses[base].insert(base);
        }
        if (derivedClasses.find(base) == derivedClasses.end()) {
            derivedClasses[base] = std::set<std::string>();
            derivedClasses[base].insert(base);
        }
        for (auto ancestor : baseClasses[base]) {
            baseClasses[derived].insert(ancestor);
            derivedClasses[ancestor].insert(derived);
        }
    }
};

#define NEW(B, T, o) new T();                             \
typeInfoForClasses[std::string(#o)] = TypeInfo(#T);


#define TYPEID(o) typeInfoForClasses[std::string(#o)]

#define EXTENDS(Derived, Base) Derived : Base { \
registrator r = registrator(#Derived, #Base);

#define MEXTENDS(Derived, Base1, Base2) Derived : Base1, Base2 { \
registrator r1 = registrator(#Derived, #Base1); \
registrator r2 = registrator(#Derived, #Base2);

#define _EXIST(collection, element) collection.find(element) != collection.end()

inline bool haveCommonDescendant(const std::string& A, const std::string& B)
{
    for (auto d : derivedClasses[A]) {
        if (_EXIST(derivedClasses[B], d)) return true;
    }
    return false;
}

#define DYNAMIC_CAST(R, T, a) \
((_EXIST(baseClasses[#R], #T) || _EXIST(derivedClasses[#R], #T) || haveCommonDescendant(#R, #T)) ? \
reinterpret_cast<T*>(reinterpret_cast<T*>(a)) : static_cast<T*>(nullptr))

struct Base {
    virtual void printType() {
        std::cout << "Base" << std::endl;
    }
    void printCurrentType()
    {
        std::cout << "Base" << std::endl;
    }
    int k;
};

struct EXTENDS(DerivedA, Base)
    virtual void printType()
    {
        std::cout << "DerivedA" << std::endl;
    }
    void printCurrentType()
    {
        std::cout << "DerivedA" << std::endl;
    }
    int d = 20;
    int e = 100;
    int c = 10;
};

struct EXTENDS(DerivedB, Base)
    virtual void printType()
    {
        std::cout << "DerivedB" << std::endl;
    }
    void printCurrentType()
    {
        std::cout << "DerivedB" << std::endl;
    }
    int e = 115;
    int a;
    int b;
};

struct EXTENDS(DerivedBB, DerivedB)
    virtual void printType()
    {
        std::cout << "DerivedBB" << std::endl;
    }
    void printCurrentType()
    {
        std::cout << "DerivedBB" << std::endl;
    }
    int z;
};


struct MEXTENDS(Derived, DerivedA, DerivedB)
    virtual void printType()
    {
        std::cout << "Derived" << std::endl;
    }
    void printCurrentType()
    {
        std::cout << "Derived" << std::endl;
    }
    int a;
    int b;
};

class AAA {
};

int main()
{
    DerivedB *d = NEW(DerivedB, Derived, d);

    DYNAMIC_CAST(DerivedB, DerivedA, d)->printType(); // Derived (function is virtual)
    DYNAMIC_CAST(DerivedB, DerivedA, d)->printCurrentType(); // DerivedA

    Base *a = NEW(Base, DerivedB, a);
    Base *b = NEW(Base, Base, b);
    Base *c = NEW(Base, DerivedBB, c);

    // a
    std::cout << "real type of a: " << TYPEID(a).name << std::endl;
    std::cout << "dynamic_cast<Base*>(a):" << std::endl;
    Base* p1 = DYNAMIC_CAST(Base, Base, a);
    p1->printType(); // DerivedB (function is virtual)
    p1->printCurrentType(); // Base
    std::cout << std::endl;

    std::cout << "dynamic_cast<DerivedB*>(a):" << std::endl;
    DerivedB* p2 = DYNAMIC_CAST(Base, DerivedB, a);
    p2->printType(); // DerivedB (function is virtual)
    p2->printCurrentType(); // DerivedB
    std::cout << std::endl;

    // b
    std::cout << "dynamic_cast<Base*>(b):" << std::endl;
    Base* p3 = DYNAMIC_CAST(Base, Base, b);
    p3->printType(); // Base (function is virtual)
    p3->printCurrentType(); // Base
    std::cout << std::endl;

    // c
    std::cout << "dynamic_cast<DerivedB*>(c):" << std::endl;
    DYNAMIC_CAST(Base, DerivedB, c)->printType(); // DerivedBB (function is virtual)
    DYNAMIC_CAST(Base, DerivedB, c)->printCurrentType(); // DerivedB
    std::cout << std::endl;

    // d
    std::cout << "dynamic_cast<DerivedB>(d):" << std::endl;
    std::cout << TYPEID(d).name << std::endl;
    DYNAMIC_CAST(DerivedB, Derived, d)->printType(); // Derived (function is virtual)
    DYNAMIC_CAST(DerivedB, Derived, d)->printCurrentType(); // Derived
    std::cout << std::endl;

    // static after dynamic
    Derived* dd = DYNAMIC_CAST(DerivedB, Derived, d);
    static_cast<DerivedA*>(dd)->printType();
    static_cast<DerivedA*>(dd)->printCurrentType();

    // nullptr
    AAA* n1 = DYNAMIC_CAST(DerivedB, AAA, d);
    std::cout << n1;

    return 0;
}