/*
Calls server portion of the game modes
Deletes unused objectives
*/

if (!isServer) exitWith {};

missionNamespace setVariable ["phx_gameEnd", false, true];

phx_overTimeConStr = "N/A";

_fnc_warnForAD = {
  _str = format["phx_attackingSide (%1)<br/>or<br/>phx_defendingSide (%2)<br/>isn't set, but this is an attack/defend gamemode (%3).",phx_attackingSide,phx_defendingSide,phx_gameMode];
  _strStruct = "<t align='center'>" + _str + "<br/>The framework may not work properly!</t>";
  [{time > 3}, {
    [_this, "error", 15] remoteExecCall ["phx_ui_fnc_notify", 0, true];
  }, _strStruct] call CBA_fnc_waitUntilAndExecute;
  [_str] call BIS_fnc_error;
  systemChat _str;
  systemChat "The framework may not work properly!";
};
_fnc_warnForNeutral = {
  _str = format["phx_attackingSide (%1)<br/>or<br/>phx_defendingSide (%2)<br/>is set, but this is a neutral gamemode (%3).",phx_attackingSide,phx_defendingSide,phx_gameMode];
  _strStruct = "<t align='center'>" + _str + "<br/>The framework may not work properly!</t>";
  [{time > 3}, {
    [_this, "error", 15] remoteExecCall ["phx_ui_fnc_notify", 0, true];
  }, _strStruct] call CBA_fnc_waitUntilAndExecute;
  [_str] call BIS_fnc_error;
  systemChat _str;
  systemChat "The framework may not work properly!";
};

switch (phx_gameMode) do {
  case "destroy": {
    if (sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForAD};
    execVM "modes\destroy\destroy_server.sqf";
    phx_overTimeConStr = "The mission will go into overtime if there is only 1 alive objective remaining and attackers stay near the objective.";
  };
  case "uplink": {
    if (sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForAD};
    execVM "modes\uplink\uplink_server.sqf";
    phx_overTimeConStr = "The mission will go into overtime if any terminal is being hacked.";
  };
  case "rush": {
    if (sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForAD};
    execVM "modes\rush\rush_server.sqf";
    phx_overTimeConStr = "The mission will go into overtime if the final terminal is being hacked.";
  };
  case "captureTheFlag": {
    if (sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForAD};
    execVM "modes\ctf\ctf_server.sqf";
    phx_overTimeConStr = "The mission will go into overtime if the flag stays within the capture zone.";
  };
  case "adSector": {
    if (sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForAD};
    execVM "modes\adsector\adSector.sqf";
    phx_overTimeConStr = "The mission will go into overtime if there is only 1 active sector remaining and attackers stay inside it.";
  };
  case "assassin": {
    if (sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForAD};
    execVM "modes\assassin\assassin_server.sqf";
  };
  case "neutralSector": {
    if !(sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForNeutral};
    execVM "modes\neutralsector\neutralSector.sqf";
    phx_overTimeConStr = "The mission will go into overtime if the second-highest side stays within 20 points of the highest side. The first side to 100 points will still win if mission is within normal time limit.";
  };
  case "scavHunt": {
    if !(sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForNeutral};
    execVM "modes\scavHunt\scavHunt_server.sqf";
    phx_overTimeConStr = "The mission will go into overtime if both teams hold an equal number of target items in their zone when the timer reaches zero.";
  };
  case "connection": {
    if !(sideEmpty in [phx_attackingSide, phx_defendingSide]) exitWith {call _fnc_warnForNeutral};
    execVM "modes\connection\connection_server.sqf";
    phx_overTimeConStr = "The mission will go into overtime if the second-highest side stays within 20 points of the highest side. The first side to 100 points will still win if mission is within normal time limit.";
  };
};

publicVariable "phx_overTimeConStr";

//To do: allow objectives to be deleted w/o throwing error

_deleteObj = {
  params ["_obj"];

  if (!isNil "_obj") then {
    if (!isNull _obj) then {deleteVehicle _obj};
  };
};

if !(phx_gameMode isEqualTo "destroy") then {
  (getMissionLayerEntities "FNF Gamemode: Destroy") params ["_objects", "_markers"];
  {_x call _deleteObj} forEach _objects;
  {_x remoteExec ["deleteMarkerLocal", 0, true]} forEach _markers;
};

if !(phx_gameMode isEqualTo "uplink" || phx_gameMode isEqualTo "rush" || phx_gameMode isEqualTo "connection") then {
  (getMissionLayerEntities "FNF Gamemode: Rush, Uplink, Connection") params ["_objects", "_markers"];
  {_x call _deleteObj} forEach _objects;
  {_x remoteExec ["deleteMarkerLocal", 0, true]} forEach _markers;
};

if !(phx_gamEMode isEqualTo "captureTheFlag") then {
  (getMissionLayerEntities "FNF Gamemode: CTF") params ["_objects", "_markers"];
  {_x call _deleteObj} forEach _objects;
  {_x remoteExec ["deleteMarkerLocal", 0, true]} forEach _markers;
};

if !(phx_gameMode isEqualTo "adSector") then {
  (getMissionLayerEntities "FNF Gamemode: ADSector") params ["_objects", "_markers"];
  {_x call _deleteObj} forEach _objects;
  {_x remoteExec ["deleteMarkerLocal", 0, true]} forEach _markers;
};

if !(phx_gameMode isEqualTo "scavHunt") then {
  (getMissionLayerEntities "FNF Gamemode: ScavHunt") params ["_objects", "_markers"];
  {_x call _deleteObj} forEach _objects;
  {_x remoteExec ["deleteMarkerLocal", 0, true]} forEach _markers;
};

if !(phx_gameMode isEqualTo "assassin") then {
  (getMissionLayerEntities "FNF Gamemode: Assassin") params ["_objects", "_markers"];
  {_x call _deleteObj} forEach _objects;
  {_x remoteExec ["deleteMarkerLocal", 0, true]} forEach _markers;
};
