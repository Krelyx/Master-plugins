
#include "Kernel.h"
#include "Float.h"

namespace ydle {

class NodeTeleInfo : public INode
{
public:
	typedef struct {
		long index_base ;
		float16 iinst ;
		int16_t papp ;
	} sTeleInfoData  ;
	NodeTeleInfo () { ;}
	std::string Name () { return "TeleInfo" ; }
	virtual void FormatCmd (int target, int sender, int param, int cmd) ;
	virtual int GetData (Frame_t *, tNodeDataList & list) ;
} ;
} ;	 // namespace ydle
extern "C" int LoadPlugins (ydle::Kernel &) ;
