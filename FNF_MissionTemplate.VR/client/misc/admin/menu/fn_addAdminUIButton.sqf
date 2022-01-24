private _admin = false;
if ((getPlayerUID player) in (missionNamespace getVariable ["fnf_staffInfo",[]])) then {_admin = true};
if (serverCommandAvailable "#kick") then {_admin = true};
if (!_admin) exitWith {};

private _adminMenuButton = _display ctrlCreate ["FNF_AdminMenuButton", -1];
_adminMenuButton ctrlAddEventHandler ["ButtonClick", {
  phx_handle_adminMenu = [] spawn phx_admin_fnc_adminUI;
  [{scriptDone phx_handle_adminMenu}, {
    showChat true;
  }] call CBA_fnc_waitUntilAndExecute;
}];
