/*
    ------------------ Extended Vehicle Attached Object ------------------
    those dont know, Attaching Object to Vehicle doesn't same like Attaching Object to Player.
    So, in this include i've replicated Attaching Object to Player for Vehicle.

    remember! this is just replicated, and have any lack.

    By : Fann / Xaeraa

    ------ [ Native ] ------
	IsVehicleAttachedObjectSlotUsed(vehicleid, index)
	SetVehicleAttachedObject(vehicleid, index, modelid, Float:offset_x= 0.0, Float:offset_y= 0.0, Float:offset_z= 0.0, Float:rotation_x= 0.0, Float:rotation_y= 0.0, Float:rotation_z= 0.0, materialColour1 = 0, materialColour2 = 0) 
    RemoveVehicleAttachedObject(vehicleid, index)
	GetInfoVehicleAttachedObject(vehicleid, index, &modelid, &Float:offset_x, &Float:offset_y, &Float:offset_z, &Float:rotation_x, &Float:rotation_y, &Float:rotation_z, &materialColour1 = 0, &materialColour2 = 0)
    EditVehicleAttachedObject(vehicleid, objectid)

	------ [ Callback ] -----
	OnPlayerEditVehicleAttachedObject(playerid, vehicleid, response, index, modelid, Float:offset_x, Float:offset_y, Float:offset_z, Float:rotation_x, Float:rotation_y, Float:rotation_z)
*/

#if defined _inc_vehicle_attached_object 
    #endinput
#endif
#define _inc_vehicle_attached_object

#if !defined _streamer_included
    #error [ADM] need streamer for running. (github.com/incognito/samp-streamer)
#endif

#if !defined MAX_VEHICLEOBJECT_INDEX
    #define MAX_VEHICLEOBJECT_INDEX 10
#endif

forward OnPlayerEditVehicleAttachedObject(playerid, vehicleid, response, index, modelid, Float:offset_x, Float:offset_y, Float:offset_z, Float:rotation_x, Float:rotation_y, Float:rotation_z);

#define VO:: FannVehicleObject_
enum VO::enum_data
{
	bool:VO::Exist,
    VO::Model,
    Float:VO::Pos[6],
    VO::Material[2],
    STREAMER_TAG_OBJECT:VO::TempObject,
    STREAMER_TAG_OBJECT:VO::Object
};

static 
    VO::Data[MAX_VEHICLES][MAX_VEHICLEOBJECT_INDEX][VO::enum_data],
    STREAMER_TAG_OBJECT:VO::playerEditObject[MAX_PLAYERS],
    VO::playerIndex[MAX_PLAYERS],
    VO::playerVehicle[MAX_PLAYERS]
;

static VO::ResetVehicleAttachedObject(vehicleid, index)
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] ResetVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(IsValidDynamicObject(VO::Data[vehicleid][index][VO::Object]))
        DestroyDynamicObject(VO::Data[vehicleid][index][VO::Object]);

    if(IsValidDynamicObject(VO::Data[vehicleid][index][VO::TempObject]))
        DestroyDynamicObject(VO::Data[vehicleid][index][VO::TempObject]);

	VO::Data[vehicleid][index][VO::Exist] = false;
    VO::Data[vehicleid][index][VO::Model] = 0;
    VO::Data[vehicleid][index][VO::TempObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    VO::Data[vehicleid][index][VO::Object] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

    for(new fan = 0; fan < 6; fan++)
    {
        VO::Data[vehicleid][index][VO::Pos][fan] = 0.0;
        if(fan < 2) VO::Data[vehicleid][index][VO::Material][fan] = 0;
    }
    return 1;
}

stock bool:VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index) 
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] IsVehicleAttachedObjectSlotUsed(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return false;
    }

    return VO::Data[vehicleid][index][VO::Exist];
}

