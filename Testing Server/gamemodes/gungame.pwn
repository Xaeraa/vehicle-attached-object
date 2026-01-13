/*
    GunGame is an example gamemode.
    It contains minimal features to be fun out of the box. It is up to the
    developer to add their own ideas to it.

    Possibilites for new features include:
        - Multiple skins
        - Different maps
        - Textdraws instead of gametext
        - 'Effects' for weapons (e.g. exploding bullets for the
            otherwise boring rifle)

    Originally made by NotUnlikeTheWaves

    Authors:
        - NotUnlikeTheWaves
        - AmyrAhmady (iAmir)
*/

#define MIXED_SPELLINGS

#include <open.mp>
#include <streamer>
#define VO_DEBUG
#include <a_vehicleobject>

// Amount of kills required per level-up
#define KILLS_PER_LEVEL 3

// Definition of body part ID that corresponds to the head of a character
#define BODYPART_HEAD 9

enum e_body_data 
{
    Id,
    Model[37]
};

new BodyWork[][e_body_data] = 
{
    {1000,"Generic Spoiler"},
    {1001,"Generic Spoiler"},
    {1002,"Generic Spoiler"},
    {1003,"Generic Spoiler"},
    {1004,"Bonnet Scoop"},
    {1005,"Bonnet Scoop"},
    {1006,"Generic Vehicle Roof-Scoop"},
    {1007,"Generic Vehicle Side Skirt (L)"},
    {1011,"Bonnet Scoop"},
    {1012,"Bonnet Scoop"},
    {1013,"Round Fog Lamps"},
    {1014,"Generic Spoiler"},
    {1015,"Generic Spoiler"},
    {1016,"Generic Spoiler"},
    {1017,"Generic Vehicle Side Skirt (R)"},
    {1018,"Curved Twin Cylinder Generic Exhaust"},
    {1019,"Twin Cylinder Generic Exhaust"},
    {1020,"Large Generic Exhaust"},
    {1021,"Medium Generic Exhaust"},
    {1022,"Small Generic Exhaust"},
    {1023,"Generic Spoiler"},
    {1024,"Square Fog Lamps"},
    {1026,"Sultan Side Skirt Type 1 (L)"},
    {1027,"Sultan Side Skirt Type 1 (R)"},
    {1028,"Sultan Exhaust Type 1"},
    {1029,"Sultan Exhaust Type 2"},
    {1030,"Sultan Side Skirt Type 2 (R)"},
    {1031,"Sultan Side Skirt Type 1 (L)"},
    {1032,"Sultan Roof Scoop type 1"},
    {1033,"Sultan Roof Scoop type 2"},
    {1169,"Sultan Front Bumper type 1"},
    {1170,"Sultan Front Bumper type 2"},
    {1138,"Sultan Spoiler type 1"},
    {1139,"Sultan Spoiler type 2"},
    {1140,"Sultan Rear Bumper type 2"},
    {1141,"Sultan Rear Bumper type 1"},
    {1146,"Elegy Spoiler type 2"},
    {1147,"Elegy Spoiler type 1"},
    {1148,"Elegy Rear Bumper type 2"},
    {1149,"Elegy Rear Bumper type 1"},
    {1150,"Flash Rear Bumper type 1"},
    {1151,"Flash Rear Bumper type 2"},
    {1152,"Flash Front Bumper type 2"},
    {1153,"Flash Front Bumper type 1"},
    {1154,"Stratum Rear Bumper type 1"},
    {1155,"Stratum Front Bumper type 1"},
    {1156,"Stratum Rear Bumper type 2"},
    {1157,"Stratum Front Bumper type 2"},
    {1158,"Jester Spoiler type 2"},
    {1159,"Jester Rear Bumper type 1"},
    {1160,"Jester Front bumper type 1"},
    {1161,"Jester Rear bumper type2"},
    {1162,"Jester Spoiler type 1"},
    {1163,"Uranus Spoiler type 2"},
    {1164,"Uranus Spoiler type 1"},
    {1165,"Uranus Front Bumper type 2"},
    {1166,"Uranus Rear Bumper type 2"},
    {1167,"Uranus Front Bumper type 1"},
    {1168,"Uranus Rear Bumper type 1"},
    {1171,"Elegy Front Bumper type 1"},
    {1172,"Elegy Front Bumper type 2"},
    {1173,"Jester Front Bumper type 2"},
    {1174,"Broadway Front Bumper type 1"},
    {1175,"Broadway Front Bumper type 2"},
    {1176,"Broadway Rear Bumper type 1"},
    {1178,"Remington Rear Bumper type 2"},
    {1179,"Remington Front Bumper type 1"},
    {1180,"Remington Rear Bumper type 2"},
    {1181,"Blade Front Bumper type 2"},
    {1182,"Blade Front Bumper type 1"},
    {1183,"Blade Rear Bumper type 2"},
    {1184,"Blade Rear Bumper type 1"},
    {1185,"Remington Front Bumper type 2"},
    {1186,"Savanna Rear Bumper type 2"},
    {1187,"Savanna Rear Bumper type 1"},
    {1188,"Savanna Front Bumper type 2"},
    {1189,"Savanna Front Bumper type 1"},
    {1190,"Tornado Rear Bumper type 1"},
    {1191,"Tornado Rear Bumper type 2"},
    {1192,"Tornado Front Bumper type 1"},
    {1193,"Tornado Front Bumper type 2"},
    {1034,"Elegy Exhaust type 1"},
    {1035,"Elegy Roof Scoop Type 1"},
    {1036,"Elegy Side Skirt type 1 (L)"},
    {1037,"Elegy Exhaust Type 2"},
    {1038,"Elegy Roof Scoop type 2"},
    {1039,"Elegy Side Skirt type 2 (L)"},
    {1040,"Elegy Side Skirt type 1 (R)"},
    {1041,"Elegy Side Skirt type 2 (R)"},
    {1042,"Broadway Side Skirt (L)"},
    {1043,"Broadway Exhaust type 2"},
    {1044,"Broadway Exhaust type 1"},
    {1045,"Flash Exhaust type 2"},
    {1046,"Flash Exhaust type 1"},
    {1047,"Flash Side Skirt type 1 (L)"},
    {1048,"Flash Side Skirt type 2 (L)"},
    {1049,"Flash Spoiler type 1"},
    {1050,"Flash Spoiler type 2"},
    {1051,"Flash Side Skirt type 1 (R)"},
    {1052,"Flash Side Skirt type 2 (R)"},
    {1053,"Flash Roof Scoop type 2"},
    {1054,"Flash Roof Scoop type 1"},
    {1055,"Stratum Roof Scoop type 1"},
    {1056,"Stratum Side Skirt type 1 (L)"},
    {1057,"Stratum Side Skirt type 2 (L)"},
    {1058,"Stratum Spoiler type 1"},
    {1059,"Stratum Exhaust type 2"},
    {1060,"Stratum Spoiler type 2"},
    {1061,"Stratum Roof Scoop type 2"},
    {1062,"Stratum Side Skirt type 1 (R)"},
    {1063,"Stratum Side Skirt type 2 (R)"},
    {1064,"Stratum Exhaust type 1"},
    {1065,"Jester Exhaust type 1"},
    {1066,"Jester Exhaust type 2"},
    {1067,"Jester Roof Scoop type 1"},
    {1068,"Jester Roof Scoop type 2"},
    {1069,"Jester Side Skirt type 1 (L)"},
    {1070,"Jester Side Skirt type 2 (L)"},
    {1071,"Jester Side Skirt type 1 (R)"},
    {1072,"Jester Side Skirt type 2 (R)"},
    {1088,"Uranus Roof Scoop 1"},
    {1089,"Uranus Exhaust Type 1"},
    {1090,"Uranus Side Skirt type 1 (L)"},
    {1091,"Uranus Roof Scoop 2"},
    {1092,"Uranus Exhaust Type 2"},
    {1093,"Uranus Side Skirt type 2 (L)"},
    {1094,"Uranus Side Skirt type 1 (R)"},
    {1095,"Uranus Side Skirt type 2 (R)"},
    {1099,"Broadway Side Skirt (R)"},
    {1100,"Remington Misc. Part 1"},
    {1101,"Remington Side Skirt type 1 (R)"},
    {1102,"Savanna Side Skirt (R)"},
    {1103,"Blade Roof type 2"},
    {1104,"Blade Exhaust type 1"},
    {1105,"Blade Exhaust type 2"},
    {1106,"Remington Side Skirt type 2 (L)"},
    {1107,"Blade Side Skirt (R)"},
    {1108,"Blade Side Skirt (L)"},
    {1109,"Slamvan Rear Bullbars type 1"},
    {1110,"Slamvan Rear Bullbars type 2"},
    {1111,"Slamvan hood ornament 1 (not used)"},
    {1112,"Slamvan hood ornament 2 (not used)"},
    {1113,"Slamvan Exhaust type 1"},
    {1114,"Slamvan Exhaust type 2"},
    {1115,"Slamvan Front Bullbars type 1"},
    {1116,"Slamvan Front Bullbars type 2"},
    {1117,"Slamvan Front Bumper"},
    {1118,"Slamvan Side Skirt type 1 (L)"},
    {1119,"Slamvan Side Skirt type 2 (L)"},
    {1120,"Slamvan Side Skirt type 1 (R)"},
    {1121,"Slamvan Side Skirt type 2 (R)"},
    {1122,"Remington Side Skirt type 1 (L)"},
    {1123,"Remington Misc. Part 2"},
    {1124,"Remington Side Skirt type 2 (R)"},
    {1125,"Remington Misc. Part 3"},
    {1126,"Remington Exhaust type 1"},
    {1127,"Remington Exhaust type 2"},
    {1128,"Blade Roof Type 1"},
    {1129,"Savanna Exhaust type 1"},
    {1130,"Savanna Roof type 1"},
    {1131,"Savanna Roof type 2"},
    {1132,"Savanna Exhaust type 2"},
    {1133,"Savanna Side Skirt (L)"},
    {1134,"Tornado Side Skirt (L)"},
    {1135,"Tornado Exhaust type 2"},
    {1136,"Tornado Exhaust type 1"},
    {1137,"Tornado Side Skirt (R)"},
    {1142,"Oval Bonnet Vents (R)"},
    {1143,"Oval Bonnet Vents (L)"},
    {1144,"Square Bonnet Vents (R)"},
    {1145,"Square Bonnet Vents (L)"},
    {19310,"Taxi Cab White"},
    {19311,"Taxi Cab Black"},
    {18646,"Police_Light1"},
    {19797,"Police_Visor_Strobe1"},
    {19306,"Red_flag1"},
    {19307,"Blue_flag2"},
    {19620,"Light_Bar1"},
    {11701,"Ambulance_Lights1"},
    {19419,"Police_lights01"},
    {19834,"PoliceLine1"}
};

