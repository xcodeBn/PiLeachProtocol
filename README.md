# LEACH Protocol Simulation in OMNeT++ with INET

This project implements the **Low-Energy Adaptive Clustering Hierarchy (LEACH)** protocol, a classic hierarchical routing protocol for wireless sensor networks (WSNs), using OMNeT++ and the INET framework. The code simulates a distributed clustering algorithm where sensor nodes self-organize into clusters, elect cluster heads (CHs) probabilistically, and transmit data to a base station (BS) via CHs to optimize energy consumption.

## Requirements

- OMNeT++ 6.0
- INET Framework 4.5

## Installation

1. Make sure you have OMNeT++ 6.0 and INET 4.5 installed on your system.
   
2. Clone this repository:
   ```
   git clone https://github.com/xcodebn/PiLeachProtocol.git
   ```
   
3. **Important**: Copy the code directories to the correct INET folders:
   - Copy the `leach` folder into `inet/routing/`
   - Copy the `leachNode` folder into `inet/node/`

4. Import the project into your OMNeT++ IDE or build it from command line:
   ```
   cd path/to/inet
   make makefiles
   make
   ```

## Overview

The implementation consists of three main components:

1. **Leach Class**: Defines the behavior of sensor nodes in the network, including CH election, cluster formation, and data transmission.
   
2. **LeachBS Class**: Implements the base station functionality, responsible for receiving aggregated data from CHs and acting as the sink node for the entire network.
   
3. **LeachNode**: A specialized node type that incorporates the LEACH protocol for WSN simulations.

Key features include:

- **Cluster Head Election**: Nodes elect themselves as CHs based on a probabilistic threshold.
- **Dynamic Clustering**: Non-cluster head (NCH) nodes join CHs based on received signal strength.
- **TDMA Scheduling**: CHs assign time slots to their cluster members for data transmission.
- **Data Transmission**: NCHs send data to CHs, which aggregate and forward it to the BS.
- **Visualization**: Nodes visually update their icons in the simulation GUI to distinguish CHs from NCHs.

This implementation adheres to the **classic LEACH** algorithm, as originally proposed by Heinzelman et al., with a distributed approach and no centralized control from the BS.

## Project Structure

```
PiLeachProtocol/
├── inet/routing/leach/	    # Directory to copy to inet/routing/
│   ├── Leach.cc           # Main LEACH protocol implementation for sensor nodes
│   ├── Leach.h            # Header file for the LEACH module
│   ├── LeachBS.cc         # Base station implementation
│   ├── LeachBS.h          # Header file for the base station module
│   ├── Leach.ned          # Network description file for LEACH
│   └── LeachPacket.msg    # Message definitions for LEACH
├── inet/node/leachNode/             # Directory to copy to inet/node/
│   ├── LEACHnode.ned      # Node model with LEACH protocol
│   └── LEACHbs.ned # Base station node model
├── simulations/
│   ├── LeachNetwork.ned   # Network topology definition
│   ├── omnetpp.ini        # Simulation configuration file
│   ├── address.xml        # Network addressing configuration
│   └── README.md          # Instructions for running the simulation
├── results/               # Directory for simulation results
├── LICENSE                # License information
└── README.md              # This file
```

## Component Details

### Leach Module

The Leach module (`Leach.cc`) handles:
- Self-election as a cluster head based on probabilistic threshold
- Advertisement of CH status
- Cluster formation
- TDMA schedule creation and distribution
- Data collection from cluster members
- Data aggregation
- Forwarding aggregated data to the base station

### LeachBS Module

The LeachBS module (`LeachBS.cc`) handles:
- Receiving advertisements from CHs
- Recording network topology information
- Collecting aggregated data from all CHs
- Processing and analyzing network performance
- Tracking energy consumption across the network
- Serving as the ultimate destination for all sensor data

### Network Components

- **LeachNode**: Standard sensor nodes that can become either cluster heads or cluster members
- **LeachBaseStation**: A specialized node with the LeachBS module that serves as the network sink

## Usage

### Running the Simulation

1. Open the OMNeT++ IDE.
2. Import the INET project with your added LEACH modules.
3. Create a new simulation project.
4. **Important**: Add inet4.5 to your referenced projects in project properties.
5. Copy the files in the inet directory to their respective destinations inside the inet project (src/inet).
6. Build your inet project to incorporate the LEACH modules.
7. Copy the files from the `simulations` directory to your project.
8. Build your simulation project.
9. Right-click on the `omnetpp.ini` file and select "Run As" > "OMNeT++ Simulation".
10. Alternatively, run from command line:
    ```
    cd simulations
    ../src/leach -c LeachSimulation -n ..
    ```

### Configuration

The main simulation parameters can be configured in the `omnetpp.ini` file:

