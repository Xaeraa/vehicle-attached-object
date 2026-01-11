/*
    ------------------ Extended Vehicle Attached Object ------------------
    those dont know, Attaching Object to Vehicle doesn't same like Attaching Object to Player.
    So, in this include i've replicated Attaching Object to Player for Vehicle.

    remember! this is just replicated, and have any lack.

    By : Fann / Xaeraa

    ------ [ Native ] ------
    bool:SetVehicleAttachedObject
    bool:EditVehicleAttachedObject(vehicleid, objectid)
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

#define VO:: FannVehicleObject_
enum VO::enum_data
{
    VO::Model,
    Float:VO::Pos[6],
    VO::Material[2],
    STREAMER_TAG_OBJECT:VO::TempObject,
    STREAMER_TAG_OBJECT:VO::Object
};

static 
    VO::Data[MAX_VEHICLES][MAX_VEHICLEOBJECT_INDEX][VO::enum_data]
;

static VO::ResetVehicleAttachedObject(vehicleid, index)
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] ResetVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index))
        DestroyDynamicObject(VO::Data[vehicleid][index][VO::Object]);

    if(IsValidDynamicObject(VO::Data[vehicleid][index][VO::TempObject]))
        DestroyDynamicObject(VO::Data[vehicleid][index][VO::TempObject]);

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

stock VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index) 
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] IsVehicleAttachedObjectSlotUsed(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    return (IsValidDynamicObject(VO::Data[vehicleid][index][VO::Object]) || IsValidDynamicObject(VO::Data[vehicleid][index][VO::TempObject]));
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
    if(materialColour1 != 0) SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::Object], 0, modelid, "none", "none", materialColour1);
    if(materialColour2 != 0) SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::Object], 1, modelid, "none", "none", materialColour2);
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

    if(!VO::IsVehicleAttachedObject(vehicleid, index)) return 0;

    VO::ResetVehicleAttachedObject(vehicleid, index);
    return 1;
}

stock VO::GetInfoVehicleAttachedObject(vehicleid, index, &modelid, &Float:offset_x, &Float:offset_y, &Float:offset_z, &Float:rotation_x, &Float:rotation_y, &Float:rotation_z, &materialColour1, &materialColour2)
{
    if(index < 0 || index > (MAX_VEHICLEOBJECT_INDEX-1))
    {
        printf("[Warning] SetVehicleAttachedObject(): index is lower than 0 or higher than %d", MAX_VEHICLEOBJECT_INDEX);
        return 0;
    }

    if(!VO::IsVehicleAttachedObject(vehicleid, index)) return 0;

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

    if(VO::IsVehicleAttachedObjectSlotUsed(vehicleid, index))
        DestroyDynamicObject(VO::Data[vehicleid][index][VO::Object]);

    VO::Data[vehicleid][index][VO::TempObject] = CreateDynamicObject(modelid, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    if(VO::Data[vehicleid][index][VO::Material][0] != 0) SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::TempObject], 0, modelid, "none", "none", VO::Data[vehicleid][index][VO::Material][0]);
    if(VO::Data[vehicleid][index][VO::Material][1] != 0) SetDynamicObjectMaterial(VO::Data[vehicleid][index][VO::TempObject], 1, modelid, "none", "none", VO::Data[vehicleid][index][VO::Material][1]);
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
        for(new fan = 0; fan < MAX_VEHICLEOBJECT_INDEX; fan++) VO::ResetVehicleAttachedObject(vehicleid, fan);
    }
    return ret;
}

#if defined _ALS_CreateVehicle
    #undef CreateVehicle 
#else
    #define _ALS_CreateVehicle
#endif
#define CreateVehicle FannVehicleObject_CreateVehicle

stock VO::DestroyVehicle(vehicleid)
{
    if(IsValidVehicle(vehicleid))
    {
        for(new fan = 0; fan < MAX_VEHICLEOBJECT_INDEX; fan++) VO::ResetVehicleAttachedObject(vehicleid, fan);
    }
    return DestroyVehicle(vehicleid);
}

#if defined _ALS_DestroyVehicle
    #undef DestroyVehicle 
#else
    #define _ALS_DestroyVehicle
#endif
#define DestroyVehicle FannVehicleObject_DestroyVehicle