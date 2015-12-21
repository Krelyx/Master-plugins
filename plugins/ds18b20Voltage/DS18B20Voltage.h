
#include "Kernel.h"
#include "Float.h"

namespace ydle {

class NodeDS18B20Voltage : public INode 
{
public:
	typedef struct {
		float16	temperature ;
		float16	voltage ;
	} sDS18B20VoltageData  ;
	NodeDS18B20Voltage () { ;}
	std::string Name () { return "DS18B20Voltage" ; }
	virtual void FormatCmd (int target, int sender, int param, int cmd) ;
	virtual int GetData (Frame_t *, tNodeDataList & list) ;
} ;
} ;	 // namespace ydle
extern "C" int LoadPlugins (ydle::Kernel &) ;
