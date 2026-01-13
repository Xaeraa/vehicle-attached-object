# Vehicle Attached Object
new natives to attached vehicle object like player attached object.
this include not 100% accurate like Player Attached Object.

## Dependecy
    [Streamer Plugin](https://github.com/samp-incognito/samp-streamer-plugin/releases)

## How to Install?

### Legacy Method
- 1. Download a_vehicleobject.inc to your **Pawno > Include** directory
- 2. Write **#include <a_vehicleobject>** to your gamemode, example:
```pawn
#include <a_vehicleobject>
```
- 3. Place **#include <a_vehicleobject>** below of streamer.inc
```pawn
#include <a_samp>
#include <streamer>
#include <a_vehicleobject>
```
- 4. Enjoy the Modified Vehicle Attached Object 

### Native
```pawn
    IsVehicleAttachedObjectSlotUsed(vehicleid, index)
	SetVehicleAttachedObject(vehicleid, index, modelid, Float:offset_x= 0.0, Float:offset_y= 0.0, Float:offset_z= 0.0, Float:rotation_x= 0.0, Float:rotation_y= 0.0, Float:rotation_z= 0.0, materialColour1 = 0, materialColour2 = 0) 
    RemoveVehicleAttachedObject(vehicleid, index)
	GetInfoVehicleAttachedObject(vehicleid, index, &modelid, &Float:offset_x, &Float:offset_y, &Float:offset_z, &Float:rotation_x, &Float:rotation_y, &Float:rotation_z, &materialColour1 = 0, &materialColour2 = 0)
    EditVehicleAttachedObject(vehicleid, objectid)
```

### Callback
```pawn
    OnPlayerEditVehicleAttachedObject(playerid, vehicleid, response, index, modelid, Float:offset_x, Float:offset_y, Float:offset_z, Float:rotation_x, Float:rotation_y, Float:rotation_z)
```