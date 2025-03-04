
package inet.node.LEACHnode;

import inet.node.inet.AdhocHost;
import inet.routing.leach.Leach;
import inet.node.inet.ManetRouter;
module LEACHnode extends AdhocHost
{
    @display("bgb=1666.404,1029.6481");
    submodules:
        LEACHnode: Leach {
            @display("p=825,226");
        }
    connections:
        LEACHnode.ipOut --> tn.in++;
        LEACHnode.ipIn <-- tn.out++;

}
