/*
	Author: Mallen

	Description:
		Sets up the Fortify system and ensures players with no fortify tool at start do not have the ability to fortify

	Parameter(s):
		0: MODULE -  The FNF init module

	Returns:
		None
*/

params["_module"];

_fortifyEnabled = true;

fnf_fortifyPoints = _module getVariable "fnf_fortifyPoints";

if !([player, "ACE_Fortify"] call BIS_fnc_hasItem) exitWith
{
  call FNF_ClientSide_fnc_disableFortify;
};

//Function made by Killzone_Kid. From A3 Wiki.
KK_fnc_inHouse = {
  lineIntersectsSurfaces [
    getPosWorld _this,
    getPosWorld _this vectorAdd [0, 0, 50],
    _this, objNull, true, 1, "GEOM", "NONE"
  ] select 0 params ["","","","_house"];

  if (_house isKindOf "House") exitWith { true };

  false
};

[{
    params ["_unit", "_object", "_cost"];
    _canPlace = true;
    _errorStr = "";

    if (_object call KK_fnc_inHouse) then {
      _canPlace = false;
      _errorStr = "<t align='center'>Cannot place objects within buildings</t>"
    };

    //when would this even be triggered?
    if (_cost > fnf_fortifyPoints) then {
      _canPlace = false;
      _errorStr = "<t align='center'>Cannot place object, not enough funds</t>";
    };

    if (_canPlace) then {

      missionNamespace setVariable ["ace_fortify_budget_west", -1, false];
      missionNamespace setVariable ["ace_fortify_budget_east", -1, false];
      missionNamespace setVariable ["ace_fortify_budget_guer", -1, false];

      fnf_fortifyPoints = fnf_fortifyPoints - _cost;

      ["<t align='center'>Fortify Budget: " + str(fnf_fortifyPoints) + "</t>", "info"] call FNF_ClientSide_fnc_notificationSystem;
    } else {
      [_errorStr, "error"] call FNF_ClientSide_fnc_notificationSystem;
    };

    _canPlace
}] call acex_fortify_fnc_addDeployHandler;

["acex_fortify_objectDeleted", {
  if !((_this select 0) == player) exitWith {};
  _type = typeOf (_this select 2);
  _fortifyObjsArr = [];
  _fortifyVarStr = "";
  _cost = 0;

  missionNamespace setVariable ["ace_fortify_budget_west", -1, false];
  missionNamespace setVariable ["ace_fortify_budget_east", -1, false];
  missionNamespace setVariable ["ace_fortify_budget_guer", -1, false];

  switch (playerSide) do {
    case east: {
      _fortifyVarStr = "ace_fortify_objects_east";
    };
    case west: {
      _fortifyVarStr = "ace_fortify_objects_west";
    };
    case independent: {
      _fortifyVarStr = "ace_fortify_objects_guer";
    };
  };

  _fortifyObjsArr = missionNamespace getVariable _fortifyVarStr;

  {
    if ((_x select 0) isEqualTo _type) then {
      _cost = (_x select 1);
    };
  } forEach _fortifyObjsArr;

  fnf_fortifyPoints = fnf_fortifyPoints + _cost;

  ["<t align='center'>Fortify Budget: " + str(fnf_fortifyPoints) + "</t>", "info"] call FNF_ClientSide_fnc_notificationSystem;
}] call CBA_fnc_addEventHandler;

["ace_interactMenuOpened", {
  if ((_this select 0) == 0) exitWith {};

  missionNamespace setVariable ["ace_fortify_budget_west", fnf_fortifyPoints, false];
  missionNamespace setVariable ["ace_fortify_budget_east", fnf_fortifyPoints, false];
  missionNamespace setVariable ["ace_fortify_budget_guer", fnf_fortifyPoints, false];

}] call CBA_fnc_addEventHandler;