stock VO::SetVehicleAttachedObject(vehicleid, index, modelid, Float:offset_x= 0.0, Float:offset_y= 0.0, Float:offset_z= 0.0, Float:rotation_x= 0.0, Float:rotation_y= 0.0, Float:rotation_z= 0.0, materialColour1 = 0, materialColour2 = 0)
{
    if(!IsValidVehicle(vehicleid)) return 0;

    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] SetVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index))
        VO::ResetVehicleAttachedObject(vehicleid, index);

	VO::Data[vehicleid][index][VO::Exist] = true;
    VO::Data[vehicleid][index][VO::Model] = modelid;
    VO::Data[vehicleid][index][VO::Pos][0] = offset_x;
    VO::Data[vehicleid][index][VO::Pos][1] = offset_y;
    VO::Data[vehicleid][index][VO::Pos][2] = offset_z;
    VO::Data[vehicleid][index][VO::Pos][3] = rotation_x;
    VO::Data[vehicleid][index][VO::Pos][4] = rotation_y;
    VO::Data[vehicleid][index][VO::Pos][5] = rotation_z;
    VO::Data[vehicleid][index][VO::Material][0] = materialColour1;
    VO::Data[vehicleid][index][VO::Material][1] = materialColour2;

    VO::Data[vehicleid][index][VO::Object] = CreateDynamicObject(modelid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::Object], 0, modelid, "none", "none", materialColour1);
    SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::Object], 1, modelid, "none", "none", materialColour2);
    AttachDynamicObjectToVehicle(VO::Data[vehicleid][index][VO::Object], vehicleid, offset_x, offset_y, offset_z, rotation_x, rotation_y, rotation_z);
    return 1;
}

stock VO::RemoveVehicleAttachedObject(vehicleid, index)
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] SetVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(!VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index)) return 0;

    VO::ResetVehicleAttachedObject(vehicleid, index);
    return 1;
}

stock VO::GetInfoVehicleAttachedObject(vehicleid, index, &modelid, &Float:offset_x, &Float:offset_y, &Float:offset_z, &Float:rotation_x, &Float:rotation_y, &Float:rotation_z, &materialColour1 = 0, &materialColour2 = 0)
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] SetVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(!VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index)) return 0;

    modelid = VO::Data[vehicleid][index][VO::Model];
    offset_x = VO::Data[vehicleid][index][VO::Pos][0];
    offset_y = VO::Data[vehicleid][index][VO::Pos][1];
    offset_z = VO::Data[vehicleid][index][VO::Pos][2];
    rotation_x = VO::Data[vehicleid][index][VO::Pos][3];
    rotation_y = VO::Data[vehicleid][index][VO::Pos][4];
    rotation_z = VO::Data[vehicleid][index][VO::Pos][5];
    materialColour1 = VO::Data[vehicleid][index][VO::Material][0];
    materialColour2 = VO::Data[vehicleid][index][VO::Material][1];
    return 1;
}

stock VO::EditVehicleAttachedObject(playerid, vehicleid, index)
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] EditVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(!VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index)) return 0;

    if(IsValidDynamicObject(VO::Data[vehicleid][index][VO::Object]))
        DestroyDynamicObject(VO::Data[vehicleid][index][VO::Object]);

    new Float:pos[4], Float:offset_pos[6], Float:last_pos[4], modelid;
    GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
    GetVehicleZAngle(vehicleid, pos[3]);

    if(!VO::GetInfoVehicleAttachedObject(vehicleid, index, modelid, offset_pos[0], offset_pos[1], offset_pos[2], offset_pos[3], offset_pos[4], offset_pos[5]))
		return 0;
    
	/*last_pos[0] = ((offset_pos[0] + pos[0]) * floatcos(pos[3], degrees)) + ((offset_pos[1] + pos[1]) * floatsin(pos[3], degrees));
    last_pos[1] = ((offset_pos[1] + pos[1]) * floatcos(pos[3], degrees)) - ((offset_pos[0] + pos[0]) * floatsin(pos[3], degrees));*/
	last_pos[0] = pos[0] + ((offset_pos[0] * floatcos(pos[3], degrees)) - (offset_pos[1] * floatsin(pos[3], degrees)));
	last_pos[1] = pos[1] + ((offset_pos[1] * floatcos(pos[3], degrees)) + (offset_pos[0] * floatsin(pos[3], degrees)));
    last_pos[2] = (offset_pos[2] + pos[2]);
    last_pos[3] = (offset_pos[5] + pos[3]);

	#if defined VO_DEBUG
		printf("Model ID: %d", modelid);
		printf("Vehicle Position X : %f", pos[0]);
		printf("Vehicle Position Y : %f", pos[1]);
		printf("Offset Position X : %f", offset_pos[0]);
		printf("Offset Position Y : %f", offset_pos[1]);
		printf("Last Position X : %f", last_pos[0]);
		printf("Last Position Y : %f", last_pos[1]);
	#endif

    VO::Data[vehicleid][index][VO::TempObject] = CreateDynamicObject(modelid, last_pos[0], last_pos[1], last_pos[2], offset_pos[3], offset_pos[4], last_pos[3]);
    SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::TempObject], 0, modelid, "none", "none", VO::Data[vehicleid][index][VO::Material][0]);
    SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::TempObject], 1, modelid, "none", "none", VO::Data[vehicleid][index][VO::Material][1]);

    VO::playerEditObject[playerid] = VO::Data[vehicleid][index][VO::TempObject];
    VO::playerIndex[playerid] = index;
    VO::playerVehicle[playerid] = vehicleid;
	Streamer_Update(playerid);
    EditDynamicObject(playerid, VO::Data[vehicleid][index][VO::TempObject]);
    return 1;
}

