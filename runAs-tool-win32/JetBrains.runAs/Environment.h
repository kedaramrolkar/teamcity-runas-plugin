#pragma once
#include <list>
#include <map>
#include "Result.h"
#include "Handle.h"
#include <set>

class Trace;

class Environment
{		
	list<LPVOID*> _environmentBlocks;
	map<wstring, wstring> _vars;
	bool _empty = true;

	void CreateVariableMap(LPVOID environment, Trace& trace);
	LPVOID* CreateEnvironmentFromMap();
	static void Environment::TraceVarible(Trace& trace, const wstring& key, const wstring& value);

public:
	static Result<Environment> CreateForCurrentProcess(Trace& trace);
	static Result<Environment> CreateForUser(Handle& token, bool inherit, Trace& trace);
	static Environment CreateFormString(wstring variables, Trace& trace);
	static Environment Override(const Environment& baseEnvironment, const Environment& sourceEnvironment, Trace& trace);
	~Environment();
	LPVOID* CreateEnvironment();
	wstring TryGetValue(wstring variableName);
	static set<wstring> GetAutoOverrides();	
};