// These are the random locations the user can spawn at
// x - y - z - rotation angle
new const
    Float:gRandPos[9][4] =
    {
        {-1291.6622, 2513.7566, 87.0500, 355.3697},
        {-1303.8662, 2527.4270, 87.5878, 358.6714},
        {-1308.1099, 2544.3853, 87.7422, 171.4412},
        {-1321.0725, 2526.1138, 87.4379, 183.3481},
        {-1335.7893, 2520.8984, 87.0469, 270.7455},
        {-1298.5408, 2547.2991, 87.6747, 356.4313},
        {-1291.3345, 2533.8853, 87.7422, 92.7705},
        {-1288.5410, 2528.5769, 87.6331, 183.0114},
        {-1316.3402, 2499.9949, 87.0420, 271.8305}
    },
    WEAPON:gWeaponList[] =
    {
        WEAPON_COLT45,
        WEAPON_SILENCED,
        WEAPON_TEC9,
        WEAPON_UZI,
        WEAPON_MP5,
        WEAPON_GRENADE,
        WEAPON_SHOTGUN,
        WEAPON_SHOTGSPA,
        WEAPON_SAWEDOFF,
        WEAPON_RIFLE,
        WEAPON_AK47,
        WEAPON_M4,
        WEAPON_SNIPER,
        WEAPON_DEAGLE
    }