stock VO::CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, colour1 = -1, colour2 = -1, respawnDelay = 0, bool:addSiren = false)
{
    if(colour1 == -1)
        colour1 = random(255);
    
    if(colour2 == -1)
        colour2 = random(255);

    new ret = CreateVehicle(modelid, x, y, z, angle, colour1, colour2, respawnDelay, addSiren);

    if(IsValidVehicle(ret))
    {
        for(new fan = 0; fan < MAX_VEHICLEOBJECT_INDEX; fan++) VO::ResetVehicleAttachedObject(ret, fan);
    }
    return ret;
}

stock VO::DestroyVehicle(vehicleid)
{
    if(IsValidVehicle(vehicleid))
    {
        for(new fan = 0; fan < MAX_VEHICLEOBJECT_INDEX; fan++) VO::ResetVehicleAttachedObject(vehicleid, fan);
    }
    return DestroyVehicle(vehicleid);
}

public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(objectid == VO::playerEditObject[playerid])
    {
        switch(response)
        {
            case 0:
            {
                VO::playerEditObject[playerid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
                new index = VO::playerIndex[playerid], vehicleid = VO::playerVehicle[playerid];
                VO::playerIndex[playerid] = -1;
                VO::playerVehicle[playerid] = INVALID_VEHICLE_ID;

                new modelid = VO::Data[vehicleid][index][VO::Model];
                new Float:offset_x = VO::Data[vehicleid][index][VO::Pos][0];
                new Float:offset_y = VO::Data[vehicleid][index][VO::Pos][1];
                new Float:offset_z = VO::Data[vehicleid][index][VO::Pos][2];
                new Float:rotation_x = VO::Data[vehicleid][index][VO::Pos][3];
                new Float:rotation_y = VO::Data[vehicleid][index][VO::Pos][4];
                new Float:rotation_z = VO::Data[vehicleid][index][VO::Pos][5];
                new materialColour1 = VO::Data[vehicleid][index][VO::Material][0];
                new materialColour2 = VO::Data[vehicleid][index][VO::Material][1];

                VO::RemoveVehicleAttachedObject(vehicleid, index);
                VO::SetVehicleAttachedObject(vehicleid, index, modelid, offset_x, offset_y, offset_z, rotation_x, rotation_y, rotation_z, materialColour1, materialColour2);
                CallRemoteFunction("OnPlayerEditVehicleAttachedObject", "dddddffffff", playerid, vehicleid, 0, index, modelid, offset_x, offset_y, offset_z, rotation_x, rotation_y, rotation_z);
            }
            case 1:
            {
                VO::playerEditObject[playerid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
                new index = VO::playerIndex[playerid], vehicleid = VO::playerVehicle[playerid];
                VO::playerIndex[playerid] = -1;
                VO::playerVehicle[playerid] = INVALID_VEHICLE_ID;

                new modelid = VO::Data[vehicleid][index][VO::Model];
                new materialColour1 = VO::Data[vehicleid][index][VO::Material][0];
                new materialColour2 = VO::Data[vehicleid][index][VO::Material][1];

                VO::RemoveVehicleAttachedObject(vehicleid, index);

                new Float:new_pos[4], Float:final_pos[2], Float:veh_pos[4];
                GetVehiclePos(vehicleid, veh_pos[0], veh_pos[1], veh_pos[2]);
                GetVehicleZAngle(vehicleid, veh_pos[3]);

                new_pos[0] = x - veh_pos[0];
                new_pos[1] = y - veh_pos[1];
                new_pos[2] = z - veh_pos[2];
                new_pos[3] = rz - veh_pos[3];

                final_pos[0] = (new_pos[0] * floatcos(veh_pos[3], degrees)) + (new_pos[1] * floatsin(veh_pos[3], degrees));
                final_pos[1] = (new_pos[1] * floatcos(veh_pos[3], degrees)) - (new_pos[0] * floatsin(veh_pos[3], degrees));
                VO::SetVehicleAttachedObject(vehicleid, index, modelid, final_pos[0], final_pos[1], new_pos[2], rx, ry, new_pos[3], materialColour1, materialColour2);
                CallRemoteFunction("OnPlayerEditVehicleAttachedObject", "dddddffffff", playerid, vehicleid, 1, index, modelid, final_pos[0], final_pos[1], new_pos[2], rx, ry, new_pos[3]);
            }
			case 2:
			{
				CallRemoteFunction("OnPlayerEditVehicleAttachedObject", "dddddffffff", playerid, vehicleid, 2, index, modelid, final_pos[0], final_pos[1], new_pos[2], rx, ry, new_pos[3]);
			}
        }
    }
    #if defined FannVehicleObject_OnPlayerEditDynamicObject
        FannVehicleObject_OnPlayerEditDynamicObject(playerid, objectid, response, x, y, z, rx, ry, rz);
    #endif
    return 1;
}

public OnPlayerConnect(playerid)
{
	VO::playerEditObject[playerid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
    VO::playerIndex[playerid] = -1;
    VO::playerVehicle[playerid] = INVALID_VEHICLE_ID;

	#if defined FannVehicleObject_OnPlayerConnect
        FannVehicleObject_OnPlayerConnect(playerid);
    #endif
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(IsValidDynamicObject(VO::playerEditObject[playerid]))
	{
		new index = VO::playerIndex[playerid], vehicleid = VO::playerVehicle[playerid];

	    new modelid = VO::Data[vehicleid][index][VO::Model];
	    new Float:offset_x = VO::Data[vehicleid][index][VO::Pos][0];
	    new Float:offset_y = VO::Data[vehicleid][index][VO::Pos][1];
	    new Float:offset_z = VO::Data[vehicleid][index][VO::Pos][2];
	    new Float:rotation_x = VO::Data[vehicleid][index][VO::Pos][3];
	    new Float:rotation_y = VO::Data[vehicleid][index][VO::Pos][4];
	    new Float:rotation_z = VO::Data[vehicleid][index][VO::Pos][5];
	    new materialColour1 = VO::Data[vehicleid][index][VO::Material][0];
	    new materialColour2 = VO::Data[vehicleid][index][VO::Material][1];
	
	    VO::RemoveVehicleAttachedObject(vehicleid, index);
	    VO::SetVehicleAttachedObject(vehicleid, index, modelid, offset_x, offset_y, offset_z, rotation_x, rotation_y, rotation_z, materialColour1, materialColour2);
	
		VO::playerEditObject[playerid] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	    VO::playerIndex[playerid] = -1;
	    VO::playerVehicle[playerid] = INVALID_VEHICLE_ID;
	}

	#if defined FannVehicleObject_OnPlayerDisconnect
        FannVehicleObject_OnPlayerDisconnect(playerid, reason);
    #endif
	return 1;
}

#if defined _ALS_DestroyVehicle
    #undef DestroyVehicle 
#else
    #define _ALS_DestroyVehicle
#endif
#define DestroyVehicle FannVehicleObject_DestroyVehicle

#if defined _ALS_CreateVehicle
    #undef CreateVehicle 
#else
    #define _ALS_CreateVehicle
#endif
#define CreateVehicle FannVehicleObject_CreateVehicle

#if defined _ALS_OnPlayerEditDynObject
    #undef OnPlayerEditDynamicObject
#else
    #define _ALS_OnPlayerEditDynObject
#endif
#define OnPlayerEditDynamicObject FannVehicleObject_OnPlayerEditDynamicObject

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FannVehicleObject_OnPlayerConnect

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect FannVehicleObject_OnPlayerDisconnect

forward FannVehicleObject_OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz);
forward FannVehicleObject_OnPlayerConnect(playerid);
forward FannVehicleObject_OnPlayerDisconnect(playerid, reason);

#define ResetVehicleAttachedObject FannVehicleObject_ResetVehicleAttachedObject
#define IsVehicleAttachedObjectSlotUsed FannVehicleObject_IsVehicleAttachedObjectSlotUsed
#define SetVehicleAttachedObject FannVehicleObject_SetVehicleAttachedObject
#define RemoveVehicleAttachedObject FannVehicleObject_RemoveVehicleAttachedObject
#define GetInfoVehicleAttachedObject FannVehicleObject_GetInfoVehicleAttachedObject
#define EditVehicleAttachedObject FannVehicleObject_EditVehicleAttachedObject