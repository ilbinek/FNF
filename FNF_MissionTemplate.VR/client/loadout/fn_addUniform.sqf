player forceAddUniform phx_loadout_uniform;
player addVest phx_loadout_vest;
player addBackpack phx_loadout_backpack;
player addHeadgear phx_loadout_headgear;

if (!phx_customLoadouts) then {
  clearAllItemsFromBackpack player; //Some Massi backpacks add items that we dont want
};