;

enum e_STATUS
{
    e_LEVEL,
    e_KILLS_AT_LEVEL,
    bool:e_DEAD,
    bool:e_HOLDING_PRIMARY // Whether the player holds their primary weapon
};

new
    gPlayerStatus[MAX_PLAYERS][e_STATUS],
    Text:gRespawn,
    bool:gGameInProgress
;

forward Restart();

main()
{
    print("\n----------------------------------");
    print(" gungame is a gun game mode released as");
    print(" an example mode for open.mp");
    print(" ");
    print(" Author: NotUnlikeTheWaves (github)");
    print("----------------------------------\n");
}

public OnGameModeInit()
{
    SetGameModeText("Gun Game");
    AddPlayerClass(0, -1291.6622, 2513.7566, 87.0500, 355.3697, WEAPON_FIST, 0, WEAPON_FIST, 0, WEAPON_FIST, 0);
    ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    gRespawn = TextDrawCreate(320.000000, 155.000000, "~y~Press '~r~~k~~VEHICLE_ENTER_EXIT~~y~' to spawn!");
    TextDrawAlignment(gRespawn, TEXT_DRAW_ALIGN_CENTER);
    TextDrawBackgroundColor(gRespawn, 255);
    TextDrawFont(gRespawn, TEXT_DRAW_FONT_2);
    TextDrawLetterSize(gRespawn, 0.549999, 1.500000);
    TextDrawColor(gRespawn, -65281);
    TextDrawSetOutline(gRespawn, 0);
    TextDrawSetProportional(gRespawn, true);
    TextDrawSetShadow(gRespawn, 3);
    gGameInProgress = true;
    return 1;
}

