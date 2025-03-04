
import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;
import inet.networklayer.contract.ipv4.Ipv4Address;

cplusplus {{
    #include <vector>
    #include "inet/common/INETDefs.h"
    #include "Leach.h"
    #include "inet/networklayer/contract/ipv4/Ipv4Address.h"
    using namespace std;
    using namespace inet;
    
}}

namespace inet;

enum LeachPktType {
    CH = 1;
    ACK = 2;
    SCH = 3;
    DATA = 4;
    BS = 5;
}

class ScheduleEntry extends cObject {
    Ipv4Address nodeAddress;
    double TDMAdelay;
}

class LeachControlPkt extends FieldsChunk {
	LeachPktType packetType = static_cast<LeachPktType>(-1); 
	Ipv4Address srcAddress;
	string fingerprint;
	
	ScheduleEntry schedule[];
}

class LeachDataPkt extends LeachControlPkt {
    double temperature;
	double humidity;
}

class LeachBSPkt extends LeachControlPkt {
    Ipv4Address CHAddr;
}	

class LeachAckPkt extends LeachControlPkt {
    
}

class LeachSchedulePkt extends LeachControlPkt { 
	
}





