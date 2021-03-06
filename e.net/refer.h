#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace Mono::Cecil;

ref struct EMethodData
{
	MethodReference^ Method;
	EMethodMode Mode;
	EMethodData();
	EMethodData(MethodReference^ method);
	EMethodData(MethodReference^ method, EMethodMode mode);
	bool operator==(EMethodData^ data);
	bool operator!=(EMethodData^ data);
	operator MethodReference ^ ();
	operator MethodDefinition ^ ();
};

ref struct ECListInfo
{
	EInfo* Info;
};

ref struct ELibInfo
{
	String^ Name;
	String^ Guid;
};

ref class CodeRefer
{
public:
	CodeRefer(ModuleDefinition^ module, IEnumerable<ELibInfo^>^ list);
	~CodeRefer();
	void AddType(ETAG tag, TypeDefinition^ type);
	void AddTypeRefer(ETAG tag, TypeReference^ type);
	void AddTypeRefer(ETAG tag, String^ fullname);
	void AddReferList(IEnumerable<String^>^ list);
	void AddReferList(String^ refer);
	void AddMethodRefer(short index, ETAG tag, EMethodData^ method);
	void AddMethodList(IEnumerable<EMethodData^>^ list);
	void AddVariable(ETAG tag, VariableDefinition^ var);
	void AddParameter(ETAG tag, ParameterDefinition^ param);
	void AddField(ETAG tag, FieldDefinition^ field);
	void AddGlobalVariable(ETAG tag, FieldDefinition^ var);
	void AddProperty(ETAG tag, PropertyDefinition^ prop);
	void AddECList(IEnumerable<String^>^ list);
	TypeDefinition^ FindType(ETAG tag);
	TypeDefinition^ FindType(String^ fullname);
	TypeReference^ FindTypeRefer(ETAG tag);
	TypeReference^ FindTypeRefer(String^ fullname);
	TypeDefinition^ FindTypeDefine(ETAG tag);
	TypeDefinition^ FindTypeDefine(String^ fullname);
	EMethodData^ FindMethodRefer(short index, ETAG tag);
	List<EMethodData^>^ FindMethodList(MethodReference^ method);
	List<EMethodData^>^ FindMethodList(String^ fullname);
	VariableDefinition^ FindVariable(ETAG tag);
	ParameterDefinition^ FindParameter(ETAG tag);
	FieldDefinition^ FindField(ETAG tag);
	FieldDefinition^ FindGlobalVariable(ETAG tag);
	PropertyDefinition^ FindProperty(ETAG tag);
	EMethodData^ FindLibMethod(short index, ETAG tag);
	TypeDefinition^ FindLibType(LIBTAG tag);
	PropertyDefinition^ FindLibTypeProperty(ETAG tag, UINT index);
	EventDefinition^ FindLibTypeEvent(ETAG tag, UINT index);
private:
	ModuleDefinition^ _module;
	Plugins^ _plugins;
	Dictionary<String^, TypeDefinition^>^ _type;
	Dictionary<UINT, String^>^ _typename;
	Dictionary<String^, TypeReference^>^ _typerefer;
	Dictionary<UINT, String^>^ _typerefername;
	Dictionary<short, Dictionary<UINT, EMethodData^>^>^ _method;
	Dictionary<String^, List<EMethodData^>^>^ _methodname;
	Dictionary<UINT, VariableDefinition^>^ _var;
	Dictionary<UINT, ParameterDefinition^>^ _param;
	Dictionary<UINT, FieldDefinition^>^ _field;
	Dictionary<UINT, FieldDefinition^>^ _globalvar;
	Dictionary<UINT, PropertyDefinition^>^ _prop;
	Dictionary<UINT, TypePackage^>^ _libtype;
	List<ECListInfo^>^ _eclist;
	List<ELibInfo^>^ _elib;
	List<PluginInfo^>^ _elibinfo;
	void LoadKrnln();
	void LoadE_Net();
	void LoadPlugins();
	void LoadLibType(UINT tag, TypePackage^ package);
};