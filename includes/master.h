#ifndef Master_H
#define Master_H


//----------------------------------------------------------------------
//  Project: Ydle
//-------------------------------------------------------------------------
//  Author: 
//
//-------------------------------------------------------------------------
//
//  Copyright 2013
//-------------------------------------------------------------------------
#include "NodesManager.h"
#include "restLoggerDestination.h"
#include "SettingsParser.h"
#include "IhmCommunicationThread.h"
#include "NodeRequestHandler.h"
#include "MasterRequestHandler.h"
#include "ScriptsManager.h"
#include "logging.h"
#include <memory>
#include <string>

namespace ydle {

class Master
{
public:
	Master (int argc, char **argv)  ;
	void	StartComm() ;
	void	Start() ;
	NodesManager * NodesMgr () {return &_nodesManager ; }
	ScriptsManager * ScriptsMgr () {return &_scriptsManager ; }
private:
	void	InitLog () ;
	void	InitRestLog();
	void	InitPlugins () ;
	void	InitProtocols () ;
	void	InitFeatures () ;
	void	StartFeatures () ;

private:
	StdErrorLogDestination *stderr_log ;
	restLoggerDestination *restLog ;
	SettingsParser *	_pSettings ;
	std::unique_ptr<IhmCommunicationThread> _pCom;
	Kernel				_kernel ;
	NodesManager		_nodesManager ;
        ScriptsManager          _scriptsManager ;
} ;

} ; // namespace ydle

#endif // Master_H