public OnGameModeExit()
{
    return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    SetPlayerPos(playerid, 1958.3783, 1343.1572, 15.3746);
    SetPlayerCameraPos(playerid, -1251.1089, 2551.7546, 104.6863);
    SetPlayerCameraLookAt(playerid, -1302.1554, 2533.4226, 93.8427);
    return 1;
}

public OnPlayerConnect(playerid)
{
    SendClientMessage(playerid, 0xFF0000FF, "Welcome to Gun Game! The rules are simple:");
    SendClientMessage(playerid, 0xFFFFFFFF, "You start with two pistols. You advance to the next weapon by killing other players.");
    SendClientMessage(playerid, 0xFFFFFFFF, "The last stage is the Desert Eagle! Get enough kills with it, and you win the round!");
    SendClientMessage(playerid, 0xFFFFFFFF, "You also have a knife. Use it to demote other players!");
    SendClientMessage(playerid, 0xFFFFFFFF, "Have fun, and let the games begin!");
    gPlayerStatus[playerid][e_LEVEL] = 0;
    gPlayerStatus[playerid][e_KILLS_AT_LEVEL] = 0;
    gPlayerStatus[playerid][e_DEAD] = true;
    gPlayerStatus[playerid][e_HOLDING_PRIMARY] = true;
    TextDrawHideForPlayer(playerid, gRespawn);
    SetPlayerColor(playerid, 0xFF0000FF);
    return 1;
}

