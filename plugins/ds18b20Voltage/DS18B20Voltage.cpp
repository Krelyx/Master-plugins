
#include "DS18B20Voltage.h"
#include "DataAccess.h"

using namespace ydle;
using namespace std;

void NodeDS18B20Voltage::FormatCmd(int target, int sender, int param, int cmd) {
}

int NodeDS18B20Voltage::GetData(Frame_t *frame, tNodeDataList & l) {
    uint8_t * pData = frame->data;
    sDS18B20VoltageData * p = (sDS18B20VoltageData *) pData;
    printf("NodeDS18B20Voltage[%s]::GetData : %#02x %#2x %#02x %#02x\n", Name().c_str()
            , pData[0], pData[1], pData[2], pData[3]);

    //printf ("\t\t\t : f16  temp=%#0x  h=%#0x  [%d  %d]\n", p->temperature, p->humidity, p->temperature, p->humidity) ;
    sNodeData nodeData;

    nodeData.type = "temperature";
    nodeData.val = Float16To32(p->temperature);
    SetVal(frame->sender, "temperature", nodeData.val);
    printf("NodeDS18B20Voltage[%s]::GetData : temperature=%g\n", Name().c_str(), nodeData.val);
    l.push_back(nodeData);

    nodeData.type = "voltage";
    nodeData.val = Float16To32(p->voltage);
    SetVal(frame->sender, "voltage", nodeData.val);
    printf("NodeDS18B20Voltage[%s]::GetData : voltage=%g\n", Name().c_str(), nodeData.val);
    l.push_back(nodeData);

    return l.size();
}

int LoadPlugins(Kernel & k) {
    //FETS		printf ("dht11::LoadPlugins  %d\n", __LINE__);
    k.RegisterNode(new NodeDS18B20Voltage);
    return 1;
}

