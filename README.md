
Adding 802.11aa support to NS-3
================================

## How to
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
