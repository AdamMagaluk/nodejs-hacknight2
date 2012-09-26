
#include <node.h>
#include <v8.h>

#include "cpp_src/Dog.h"

using namespace v8;

class MyDogWrapper : public node::ObjectWrap, Dog {
public:

    static void Init(v8::Handle<v8::Object> target) {
        
        // Prepare constructor template
        Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
        tpl->SetClassName(String::NewSymbol("Dog"));
        tpl->InstanceTemplate()->SetInternalFieldCount(1);
        
        tpl->PrototypeTemplate()->Set(String::NewSymbol("Name"),
                FunctionTemplate::New(WrapName)->GetFunction());

        tpl->PrototypeTemplate()->Set(String::NewSymbol("move"),
                FunctionTemplate::New(Wrap_move)->GetFunction());
        
        
        Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
        target->Set(String::NewSymbol("Dog"), constructor);
    }

    MyDogWrapper(std::string name) : Dog(name) {
    }

    ~MyDogWrapper() {
    }
private:
    static v8::Handle<v8::Value> Wrap_move(const v8::Arguments& args) {
        HandleScope scope;
        MyDogWrapper* obj = ObjectWrap::Unwrap<MyDogWrapper> (args.This());
        obj->move();
        return scope.Close(Undefined());
    }

    static v8::Handle<v8::Value> WrapName(const v8::Arguments& args) {
        HandleScope scope;
        return scope.Close(String::New(ObjectWrap::Unwrap<MyDogWrapper > (args.This())->Name().c_str()));
    }
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