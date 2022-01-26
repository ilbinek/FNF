/*
Disables access to removing helmet and uniform. Ensures that the player has the helmet and uniform that they started the game with.
*/

if (isServer) exitWith {}; //Don't need to run this function for local testing
if (!isNil "phx_restrictions_handle_restrictUniform") then {
  [phx_restrictions_handle_restrictUniform] call CBA_fnc_removePerFrameHandler;
  phx_restrictions_handle_restrictUniform = nil;
};

private _playerUniform = uniform player;
private _playerHead = headgear player;
private _playerVest = vest player;

//Handle player not having the right uniform, vest, or helmet on
phx_restrictions_handle_restrictUniform = [{
  params ["_args","_handle"];
  _args params ["_playerUniform","_playerHead","_playerVest"];

  if !(uniform player isEqualTo _playerUniform) then {
    private ["_uniform", "_uniformItems", "_uniformMagazines"];
    _uniform = uniform player;
    _uniformItems = uniformItems player;
    _uniformMagazines = magazinesAmmoCargo (uniformContainer player);
    removeUniform player;

    player forceAddUniform _playerUniform;
    {
      if not (isClass (configFile >> "cfgMagazines" >> _x)) then {
        player addItemToUniform _x;
      };
    } foreach _uniformItems;

    {
      (uniformContainer player) addMagazineAmmoCargo [_x select 0, 1, _x select 1];
    } foreach _uniformMagazines;

  };

  if !(headgear player isEqualTo _playerHead) then {
    removeHeadgear player;
    player addHeadgear _playerHead;
  };
  /*
  if !(vest player isEqualTo _playerVest) then {
    _items = vestItems player;
    removeVest player;
    player addVest _playerVest;
    {player addItemToVest _x} forEach _items;
  };
  */
}, 5, [_playerUniform, _playerHead, _playerVest]] call CBA_fnc_addPerFrameHandler;

//Stop player from being able to take off gear
if !(isClass ((configOf player) >> "ACE_SelfActions" >> "ACE_Equipment" >> "ace_compat_sog_digSpiderhole")) then {
  // disable when SOG is loaded because items don't support it
  player addEventHandler ["InventoryOpened",{
    [{!(isNull (findDisplay 602))}, {
      //Uniform
      ((findDisplay 602) displayCtrl 6331) ctrlAddEventHandler ["mouseButtonDown", "ctrlEnable [6331, false];"];
      ((findDisplay 602) displayCtrl 6331) ctrlAddEventHandler ["mouseHolding", "ctrlEnable [6331, false];"];

      //Vest
      //((findDisplay 602) displayCtrl 6381) ctrlAddEventHandler ["mouseButtonDown", "ctrlEnable [6381, false];"];
      //((findDisplay 602) displayCtrl 6381) ctrlAddEventHandler ["mouseHolding", "ctrlEnable [6381, false];"];

      //Headgear
      ((findDisplay 602) displayCtrl 6240) ctrlAddEventHandler ["mouseButtonDown", "ctrlEnable [6240, false];"];
      ((findDisplay 602) displayCtrl 6240) ctrlAddEventHandler ["mouseHolding", "ctrlEnable [6240, false];"];
    }, [], 5] call CBA_fnc_waitUntilAndExecute;
  }];
};
