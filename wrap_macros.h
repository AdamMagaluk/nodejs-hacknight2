/* 
 * File:   wrap_macros.h
 * Author: adam
 *
 * Created on September 26, 2012, 3:53 PM
 */

#ifndef WRAP_MACROS_H
#define	WRAP_MACROS_H


#include <node.h>
#include <v8.h>


using namespace v8;


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


#endif	/* WRAP_MACROS_H */