public OnPlayerSpawn(playerid)
{
    // Set position
    new rand = random(9);
    SetPlayerPos(playerid, gRandPos[rand][0], gRandPos[rand][1], gRandPos[rand][2]);
    SetPlayerFacingAngle(playerid, gRandPos[rand][3]);
    SetPlayerWorldBounds(playerid, -1274.2817, -1358.5095, 2575.6509, 2472.3486);
    SetCameraBehindPlayer(playerid);

    // Give the right weapons to the player
    GivePlayerWeapon(playerid, WEAPON_KNIFE, 1);
    GivePlayerWeapon(playerid, gWeaponList[gPlayerStatus[playerid][e_LEVEL]], 65535);

    // General stuff
    gPlayerStatus[playerid][e_DEAD] = false;
    gPlayerStatus[playerid][e_HOLDING_PRIMARY] = true;
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	if(!strcmp(cmdtext, "/veh", true))
	{
		new Float:pos[4];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		GetPlayerFacingAngle(playerid, pos[3]);
		
		new vehicleid = CreateVehicle((random(211)+1)+400, pos[0], pos[1], pos[2], pos[3]);
		if(!IsValidVehicle(vehicleid)) return SendClientMessage(playerid, -1, "kendaraan tidak dapat dispawn!");
		
		SendClientMessage(playerid, -1, "kendaraan telah spawn");
		PutPlayerInVehicle(playerid, vehicleid, 0);
	}
	if(!strcmp(cmdtext, "/attached", true))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Kamu tidak naik kendaraan!");
		
		new rand = random(sizeof(BodyWork));
		SetVehicleAttachedObject(vehicleid, 0, BodyWork[rand][Id]);
		SendClientMessage(playerid, -1, "kendaraan udah diattached object %s random.", BodyWork[rand][Model]);
	}		
	if(!strcmp(cmdtext, "/edit", true))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Kamu tidak naik kendaraan!");
		
		if(!IsVehicleAttachedObjectSlotUsed(vehicleid, 0)) return SendClientMessage(playerid, -1, "belum diattached object!");
		
		EditVehicleAttachedObject(playerid, vehicleid, 0);
	}
	if(!strcmp(cmdtext, "/remove", true))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, -1, "Kamu tidak naik kendaraan!");
		
		if(!IsVehicleAttachedObjectSlotUsed(vehicleid, 0)) return SendClientMessage(playerid, -1, "belum diattached object!");
		
		RemoveVehicleAttachedObject(vehicleid, 0);
		SendClientMessage(playerid, -1, "berhasil dihapus!");
	}
	return 1;
}

public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	return 1;
}

public OnPlayerDeath(playerid, killerid, WEAPON:reason)
{
    SendDeathMessage(killerid, playerid, reason);
    TogglePlayerSpectating(playerid, true);
    TextDrawShowForPlayer(playerid, gRespawn);
    gPlayerStatus[playerid][e_DEAD] = true;
    if(killerid == INVALID_PLAYER_ID)
    {
        SetPlayerCameraPos(playerid, -1251.1089, 2551.7546, 104.6863);
        SetPlayerCameraLookAt(playerid, -1302.1554, 2533.4226, 93.8427);
    }
    else
    {
        PlayerSpectatePlayer(playerid, killerid);

        // Knife deaths are humiliating, and demote the player.
        if(reason == WEAPON_KNIFE)
        {
            GameTextForPlayer(killerid, "~r~Humiliation!~n~~y~You demoted someone!", 1650, 6);
            GameTextForPlayer(playerid, "~r~Humiliated~n~~y~You got demoted!", 1650, 6);
            if(gPlayerStatus[playerid][e_LEVEL] != 0) gPlayerStatus[playerid][e_LEVEL]--;
            gPlayerStatus[playerid][e_KILLS_AT_LEVEL] = 0;

        }
        gPlayerStatus[killerid][e_KILLS_AT_LEVEL]++;
        if(gPlayerStatus[killerid][e_KILLS_AT_LEVEL] == KILLS_PER_LEVEL)
        {
            gPlayerStatus[killerid][e_KILLS_AT_LEVEL] = 0;
            gPlayerStatus[killerid][e_LEVEL]++;

            //Player has won the game.
            if(gPlayerStatus[killerid][e_LEVEL] == sizeof gWeaponList)
            {
                EndRound();
            }
            else
            {
                GameTextForPlayer(killerid, "~r~Player Killed!~n~~y~Advanced to the next tier!", 1650, 6);
                SetPlayerScore(killerid, gPlayerStatus[killerid][e_LEVEL] + 1);
                ResetPlayerWeapons(killerid);
                GivePlayerWeapon(killerid, WEAPON_KNIFE, 1);
                GivePlayerWeapon(killerid, gWeaponList[gPlayerStatus[killerid][e_LEVEL]], 65535);
            }
        }
        else
        {
            ShowKillsTillNextLevel(killerid);
        }
    }
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, WEAPON:weaponid, bodypart)
{
    new Float:health;
    GetPlayerHealth(playerid, health);

    // Take twice the damage as you normally would, to increase the pace in the game.
    new Float:multiplier = 2.0;

    // Make headshots do 50% more damage over the regular multiplier
    if(bodypart == BODYPART_HEAD)
    {
        multiplier = 3.0;
    }
    SetPlayerHealth(playerid, health - amount * multiplier);
}