```ini
[General]
network = LeachNetwork
sim-time-limit = 300s

# Address configuration
*.configurator.config = xmldoc("address.xml")

# Node configuration
*.host*.typename = "LEACHnode"
*.host*.hasStatus = true
*.host*.LEACHnode.clusterHeadPercentage = 0.5

# Base station configuration
*.baseStation.typename = "LEACHbs"
```

### Network Addressing

The `address.xml` file configures IP addressing for the network:

```xml
<config>
  <interface hosts="host*" names="wlan0" address="10.0.0.x" netmask="255.255.255.0"/>
  <interface hosts="baseStation" names="wlan0" address="10.0.0.100" netmask="255.255.255.0"/>
</config>
```

## Protocol Operation

The LEACH protocol operates in rounds, with each round consisting of:

1. **Setup Phase**:
   - Cluster head election based on probabilistic threshold
   - Cluster formation with remaining nodes joining nearest CH
   - TDMA schedule creation by CHs

2. **Steady-State Phase**:
   - Data transmission from NCHs to CHs according to TDMA schedule
   - Data aggregation at CHs
   - Aggregated data transmission from CHs to BS

## Energy Model

The simulation tracks energy consumption for:
- Transmission (based on distance and packet size)
- Reception
- Idle listening
- Processing

Nodes display their remaining energy level in the simulation GUI.

## Base Station Functionality

The base station (implemented in `LeachBS.cc`) serves several key functions:
- Acts as the central data collection point
- Tracks the formation of clusters in the network
- Records which nodes are serving as CHs in each round
- Collects statistics on network performance
- Does not have energy constraints like regular sensor nodes
- Provides a global view of the network state for analysis

## Visualization

During the simulation:
- Cluster heads are highlighted with a special icon
- Energy levels are displayed graphically
- Communication patterns are visualized with arrows
- Coverage areas of clusters are displayed as circles

## Performance Metrics

The simulation collects the following metrics:
- Network lifetime
- Energy consumption per round
- Number of alive nodes over time
- Data delivery ratio
- End-to-end delay
- Number of clusters per round

Results are stored in the `results/` directory and can be visualized using OMNeT++'s Analysis Tool.

## Analyzing Results

To analyze the simulation results:
1. Run the simulation with data collection enabled
2. Open OMNeT++ Analysis Tool (Tools → Analysis Tool)
3. Add your result files (.vec and .sca files)
4. Create line charts or bar graphs for metrics of interest
5. Compare performance with different parameter settings

Key metrics to examine:
- Average node lifetime (time until first node dies)
- Network lifetime (time until network becomes disconnected)
- Energy efficiency (data packets per unit of energy)
- Cluster distribution (average nodes per cluster)

## Customization

To customize the LEACH protocol implementation:

1. Modify the probability threshold for CH election in `omnetpp.ini`
2. Adjust energy model parameters in `Leach.cc`
3. Change the network topology in `LeachNetwork.ned`
4. Implement additional routing features in `Leach.cc` or `LeachBS.cc`

## Common Issues and Troubleshooting

- **Compilation errors**: Make sure INET is correctly built after adding the LEACH modules
- **Module not found**: Verify that the module paths in NED files match the physical location of the files in the INET directory structure
- **Simulation crashes**: Check energy parameter configuration, as extremely low values might cause premature node death
- **Base station issues**: Ensure the LeachBS module is properly configured in the network
- **Network connectivity problems**: Verify that address.xml is correctly configured and that all nodes are within communication range

## Extending the Implementation

To extend this implementation with additional features:
1. To add multi-hop capabilities, modify the `sendToBS()` method in `Leach.cc`
2. For adaptive CH probability, implement a function that adjusts `probabilityThreshold` based on remaining energy
3. To implement secure LEACH, add authentication fields to `LeachPacket.msg`
4. To enhance base station functionality, extend the `LeachBS.cc` with additional data processing capabilities

## Implementation Details

### Cluster Head Selection Algorithm

The CH selection is implemented according to the following formula:

```
T(n) = { (p / (1 - p * (r mod (1/p)))), if n ∈ G
          0,                            otherwise
```

Where:
- p: desired percentage of cluster heads
- r: current round number
- G: set of nodes that have not been cluster heads in the last 1/p rounds

### Energy Consumption Model

The energy consumption follows the first-order radio model:
- Transmitting: ETx = Eelec * k + Eamp * k * d²
- Receiving: ERx = Eelec * k

Where:
- Eelec: energy consumed by the transceiver electronics
- Eamp: energy consumed by the transmitter amplifier
- k: message length in bits
- d: distance between sender and receiver

## License

This project is licensed under the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1 - see the LICENSE file for details.

## Acknowledgments

- W. R. Heinzelman, A. Chandrakasan, and H. Balakrishnan, "Energy-efficient communication protocol for wireless microsensor networks," in Proceedings of the 33rd Annual Hawaii International Conference on System Sciences, 2000.
- The OMNeT++ and INET framework communities

## Contact

For questions or support, please create an issue in the GitHub repository: https://github.com/xcodebn/PiLeachProtocol