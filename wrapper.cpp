#define INIT_OBJ_WRAP(obj,name) Local<FunctionTemplate> obj = FunctionTemplate::New(New); \
                            obj->SetClassName(String::NewSymbol(#name)); \
                            obj->InstanceTemplate()->SetInternalFieldCount(1);

#define PERSIST_OBJ(target,obj,name)  Persistent<Function> constructor = Persistent<Function>::New(obj->GetFunction()); \
                                  target->Set(String::NewSymbol(#name), constructor);

#define FUNC_WRAP_NAME(name) wrap_string_ ##name

#define WRAP_FUNCTION(parent,name) parent->PrototypeTemplate()->Set(String::NewSymbol(#name), \
                FunctionTemplate::New(FUNC_WRAP_NAME(name))->GetFunction());              

#define FUNC_STRING_WRAP(obj,name) static v8::Handle<v8::Value> FUNC_WRAP_NAME(name)(const v8::Arguments& args) { \
                                   HandleScope scope;                                                                \
                                   return scope.Close(String::New(ObjectWrap::Unwrap<obj> (args.This())->name().c_str())); \
                                }

#define V8WRAP(name) static v8::Handle<v8::Value> FUNC_WRAP_NAME(name)(const v8::Arguments& args) {

#define GETWARPPED(type) ObjectWrap::Unwrap<type>(args.This());


#include <node.h>
#include <v8.h>

#include "cpp_src/Dog.h"

using namespace v8;



//#define SETUP_PC_COMMAND_WRAP(name) obj->SetAccessor(String::New(#name), FUNC_PC_COMMAND_ID(name), NULL);



class MyDogWrapper : public node::ObjectWrap, Dog {
public:

    static void Init(v8::Handle<v8::Object> target) {
        INIT_OBJ_WRAP(tpl,Dog)

        WRAP_FUNCTION(tpl,Name)
        WRAP_FUNCTION(tpl,move)
        
        PERSIST_OBJ(target,tpl,Dog)
    }

    MyDogWrapper(std::string name) : Dog(name) { }

private:
    V8WRAP(move)
        HandleScope scope;
        MyDogWrapper* obj = GETWARPPED(MyDogWrapper)
        obj->move();
        return scope.Close(Undefined());
    }

    FUNC_STRING_WRAP(MyDogWrapper,Name)
    
    static v8::Handle<v8::Value> New(const v8::Arguments& args) {
        HandleScope scope;
        if (args.Length() < 1) {
            ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
            return scope.Close(Undefined());
        }

        // get the param
        v8::String::Utf8Value param1(args[0]->ToString());
        MyDogWrapper* obj = new MyDogWrapper(*param1);
        obj->Wrap(args.This());

        return args.This();
    }
};



void InitAll(Handle<Object> target) {
     MyDogWrapper::Init(target);
}

NODE_MODULE(farm, InitAll)