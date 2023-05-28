# splitflap
A modular splitflap display system

## Project Goals
I wanted to create a splitflap display that used primarily 3D-printed parts and minimal third-party hardware. Given the increased availability of multi-material 3D-printing solutions, the overwhelming majority of parts for these splitflap display modules can be manufactured at home with minimal additional work beyond the printing itself. 

Beyond that, I wanted to use off-the-shelf electronics that were cheap and easy to source from both Amazon and AliExpress. This allows most people to be able to build these at home, get fast shipping through Amazon if building a sign at low scale, and low pricing at large scale through AliExpress if building a larger display. 

In the future a custom PCB would be ideal, but for now, the time it takes to hand-solder the components is a small fraction of the time it takes to print them, so the production timeline bottleneck will not be a lack of custom PCB unless you have a printer farm.

## Design Considerations

### Encapsulated
Each module has an entirely internalized microcontroller, which includes the driver for the motor and the limit switch for homing purposes. The intention is that if a module fails, it can be removed and either repaired or replaced with no firmware updates required. Each module is a soverign citizen and can communicate unidirectonally with the neighboring modules. 

### Extensible
The entire display is agnostic of size. You can add any number of modules to the chain, and as long as the data provided has enough coverage for each module, they will all respond in kind. Closing the RX/TX loop will enable a discovery process so the header controller can determine the length of the chain, but that is not strictly necessary for base functionality. 
