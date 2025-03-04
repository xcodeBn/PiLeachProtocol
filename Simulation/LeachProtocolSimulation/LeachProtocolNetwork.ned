
package samples.LeachProtocolSimulation; //dont forget to change this incase to make it work in your project;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.contract.INetworkNode;
import inet.node.inet.SensorNode;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import inet.physicallayer.wireless.apsk.packetlevel.ApskScalarRadioMedium;

network LeachProtocolNetwork
{
    parameters:
        int numNodes;
        @display("bgb=1209.63,909.50995;bgg=100,1,grey95");
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);

        @statistic[residualEnergyCapacity](source="energyStorage"; record=count);

        @signal[subIntervalTot](type="int");
        @statistic[rounds](title="num of rounds"; source="subIntervalTot"; record=vector?,counts?);


    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            @display("p=536.19,42.089996");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=512.39996,181.17");
        }
        radioMedium:  ApskScalarRadioMedium {
            @display("p=512.39996,289.13998");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=512.39996,441.02997");
        }

        baseStation: <default("ManetRouter")> like INetworkNode {
            @display("p=153.38399,381.63397;i=misc/sensorgateway");
        }


        host[numNodes]: <default("ManetRouter")> like INetworkNode {
            @display("i=misc/sensor2;p=180.77399,472.934");
        }
//        hostC: <default("WirelessHost")> like INetworkNode {
//            @display("i=misc/sensor2;p=233.72798,312.24597");
//        }
//        hostA: <default("WirelessHost")> like INetworkNode {
//            @display("i=misc/sensor2;p=138.776,483.88998");
//        }

}