public OnPlayerUpdate(playerid)
{
    if(gPlayerStatus[playerid][e_DEAD] == false)
    {
        // We want to avoid the player switching to his hands as a weapon
        // A player should only be able to use his knife and the weapon given to them.
        if(!GetPlayerWeapon(playerid))
        {
            if(gPlayerStatus[playerid][e_HOLDING_PRIMARY] == true)
            {
                SetPlayerArmedWeapon(playerid, WEAPON_KNIFE);
                gPlayerStatus[playerid][e_HOLDING_PRIMARY] = false;
            }
            else
            {
                SetPlayerArmedWeapon(playerid, gWeaponList[gPlayerStatus[playerid][e_LEVEL]]);
                gPlayerStatus[playerid][e_HOLDING_PRIMARY] = true;
            }
        }
        else
        {
            gPlayerStatus[playerid][e_HOLDING_PRIMARY] = !(GetPlayerWeapon(playerid) == WEAPON_KNIFE);
        }

    }
    else
    {
        SetPlayerCameraPos(playerid, -1251.1089, 2551.7546, 104.6863);
        SetPlayerCameraLookAt(playerid, -1302.1554, 2533.4226, 93.8427);
        new KEY:keys[3];
        GetPlayerKeys(playerid, keys[0], keys[1], keys[2]);
        if(keys[0] & KEY_SECONDARY_ATTACK && gGameInProgress == true)
        {
            TogglePlayerSpectating(playerid, false);
            SpawnPlayer(playerid);
            TextDrawHideForPlayer(playerid, gRespawn);
            gPlayerStatus[playerid][e_DEAD] = false;
        }
    }
    return 1;
}

public Restart()
{
    SendRconCommand("gmx");
}

EndRound()
{
    SendClientMessageToAll(0x008000FF, "The game has ended!");
    SendClientMessageToAll(0x008000FF, "A new round will start in 8 seconds.");
    gGameInProgress = false;

    // Print the top three best players.
    new highest[3] = {INVALID_PLAYER_ID, ...};
    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if (!IsPlayerConnected(i))
        {
            continue;
        }
        TogglePlayerSpectating(i, true);
        SetPlayerCameraPos(i, -1251.1089, 2551.7546, 104.6863);
        SetPlayerCameraLookAt(i, -1302.1554, 2533.4226, 93.8427);

        // Find the player with the highest score.
        if(GetPlayerScore(i) > GetPlayerScore(highest[0]))
        {
            highest[2] = highest[1];
            highest[1] = highest[0];
            highest[0] = i;
        }
        else if(GetPlayerScore(i) > GetPlayerScore(highest[1]))
        {
            highest[2] = highest[1];
            highest[1] = i;
        }
        else if(GetPlayerScore(i) > GetPlayerScore(highest[2]))
        {
            highest[2] = i;
        }
    }

    new string[144], pName[3][MAX_PLAYER_NAME + 1];
    GetPlayerName(highest[0], pName[0], MAX_PLAYER_NAME);
    GetPlayerName(highest[1], pName[1], MAX_PLAYER_NAME);
    GetPlayerName(highest[2], pName[2], MAX_PLAYER_NAME);
    format(string, sizeof string,
        "~r~The match ended!~n~~g~1. %02i - %s~n~~y~2. %02i - %s~n~~r~~h~3. %02i - %s", 
        GetPlayerScore(highest[0]),
        pName[0],
        GetPlayerScore(highest[1]),
        pName[1],
        GetPlayerScore(highest[2]),
        pName[2]);
    GameTextForAll(string, 7500, 1);
    SetTimer("Restart", 8000, false);
}

ShowKillsTillNextLevel(playerid)
{
    new str[128];
    format(str, sizeof str, "~r~%i~y~ kills till level up!", KILLS_PER_LEVEL - gPlayerStatus[playerid][e_KILLS_AT_LEVEL]);
    GameTextForPlayer(playerid, str, 1000, 4);
}
