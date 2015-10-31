/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScriptsManager.h
 * Author: Xylerk
 *
 * Created on 29 octobre 2015, 21:58
 */

#ifndef SCRIPTSMANAGER_H
#define SCRIPTSMANAGER_H

#include "Kernel.h"
#include "IScriptsManager.h"
#include "IFeature.h"
#include <list>
#include <string>

namespace ydle {

class ScriptsManager : public IScriptsManager
{

public:

	ScriptsManager () {}; 
        void Init (Kernel * k) ;
        virtual int	ReloadScript (string script_file) ;	
private:

	Kernel::FeatureList	* pFeatures ;
} ;

} ; // namespace ydle


#endif /* SCRIPTSMANAGER_H */

