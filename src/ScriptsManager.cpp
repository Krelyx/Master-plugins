/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "ScriptsManager.h"
#include "logging.h"
#include <iostream>
#include "Dir.h"
#include "SettingsParser.h"
using namespace ydle ;
using namespace std ;

void ScriptsManager::Init (Kernel * k)
{
//	memset (_nodes, 0, sizeof (_nodes)) ;

	// search for node affection in config file
try {
/*	SettingsParser * pSettings = SettingsParser::Instance() ;
	// get number of configured nodes
	int nbNodes = pSettings->Int("nodes.number") ;
	// parse each configured node
	for (int i = 0 ; i < nbNodes; i++) {
		std::stringstream ss;
		ss << "nodes.node" << i+1 ;

		string node = pSettings->Str(ss.str()) ;
		printf ("node %d : <%s>=<%s>\n", i+1, ss.str().c_str(), node.c_str()) ;
		string nomPlugin ;
		tNodesList listNodes ;
		// try to parse node plugin name and list of nodes related
		if (decoder (node, nomPlugin, listNodes)) {
			printf ("\t : node<%s>  nomPlugin<%s>  \n", node.c_str(), nomPlugin.c_str());
			// try to get node plugin pointer from its name
			INode * pNode = k->Node (nomPlugin) ;
			// if node exists
			if (pNode != NULL) {
				printf ("\t\t : ") ;
				// for each node listed, memorize its plugin
				for (tNodesList::iterator it = listNodes.begin(); it != listNodes.end(); it++) {
					int numNode = *it ;
					printf ("%d ", numNode) ;
					if (_nodes[numNode] != NULL) {
						YDLE_FATAL << "NodesManager::Init FAILED, node " << nomPlugin << " num:" 
							<< numNode << " already set !!!" ; 
					}
					else {
						_nodes[numNode] = pNode ;
					}
				}
				printf ("\n") ;
			}
			else {
				YDLE_FATAL << "NodesManager::Init FAILED, node " << nomPlugin << " unknown !!!" ; 
			}
		}

	}
#ifdef DBG_NODES_CONFIG
	for (int i = 0 ; i < NB_NODES; i++) {
		if (_nodes[i] != NULL) {
			printf ("i:%d node<%s>\n", i, _nodes[i]->Name().c_str());
		}
	}
#endif // DBG_NODES_CONFIG
*/
   // memorize list of protocols

        pFeatures = &(k->Features()) ;

}
catch (const runtime_error & e)  {
	YDLE_FATAL << "ScriptsManager::Init FAILED !!! : " << e.what() ;
}
}
int	ScriptsManager::ReloadScript (string script_file)
{
    YDLE_DEBUG <<  script_file  <<std::endl;
    string script = PARAM_STR("lua-scripts.scripts_dir")+ "/"+ script_file + ".lua" ;
    for( Kernel::FeatureList::iterator it = pFeatures->begin(); it != pFeatures->end(); ++it) {
		IFeature * feature = *it ;
        //        IFeature  feature = "lua-script";
                feature->AddScript (script.c_str()) ;
		printf ("\tFeature : %s:AddScript \n", feature->Name().c_str()) ;
        //intf("\t Test \n");
        }
    
	return 1 ;
}