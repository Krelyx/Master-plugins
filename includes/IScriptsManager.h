/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IScriptsManager.h
 * Author: Xylerk
 *
 * Created on 29 octobre 2015, 21:55
 */

#ifndef ISCRIPTSMANAGER_H
#define ISCRIPTSMANAGER_H
#include <string>
namespace ydle {


class IScriptsManager
{
public:
	virtual ~IScriptsManager () {}
	virtual int	ReloadScript (std::string script_file) = 0 ;
} ;

} // namespace ydle




#endif /* ISCRIPTSMANAGER_H */

