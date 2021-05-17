#include <iostream>
#include <map>
#include <functional>
#include <string>

struct BaseHuman;
struct DerivedDog;

struct Vtable {
    std::map<std::string, std::function<void(void*)>> vtable;
};

#define VIRTUAL_CLASS(BaseName) Vtable Vtable##BaseName; struct BaseName{ Vtable* VTable = &Vtable##BaseName;

#define END };

#define DECLARE_METHOD(Class, Name) void Name##Class(void* self); \
struct Help##Name##Class{Help##Name##Class(){ Vtable##Class.vtable[#Name] = Name##Class; }} help##Name##Class; \
void Name##Class(void* self)

#define VIRTUAL_CALL(Object, FunctionName) Object->VTable->vtable[#FunctionName](Object);

VIRTUAL_CLASS(BaseHuman)
    int age;
    std::string speech;
END
DECLARE_METHOD(BaseHuman, Both) {
    int a = reinterpret_cast<BaseHuman*>(self)->age;
    std::cout << "Human::Both age = " << a << "\n";
}
DECLARE_METHOD(BaseHuman, OnlyBase) {
    std::string s = reinterpret_cast<BaseHuman*>(self)->speech;
    std::cout << "Human::OnlyHuman speech = " << s << "\n";
}

VIRTUAL_CLASS(DerivedDog)
    int age;
    std::string breed;
END
DECLARE_METHOD(DerivedDog, Both) {
    int a = reinterpret_cast<DerivedDog*>(self)->age;
    std::cout << "DerivedDog::Both age = " << a << "\n";
}
DECLARE_METHOD(DerivedDog, OnlyDerived) {
    std::string b = reinterpret_cast<DerivedDog*>(self)->breed;
    std::cout << "DerivedDog::OnlyDog breed = " << b << "\n";
}

int main()
{
    BaseHuman base = BaseHuman();
    base.age = 21;
    base.speech = "Hello!";
    BaseHuman* pbase = &base;
    DerivedDog derived = DerivedDog();
    derived.age = 2;
    derived.breed = "fox terrier";
    BaseHuman* reallyDerived = reinterpret_cast<BaseHuman*>(&derived);

    VIRTUAL_CALL(pbase, Both)
    VIRTUAL_CALL(reallyDerived, Both)
    VIRTUAL_CALL(pbase, OnlyBase)
    VIRTUAL_CALL(reallyDerived, OnlyDerived)

    return 0;
}