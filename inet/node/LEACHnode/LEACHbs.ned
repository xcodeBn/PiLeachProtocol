

package inet.node.LEACHnode;

import inet.node.inet.AdhocHost;
import inet.routing.leach.LeachBS;
import inet.node.inet.ManetRouter;
module LEACHbs extends AdhocHost {
    submodules:
        LEACHbs: LeachBS {
            @display("p=825,226");
        }
    connections:
        LEACHbs.ipOut --> tn.in++;
        LEACHbs.ipIn <-- tn.out++;
        
}
