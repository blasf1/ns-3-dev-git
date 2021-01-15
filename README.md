
802.11aa support for NS-3
================================
This fork extends the NS-3 discrete-event network simulator to add support for the different multicast transmission modes included in the IEEE 802.11aa standard.

More information about NS-3 can be found at https://www.nsnam.org

## Building and Running NS-3
For full installation instructions, refer to the original [README.md](https://github.com/blasf1/ns-3-dev-git/blob/master/README.md).

## Using 802.11aa standard in NS-3
Create a MulticastMode object and initialize it with the mode you want to use and the number of retries in the case of GCR-UR:
```c++
Ptr<MulticastMode> mode(new MulticastMode());
mode->SetMode(MulticastMode::ModesList::GCRUR);
mode->SetRetries(3);
 ```
Modes currently available are:
* GCR-UR: 

```c++
MulticastMode::ModesList::GCRUR
```
* DMS:

```c++
MulticastMode::ModesList::DMS
```
You will need to register the clients connected to the multicast group:

```c++
mode->Register(GroupMacAddress, StationMacAddress);
```
Then, add a pointer to the mode object you have just created to the ApWifiMac in use and install the mac into the AP device:

```c++
WifiHelper wifi;
WifiMacHelper mac;
mac.SetType("ns3::ApWifiMac", 
					"MulticastMode", PointerValue(mode));
auto apDevice = wifi.Install(phy, mac, apNode);
```

## Acknowledgments
This project is part of the PhD thesis of Blas Gómez Mora, whose advisors are Antonio Garrido, José Villalón and Estefanía Coronado. Blas Gomez is funded by Universidad de Castilla-La Mancha and the European Union [Grant 2019-PREDUCLM-10921].
