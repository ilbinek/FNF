// Only run server-side
if (!isServer) exitWith {};

#include "..\..\mode_config\scavHunt.sqf"

// Lower game mode to 40 minutes
phx_missionTimeLimit = 40;

// Get present sides
phx_sidesInMission = [east, west, independent] select {playableSlotsNumber _x > 3};

private _numberOfObjectives = 5;
private _numberOfTransportsPerSide = 3;

/*
[OBJECT_NAME, MARKER_NAME, OBJECT_DESCRIPTION, INDEX]
*/
private _scavHuntObjectives = [];
for "_i" from 1 to _numberOfObjectives do {
	private _obj = missionNamespace getVariable [format["scav_obj_%1", _i], objNull];
	if !(isNull _obj) then {
		private _name = "Weapons Cache";
		if (typeOf _obj != "Box_FIA_Ammo_F") then {
			_name = [configfile >> "CfgVehicles" >> typeOf _obj] call BIS_fnc_displayName;
		};
		_scavHuntObjectives pushBack [
			_obj,
			format["scav_obj_%1_mark", _i],
			_name,
			_i
		];
	};
};

private _scavHuntTransports = [];
for "_i" from 1 to (_numberOfTransportsPerSide * (count phx_sidesInMission)) do {
	private _obj = missionNamespace getVariable [format["scav_transport_%1", _i], objNull];
	if !(isNull _obj) then {
		_scavHuntTransports pushBack _obj;
	};
};



// Create array of objectives and transports and push to global var for use in other scripts
_objArr = _scavHuntObjectives;
phx_scavHuntObjs = _objArr apply {_x select 0};
phx_scavHuntTransports = _scavHuntTransports;


// Prep capturable objects
{
  _x allowDamage false;
  _x setVariable ["capturedBy", sideUnknown];
  _x setVariable ["phx_objLoaded", false];
  [_x, true] call ace_arsenal_fnc_removeBox;
  [_x, 7] call ace_cargo_fnc_setSize;
} forEach phx_scavHuntObjs;


