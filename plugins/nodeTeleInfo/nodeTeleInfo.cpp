
#include "nodeTeleInfo.h"
#include "DataAccess.h"

using namespace ydle ;
using namespace std ;


void NodeTeleInfo::FormatCmd (int target, int sender, int param, int cmd)
{
}

int NodeTeleInfo::GetData (Frame_t *frame, tNodeDataList & l)
{
	uint8_t * pData = frame->data ;
	
	sTeleInfoData * p = (sTeleInfoData *)pData ;
//	printf ("NodeTeleInfo[%s]::GetData : %#02x %#2x %#02x %#02x\n", Name().c_str()
//			, pData[0] , pData[1] , pData[2] , pData[3]) ;

	printf ("\t\t\t :  index_compteur=%#0lx  Iinst=%#0x	Papp=%#0x \n", p->index_base, p->iinst, p->papp) ;
	sNodeData nodeData ;
	nodeData.type = "index_base" ;
	nodeData.val = (float)p->index_base ;
	SetVal (frame->sender,  "index_base", nodeData.val) ;

	printf ("NodeTeleInfo[%s]::GetData : index_compteur=%g\n", Name().c_str(), nodeData.val) ;
	l.push_back (nodeData) ;
	nodeData.type = "I_inst" ;
//FETS		nodeData.val = Float16To32(p->humidity) ;
	nodeData.val = Float16To32(p->iinst) ;
	SetVal (frame->sender,  "I_inst", nodeData.val) ;
	printf ("NodeTeleInfo[%s]::GetData : I_inst=%g\n", Name().c_str(), nodeData.val) ;
	l.push_back (nodeData) ;

	nodeData.type = "P_app" ;
	nodeData.val = (float)p->papp ;
	SetVal (frame->sender,  "P_app", nodeData.val) ;

	printf ("NodeTeleInfo[%s]::GetData : P_app=%g\n", Name().c_str(), nodeData.val) ;
	l.push_back (nodeData) ;

	return l.size() ;
}




int	LoadPlugins (Kernel & k)
{
//FETS		printf ("dht11::LoadPlugins  %d\n", __LINE__);
	k.RegisterNode (new NodeTeleInfo) ;
	return 1 ;
}

