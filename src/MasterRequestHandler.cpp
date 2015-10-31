/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "logging.h"
#include "MasterRequestHandler.h"
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "Dir.h"
#include "SettingsParser.h"
using namespace ydle ;

namespace WebServer {
    #define NBSEND 1
//static struct timespec WaitEndCmommand={0,900000000L};

MasterRequestHandler::MasterRequestHandler(IScriptsManager* m) : _pScripts(m)
{
}

MasterRequestHandler::~MasterRequestHandler()
{
	// TODO Auto-generated destructor stub
}


int MasterRequestHandler::Run(const HTTPRequest *request, HTTPResponse *response) {
	response->SetContentType(HTTPServer::CONTENT_TYPE_JSON);
	Json::StyledWriter *writer = new Json::StyledWriter();
	Json::Value root;

	string url = request->Url();

	if(std::count(url.begin(), url.end(), '/') > 1){
		// Split the URL
		const char *pch = std::strtok((char*)url.data(), "/" );
		pch = std::strtok(NULL, "/" );
		url = pch;
	}

	if(url.compare("activateScript") == 0){
		ManageScript (request, root, true) ;
        }
        else if (url.compare("desactivateScript") == 0){
		ManageScript (request, root, false) ;
        }
	else{
		SetResponse (root, "ko", "unknown action") ;
	}
		
	response->Append(writer->write(root));
	return response->Send();

}
void MasterRequestHandler::SetResponse (Json::Value & root, const char * result, const char * message)
{
	if (result) root["result"] = result;
	if (message) root["message"] = message;
	;
}

void MasterRequestHandler::ManageScript (const HTTPRequest *request, Json::Value & root, bool status)
{
	string script_file = request->GetParameter("script_file");
	//string sender = request->GetParameter("sender");

	if (script_file.length() == 0) {
		SetResponse (root, "ko", " parameter <target> is missing") ;
	//} else if (sender.length() == 0) {
	//	SetResponse (root, "ko", " parameter <sender> is missing") ;
	}else if (status == true){
		int result;
		ActivateScript (script_file.c_str(), &result);
		SetResponse (root, "ok", NULL) ;
	}else {
                int result;
		DesactivateScript (script_file.c_str(), &result);
		SetResponse (root, "ok", NULL) ;
        }
}



int MasterRequestHandler::ActivateScript(string script_file, int* result)
{
	YDLE_DEBUG << "enter in ActivateScript " << script_file  <<std::endl;

  	//send signal NBSEND time
	for (int i=0; i<NBSEND; i++)
    {
	string scripts_dir = PARAM_STR("lua-scripts.scripts_dir");
        string file_in = scripts_dir + "/" + script_file + ".lua" ;
        string tmpfile = scripts_dir + "/tmp.lua" ;
        std::ifstream file_in_stream (file_in.c_str() ) ; // On essaye d'ouvrir le fichier
        std::ofstream tmpfile_stream (tmpfile.c_str()); 
	
        file_in_stream.seekg(0,std::ios::beg);
	string line ;
	getline(file_in_stream, line);
      
	line.replace(14,5,"true");
	tmpfile_stream << line << std::endl;
	while(std::getline(file_in_stream, line))
	{
		tmpfile_stream << line << std::endl;
	}
	file_in_stream.close();
	tmpfile_stream.close();
	std::remove(file_in.c_str());
        string file_out = scripts_dir + "/" + script_file + ".lua" ;
	std::rename(tmpfile.c_str(),file_out.c_str());
        //Copie dans reload
        std::ifstream src( file_out.c_str() ,std::ios::binary);
        string file_reload = scripts_dir + "/reload/" + script_file + ".lua" ;
        std::ofstream dst( file_reload.c_str() ,std::ios::binary);
        dst<<src.rdbuf();
        src.close();
        dst.close();
        //
        
            //_pScripts->ReloadScript (script_file);
    }

	*result = 1;
	return 1;
}
int MasterRequestHandler::DesactivateScript(string script_file, int* result)
{
	YDLE_DEBUG << "enter in DesactivateScript " << script_file  <<std::endl;

  	//send signal NBSEND time
	for (int i=0; i<NBSEND; i++)
    {
	string scripts_dir = PARAM_STR("lua-scripts.scripts_dir");
        string file_in = scripts_dir + "/" + script_file + ".lua" ;
        string tmpfile = scripts_dir + "/tmp.lua" ;
        std::ifstream file_in_stream (file_in.c_str() ) ; // On essaye d'ouvrir le fichier
        std::ofstream tmpfile_stream (tmpfile.c_str()); 
	
        file_in_stream.seekg(0,std::ios::beg);
	string line ;
	getline(file_in_stream, line);
        
	line.replace(14,4,"false");
	tmpfile_stream << line << std::endl;
	while(std::getline(file_in_stream, line))
	{
		tmpfile_stream << line << std::endl;
	}
	file_in_stream.close();
	tmpfile_stream.close();
	std::remove(file_in.c_str());
        string file_out = scripts_dir + "/" + script_file + ".lua" ;
	std::rename(tmpfile.c_str(),file_out.c_str());
                //Copie dans reload
        std::ifstream src( file_out.c_str() ,std::ios::binary);
        string file_reload = scripts_dir + "/reload/" + script_file + ".lua" ;
        std::ofstream dst( file_reload.c_str() ,std::ios::binary);
        dst<<src.rdbuf();
        src.close();
        dst.close();
        //
          //  _pScripts->ReloadScript (script_file);
		//nanosleep(&WaitEndCmommand,NULL); // Delay 400 mili. this prevend lost frame if multi transmit
    }

	*result = 1;
	return 1;
}
 
} 
/* namespace WebServer */
        