// Prep transport vehicles
{
  // set size to 17, room for 1 objective + 2 wheels
  [_x, 9] call ace_cargo_fnc_setSpace;
  // clear existing wheels, add two
  ["ACE_Wheel", _x, 5] call ace_cargo_fnc_removeCargoItem;
  ["ACE_Wheel", _x] call ace_cargo_fnc_loadItem;
  ["ACE_Wheel", _x] call ace_cargo_fnc_loadItem;

  // prevent sides from using each other's vehicles
  _x addEventHandler ["GetIn", {
    params ["_vehicle", "_role", "_unit", "_turret"];
    if !(side _unit isEqualTo ([_vehicle, true] call BIS_fnc_objectSide)) then {
      _unit action ["Eject", _vehicle];
    };
  }];

  // accrue damage by parts and when reaching 1, reset, injure passenger
  // _x allowDamage false; // cannot be used with HandleDamage
  // _x addEventHandler ["HandleDamage", {
  //   params ["_unit", "_selection", "_damage", "_source", "_projectile", "_hitIndex", "_instigator", "_hitPoint"];
  //   private _old = _unit getVariable ["phx_damageCycle", 0];
  //   private _new = _old + (0.01 * _damage);
  //   if (_new >= 1) then {
  //     private _curPax = (fullCrew [_unit, "", false]) select {_x select 1 != 'cargo'};
  //     if (count _curPax > 0) then {
  //       // if vehicle crewed, select a random driver, gunner, commander, or turret seat
  //       private _victim = selectRandom (_curPax apply {_x select 0});
  //       // apply 0.5 damage to head or body, simulate bullet wound
  //       [
  //         _victim,
  //         0.5,
  //         (selectRandom ["Head", "Body"]),
  //         "bullet",
  //         _instigator
  //       ] call ace_medical_fnc_addDamageToUnit;
  //       // force unconscious for 30 seconds, then wake up if stable
  //       [
  //         _victim,
  //         true,
  //         30,
  //         true
  //       ] call ace_medical_fnc_setUnconscious;
  //       // reset vehicle damage counter
  //       _unit setVariable ["phx_damageCycle", 0];
  //     };
  //   } else {
  //     // if vehicle damage counter not at 1, increment
  //     _unit setVariable ["phx_damageCycle", _new];
  //   };
  //   0;
  // }];
  _x allowDamage false;


  [{
    // handle wheel removal by re-adding wheel to truck and deleting nearest wheel in 10m
    _transport = _this # 0;

    _hitParts = [];
    {
      _hitParts pushBack (configName _x);
    } forEach ([configFile >> "CfgVehicles" >> typeOf _transport >> "HitPoints", 0] call BIS_fnc_returnChildren);
    {
      if (_transport getHitPointDamage _x > 0) then {
        _transport setHitPointDamage [_x, 0, false];
        private _nearWheels = nearestObjects [getPos _transport, ["ACE_Wheel"], 10, true];
        if (count _nearWheels > 0) then {deleteVehicle (_nearWheels # 0)};
      };
    } forEach (_hitParts select {['wheel', _x] call BIS_fnc_inString})
  }, 5, _x] call CBA_fnc_addPerFrameHandler;
  

} forEach phx_scavHuntTransports;





// Fetch zone triggers
// phx_scavHuntCapZones = [];
// {
//   private _triggerObj = missionNamespace getVariable [_x, objNull];
//   if (!isNull _triggerObj) then {
//     phx_scavHuntCapZones pushBack _triggerObj;
//   };
// } forEach ["scavHuntCapEAST", "scavHuntCapWEST", "scavHuntCapGUER"];


// Register zone markers
phx_scavHuntCapZones = [];
{
  private _marker = ("scavHuntCap" + str _x);
  if (markerPos _marker select 0 != 0) then {
    phx_scavHuntCapZones pushBack _marker;
    // set marker opacity low until safe start ends
    // _marker setMarkerAlpha 0.3;
  };
} forEach phx_sidesInMission;


// Create objective markers
{
  _x params ["_obj", "_marker", "_name", "_index"];

  private _markStr = [
    _marker, // markerName
    getPos _obj, // markerPos
    "mil_dot", // markerType
    "ELLIPSE", // markerShape
    [25, 25], //markerSize
    0, // markerDir
    "Solid", //markerBrush
    "ColorOrange", //markerColor
    1, // markerAlpha
    format["Obj %1 - %2", _index, _name] // markerText
  ] joinString '|';

  format["|%1", _markStr] call BIS_fnc_stringToMarker;

} forEach _objArr;


// Add loaded/unloaded Event Handlers
["ace_cargoLoaded", {
  if (!isServer) exitWith {};
  _this params ["_item", "_vehicle"];
  private _objIndex = phx_scavHuntObjs find _item;
  if (_objIndex > -1 && (phx_scavHuntTransports find _vehicle) > -1) then {
    (_thisArgs select (_objIndex)) params ["_obj", "_marker", "_name", "_index"];
    private _likelyPlayer = nearestObject [_vehicle, "CAManBase"];
    format["Item %1 (%2) loaded into a transport by %3 (%4)!", _index, _name, side _likelyPlayer call BIS_fnc_sideName, name _likelyPlayer] remoteExec ["systemChat", 0];
    _item setVariable ["phx_objLoaded", true];
    _item allowDamage false;
  } else {
    if (_objIndex > -1) then {
      [_item, _vehicle] call ace_cargo_fnc_unloadItem;
      _item allowDamage false;
    };
  };
}, _objArr] call CBA_fnc_addEventHandlerArgs;

["ace_cargoUnloaded", {
  if (!isServer) exitWith {};
  _this params ["_item", "_vehicle"];
  private _objIndex = phx_scavHuntObjs find _item;
  if (_objIndex > -1 && (phx_scavHuntTransports find _vehicle) > -1) then {
    (_thisArgs select (_objIndex)) params ["_obj", "_marker", "_name", "_index"];
    private _likelyPlayer = nearestObject [_vehicle, "CAManBase"];
    format["Item %1 (%2) unloaded from a transport by %3 (%4)!", _index, _name, side _likelyPlayer call BIS_fnc_sideName, name _likelyPlayer] remoteExec ["systemChat", 0];
    _item setVariable ["phx_objLoaded", false];
    _item allowDamage false;
  };
}, _objArr] call CBA_fnc_addEventHandlerArgs;



phx_scavHuntCheckScores = {
  private _scores = createHashMapFromArray [
    [
      east,
      count(phx_scavHuntObjs select {(_x getVariable ["capturedBy", sideUnknown]) isEqualTo east})
    ],
    [
      west,
      count(phx_scavHuntObjs select {(_x getVariable ["capturedBy", sideUnknown]) isEqualTo west})
    ],
    [
      independent,
      count(phx_scavHuntObjs select {(_x getVariable ["capturedBy", sideUnknown]) isEqualTo independent})
    ]
  ];

  private _winScore = selectMax (values _scores);
  private _winSide = createHashMap;
  {
    if (_y == _winScore) then {_winSide set [_x, _y]};
  } forEach _scores;

  _winSide;
};



// Define cap monitors
phx_scavHuntObjIsNeutral = {
  params ["_obj","_marker","_captureID"];

  waitUntil {
    private _capped = false;
    sleep 2;
    {
      if (_obj inArea _x && (_obj getVariable ["phx_objLoaded", true] isEqualTo false)) exitWith {_capped = true};
    } forEach phx_scavHuntCapZones;
    if (_capped) then {true} else {false};
  };

  {
    private _capMark = _x;
    if (_obj inArea _capMark) exitWith {
      private _cappedSide = sideUnknown;
      switch (_capMark) do {
        case "scavHuntCapEAST": {_cappedSide = east};
        case "scavHuntCapWEST": {_cappedSide = west};
        case "scavHuntCapGUER": {_cappedSide = independent};
        case "scavHuntCapCIV": {_cappedSide = civilian};
        default {_cappedSide = sideUnknown};
      };
      _obj setVariable ["capturedBy", _cappedSide];
      [_captureID + str _cappedSide, "SUCCEEDED", true] call BIS_fnc_taskSetState;
      format["%1 has captured an objective!", _cappedSide call BIS_fnc_sideName] remoteExec ["systemChat", 0];

      _highScore = (call phx_scavHuntCheckScores) toArray false;
      "Leading Team(s):" remoteExec ["systemChat", 0];
      {
        format["  %1 with %2 items", (_x # 0) call BIS_fnc_sideName, _x # 1] remoteExec ["systemChat", 0];
      } forEach _highScore;

      [_obj, _marker, _captureID, _cappedSide, _capMark] spawn phx_scavHuntObjIsCapped;
    };
  } forEach phx_scavHuntCapZones;
};

phx_scavHuntObjIsCapped = {
  params ["_obj","_marker","_captureID","_cappedSide","_capMark"];
  waitUntil {
    sleep 2;
    if (!(_obj inArea _capMark) || (_obj getVariable ["phx_objLoaded", false] isEqualTo true)) then {
      true
    } else {
      false;
    };
  };
  _obj setVariable ["capturedBy", sideUnknown];
  [_captureID + str _cappedSide, "CREATED", true] call BIS_fnc_taskSetState;
  format["%1 has lost an objective!", _cappedSide call BIS_fnc_sideName] remoteExec ["systemChat", 0];

  _highScore = (call phx_scavHuntCheckScores) toArray false;
  format["Leading Team(s):"] remoteExec ["systemChat", 0];
  {
    format["  %1 with %2 items", (_x # 0) call BIS_fnc_sideName, _x # 1] remoteExec ["systemChat", 0];
  } forEach _highScore;

  [_obj, _marker, _captureID] spawn phx_scavHuntObjIsNeutral;
};


{
  if !(isNull (_x select 0)) then {
    _x params ["_obj", "_marker", "_name", "_index"];
    private _captureTaskText = "Capture and bring back the ";
    private _captureID = "captureTask" + str _index + "_";

    // create tasks
    {
      [
        _x,
        _captureID + str _x,
        [
          format [_captureTaskText + "%1", _name],
          format ["Item %1", _index],
          _marker
        ],
        _obj,
        "CREATED"
      ] call BIS_fnc_taskCreate;
    } forEach phx_sidesInMission;
    

    //Check for objectives captured or not
    [_obj, _marker, _captureID] spawn phx_scavHuntObjIsNeutral;


    //Handle moving objective
    [_obj, _marker, _captureID] spawn {
      params ["_obj", "_marker", "_captureID"];
      _objMarkerUpdateTime = 3; //Change this value to however often you want the objective markers to update (seconds)
      _objMaxDistance = selectMin (getMarkerSize _marker);

      //Sets marker position to a random area around the objective, keeping the objective inside the marker
      if !(_obj inArea _marker) then {
        _marker setMarkerPos ([[[position _obj,(_objMaxDistance * random [0.1,0.7,1])]],[]] call BIS_fnc_randomPos);
      };
      {
        [_captureID + str _x, _marker] call BIS_fnc_taskSetDestination;
      } forEach phx_sidesInMission;
      //Loop over objective position every _objMarkerUpdateTime
      //If objective moves more than _objMaxDistance meters away from it's last known position, the objective marker will update
      while {true} do {
        if !(_obj inArea _marker) then {
          //Move the objective marker to a random position around the objective, while keeping the objective inside the marker's area
          _newPos = ([[[position _obj,(_objMaxDistance * random [0.1,0.7,1])]],[]] call BIS_fnc_randomPos);
          _marker setMarkerPos _newPos;

          {
            [_captureID + str _x, _marker] call BIS_fnc_taskSetDestination;
          } forEach phx_sidesInMission;
        };
        sleep _objMarkerUpdateTime;
      };
    };
  };
} forEach _objArr;

// [
//   {!phx_safetyEnabled},
//   {
//     {
//       _x setMarkerAlpha 1;
//     } forEach phx_scavHuntCapZones;
//   }
// ] call CBA_fnc_waitUntilAndExecute;



// Win conditions handled at end of timer -- fn_overTimeEnd.sqf