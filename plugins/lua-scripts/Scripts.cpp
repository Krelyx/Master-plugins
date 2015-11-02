/*
 * LuaStack.cpp
 *
 *  Created on: Jan 31, 2014
 *      Author: denia
 */
#include <iostream>
#include <sys/time.h>


#include "Dir.h"
#include "Scripts.h"
#include "SettingsParser.h"
#include <string>
#include "ListPtr.h"
#include <cstring>    

using namespace ydle ;
using namespace std ;


//===============================================

//===============================================
Scripts::Scripts (std::string nom) : IFeature(nom)
{
}

Scripts::~Scripts ()
{
}
void Scripts::ReloadScript (const char *name)
{
        for (auto it = begin(); it != end(); it++) {
            if ( strcmp((*it)->NameStr(),name)==0){
                delete *it ;
                erase(it);
                break;
            }
	}
        printf ("Scripts::ReloadScript(%s)\n", name) ;
	LuaStack *lua = new LuaStack(name) ;
	push_back(lua); 
        lua->init () ;

}
void Scripts::LoadScript (const char *name)
{
        printf ("Scripts::LoadScript(%s)\n", name) ;
	LuaStack *lua = new LuaStack(name) ;
	push_back(lua); 
        lua->init () ;

}
void Scripts::UnloadScript (const char *name)
{
    printf ("Scripts::UnloadScript(%s)\n", name) ;    
    for (auto it = begin(); it != end(); it++) {
            if ( strcmp((*it)->NameStr(),name)==0){
                delete *it ;
                erase(it);
                break;
            }
	}    
}
void Scripts::AddScript (const char *name)
{
	printf ("Scripts::AddScript(%s)\n", name) ;
	LuaStack *lua = new LuaStack(name) ;
	push_back(lua); 
}
void Scripts::LoadScripts ()
{
	string dir = PARAM_STR("lua-scripts.running_scripts_dir");
	string pattern = PARAM_STR("lua-scripts.pattern");
	StringList files ;
	ListFiles (dir.c_str(), pattern.c_str(), files) ;

	for (StringList::iterator it = files.begin(); it != files.end(); ++it) {
		string full = dir + "/" + it->c_str() ;
                AddScript (full.c_str()) ;
	}

}
void Scripts::Plugins()
{
	string plugins_dir = PARAM_STR("lua-scripts.plugins_dir");

	if (size () == 0)  {
		printf ("ERROR : no plugins!!!!!!!!!\n") ;
		return ;
	}

	StringList files ;
	ListPlugins (plugins_dir.c_str(), files) ;
	for( StringList::iterator it = files.begin(); it != files.end(); ++it) {
		string full = plugins_dir + "/" + it->c_str() ;
printf ("%d  full<%s>\n", __LINE__, full.c_str());
		PluginLua * p = new PluginLua (full) ;
		for( iterator itThis = begin(); itThis != end(); ++itThis) {
			LuaStack * lua = *itThis ;
printf ("%d  lua<%s>\n", __LINE__, lua->NameStr());
			p->Register(lua->State()) ;
printf ("%d  lua<%s>\n", __LINE__, lua->NameStr());
		}
		this->_loadedPlugins.insert( PluginMap::value_type(*it, p)) ;
	}

}

void Scripts::Init()
{	
	SetPauseMs (PARAM_INT("lua-scripts:pause")) ; // pause 2 secondes
	LoadScripts () ;
	Plugins () ;
	for (iterator it = begin(); it != end(); it++) {
		(*it)->init () ;
	}
}

void Scripts::Run()
{
	for (iterator it = begin(); it != end(); it++) {
		(*it)->action () ;
	}
}

void Scripts::Start()
{
	Thread::Start() ;
}

void Scripts::ThreadBegin()
{
	printf ("Scripts::ThreadBegin TODO %d\n", __LINE__) ;
}
void Scripts::ThreadAction()
{
	Run () ;
        Pause () ;
}

void Scripts::ThreadEnd()
{
	printf ("ThreadEnd %d\n", __LINE__) ;
}

PluginLua::PluginLua(string & path) : mDyn(path.c_str())
{
}

bool PluginLua::Register (lua_State * l)
{
		return mDyn.ExecFuncTpl<bool, lua_State *>  ("LoadLua", l) ;
}
