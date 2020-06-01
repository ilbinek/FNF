// Add gear - you can also re-define gear here
phx_loadout_aid call phx_fnc_addGear;
phx_loadout_smoke call phx_fnc_addGear;
phx_loadout_grenade call phx_fnc_addGear;
phx_loadout_maptools call phx_fnc_addGear;
phx_loadout_rifle_mag call phx_fnc_addGear;
player addWeapon phx_loadout_rifle_weapon;
if (!isNil "phx_loadout_gr_adapter") then {player addPrimaryWeaponItem phx_loadout_gr_adapter};
if (!isNil "phx_loadout_gr_grenade") then {phx_loadout_gr_grenade call phx_fnc_addGear};
phx_loadout_rifle_mag_tracer call phx_fnc_addGear;
phx_loadout_sidearm_mag call phx_fnc_addGear;
player addWeapon phx_loadout_sidearm_weapon;

missionNamespace setVariable ["phx_loadoutAssigned",true]; //Place this at the end of the loadout script so other scripts can tell when the player's loadout has been set.
