#include <iostream>
#include <map>
#include <functional>
#include <string>

struct BaseHuman;
struct DerivedDog;

struct Vtable {
    std::map<std::string, std::function<void(void*)>> vtable;
};

#define VIRTUAL_CLASS(BaseName) struct BaseName; \
Vtable Vtable##BaseName; \
struct BaseName{\
Vtable* VTable = &Vtable##BaseName;

#define END };

#define DECLARE_METHOD(Class, Name) static void Name##Class(void* self) { \
    Class* casted_self = (Class*) self;

#define END_DECLARATION(Class, Name) }  \

#define VIRTUAL_CALL(Object, FunctionName) Object->VTable->vtable[#FunctionName](Object);

#define ADD_FUNCTION(Class, Name) this->VTable->vtable.emplace(#Name, this->Name##Class);
#define BASE_CONSTRUCTOR(Class, CODE) Class() { CODE }

#define DERIVED_CONSTRUCTOR(BaseClass, DerivedClass, CODE) DerivedClass() { \
    CODE\
    for (const auto& [name, cl] :  Vtable##BaseClass.vtable) {  \
         if (this->VTable->vtable.count(name) == 0) { \
            this->VTable->vtable.emplace(name, cl); \
         } \
    }\
};

VIRTUAL_CLASS(BaseHuman)
    int age;
    std::string speech;

DECLARE_METHOD(BaseHuman, Both)
    int a = casted_self->age;
    std::cout << "Human::Both age = " << a << "\n";
END_DECLARATION(BaseHuman, Both)

DECLARE_METHOD(BaseHuman, OnlyBase)
    std::string s = casted_self->speech;
    std::cout << "Human::OnlyHuman speech = " << s << "\n";
END_DECLARATION(BaseHuman, OnlyBase)

BASE_CONSTRUCTOR(BaseHuman,
                 ADD_FUNCTION(BaseHuman, Both)
                        ADD_FUNCTION(BaseHuman, OnlyBase)
)
END

VIRTUAL_CLASS(DerivedDog)
    int age;
    std::string speech;
    std::string breed;
DECLARE_METHOD(DerivedDog, Both)
    int a = casted_self->age;
    std::cout << "DerivedDog::Both age = " << a << "\n";
END_DECLARATION(DerivedDog, Both)

DECLARE_METHOD(DerivedDog, OnlyDerived) {
    std::string b = casted_self->breed;
    std::cout << "DerivedDog::OnlyDog breed = " << b << "\n";
}
END_DECLARATION(DerivedDog, OnlyDerived)

DERIVED_CONSTRUCTOR(BaseHuman, DerivedDog,
                    ADD_FUNCTION(DerivedDog, Both)
                    ADD_FUNCTION(DerivedDog, OnlyDerived))
END

int main()
{
    BaseHuman base = BaseHuman();
    base.age = 21;
    base.speech = "Hello!";
    BaseHuman* pbase = &base;
    DerivedDog derived = DerivedDog();
    derived.age = 2;
    derived.breed = "fox terrier";
    derived.speech = "Hello, I'm only dog and cannot speak.";
    BaseHuman* reallyDerived = reinterpret_cast<BaseHuman*>(&derived);

    VIRTUAL_CALL(pbase, Both)
    VIRTUAL_CALL(pbase, OnlyBase)

    VIRTUAL_CALL(reallyDerived, Both)
    VIRTUAL_CALL(reallyDerived, OnlyBase)
    VIRTUAL_CALL(reallyDerived, OnlyDerived)

    return 0;
}