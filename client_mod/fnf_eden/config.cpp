class CfgPatches
{
  class fnf_eden
  {
    units[] = {"fnf_module_init", "fnf_module_playZone", "fnf_module_safeZone", "fnf_module_hidingZone", "fnf_module_selectorHost", "fnf_module_selectorOption", "fnf_module_breifingAssets", "fnf_module_destroyObj", "fnf_module_sectorCaptureObj", "fnf_module_sectorHoldObj"};
    weapons[] = {};
    requiredVersion = 0.1;
    requiredAddons[] = {"A3_Modules_F", "cba_main", "ace_arsenal"}; //This is just to get the FNF section to the bottom of the attributes list
  };
};

class CfgFactionClasses
{
	class NO_CATEGORY;
	class fnf_standardCategory: NO_CATEGORY
	{
		displayName = "FNF";
	};
};

class CfgVehicles
{
	class Logic;
	class Module_F: Logic
	{
		class AttributesBase
		{
			class Default;
			class Edit;					// Default edit box (i.e. text input field)
			class Combo;				// Default combo box (i.e. drop-down menu)
			class Checkbox;				// Default checkbox (returned value is Boolean)
			class CheckboxNumber;		// Default checkbox (returned value is Number)
			class ModuleDescription;	// Module description
			class Units;				// Selection of units on which the module is applied
		};

		// Description base classes (for more information see below):
		class ModuleDescription
		{
			class AnyBrain;
		};
	};

  class fnf_module_init: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Init";
    scope = 2;

    class Attributes: AttributesBase
    {
      class GameTime: Edit
      {
        property = "fnf_gameTime";
        expression = "_this setVariable ['fnf_gameTime',_value, true];";
        displayName = "Time Limit";
        typeName = "NUMBER";
				defaultValue = "65";
      };
      class ViewDistance: Edit
      {
        property = "fnf_viewDistance";
        expression = "_this setVariable ['fnf_viewDistance',_value, true];";
        displayName = "View Distance";
        typeName = "NUMBER";
				defaultValue = "1000";
      };
      class FortifyPoints: Edit
      {
        property = "fnf_fortifyPoints";
        expression = "_this setVariable ['fnf_fortifyPoints',_value, true];";
        displayName = "Fortify Points";
        typeName = "NUMBER";
				defaultValue = "100";
      };
      class FortifyColour: Combo
      {
        property = "fnf_fortifyColour";
        expression = "_this setVariable ['fnf_fortifyColour',_value, true];";
        displayName = "Fortify Colour";
        typeName = "STRING";
				defaultValue = Green;
        class Values
        {
          class Green { name = "Green"; value = "Green";};
          class Tan { name = "Tan"; value = "Tan";};
        };
      };
      class BreifingNotes
      {
        control = "EditMulti5";
				property = "fnf_breifingNotes";
        expression = "_this setVariable ['fnf_breifingNotes',_value, true];";
				displayName = "Notes";
				typeName = "STRING";
				defaultValue = "";
      };
      class BreifingAO
      {
        control = "EditMulti5";
				property = "fnf_breifingAO";
        expression = "_this setVariable ['fnf_breifingAO',_value, true];";
				displayName = "Area of Operations";
				typeName = "STRING";
				defaultValue = "";
      };
      class BreifingBackground
      {
        control = "EditMulti5";
				property = "fnf_breifingBackground";
        expression = "_this setVariable ['fnf_breifingBackground',_value, true];";
				displayName = "Background";
				typeName = "STRING";
				defaultValue = "";
      };
      class BreifingRules
      {
        control = "EditMulti5";
				property = "fnf_breifingRules";
        expression = "_this setVariable ['fnf_breifingRules',_value, true];";
				displayName = "Mission Rules";
				typeName = "STRING";
				defaultValue = "";
      };
      class Debug: Checkbox
      {
        property = "fnf_debug";
        expression = "_this setVariable ['fnf_debug',_value, true];";
        displayName = "Debug";
        tooltip = "If checked, debug data will be shown";
        typeName = "BOOL";
        defaultValue = "false";
      };
    };
	};
	class fnf_module_playZone: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Play Zone";
    scope = 2;
    class Attributes: AttributesBase
    {
      class Prefix: Edit
      {
        property = "fnf_prefix";
        expression = "_this setVariable ['fnf_prefix',_value, true];";
        displayName = "Marker Prefix";
        typeName = "STRING";
				defaultValue = "fnf_marker_playzone_";
      };
    };
	};
  class fnf_module_safeZone: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Safe Zone";
    scope = 2;
    class Attributes: AttributesBase
    {
      class Prefix: Edit
      {
        property = "fnf_prefix";
        expression = "_this setVariable ['fnf_prefix',_value, true];";
        displayName = "Marker Prefix";
        typeName = "STRING";
				defaultValue = "fnf_marker_safezone_";
      };
      class TimeToBeDeleted: Edit
      {
        property = "fnf_timeZoneIsDeleted";
        expression = "_this setVariable ['fnf_timeZoneIsDeleted',_value, true];";
        displayName = "Time until Zone is Deleted";
        typeName = "NUMBER";
				defaultValue = "15";
      };
      class VisibleToAllies: Checkbox
      {
        property = "fnf_visibleToAllies";
        expression = "_this setVariable ['fnf_visibleToAllies',_value, true];";
        displayName = "Visible to Allies";
        typeName = "BOOL";
        defaultValue = "true";
      };
      class VisibleToEnemies: Checkbox
      {
        property = "fnf_visibleToEnemies";
        expression = "_this setVariable ['fnf_visibleToEnemies',_value, true];";
        displayName = "Visible to Enemies";
        typeName = "BOOL";
        defaultValue = "true";
      };
    };
	};
  class fnf_module_hidingZone: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Hiding Zone";
    scope = 2;
    class Attributes: AttributesBase
    {
      class Prefix: Edit
      {
        property = "fnf_prefix";
        expression = "_this setVariable ['fnf_prefix',_value, true];";
        displayName = "Marker Prefix";
        typeName = "STRING";
				defaultValue = "fnf_marker_hidingzone_";
      };
    };
	};
  class fnf_module_selectorHost: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Selector";
    scope = 2;
    class Attributes: AttributesBase
    {
      class SelectorName: Edit
      {
        property = "fnf_selectorName";
        expression = "_this setVariable ['fnf_selectorName',_value, true];";
        displayName = "Selector Name";
        typeName = "STRING";
				defaultValue = "";
      };
      class ObjectiveType: Combo
      {
        property = "fnf_selectorType";
        expression = "_this setVariable ['fnf_selectorType',_value, true];";
        displayName = "Selector Type";
        typeName = "STRING";
				defaultValue = Item;
        class Values
        {
          class Item { name = "Item"; value = "itm";};
          class Optic { name = "Optic"; value = "opt";};
          class PrimaryWeapon { name = "Primary Weapon"; value = "pri";};
          class SecondaryWeapon { name = "Launcher"; value = "sec";};
          class Handgun { name = "Handgun"; value = "hnd";};
        };
      };
    };
	};
  class fnf_module_selectorOption: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Selector Option";
    scope = 2;
    class Attributes: AttributesBase
    {
      class OptionName: Edit
      {
        property = "fnf_optionName";
        expression = "_this setVariable ['fnf_optionName',_value, true];";
        displayName = "Option Name";
        typeName = "STRING";
				defaultValue = "";
      };
      class DefaultSelection: Checkbox
      {
        property = "fnf_defaultSelection";
        expression = "_this setVariable ['fnf_defaultSelection',_value, true];";
        displayName = "Default?";
        tooltip = "If checked, this option will be treated as already selected";
        typeName = "BOOL";
        defaultValue = "false";
      };
    };
  };
  class fnf_module_breifingAssets: Module_F
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Breifing Assets";
    scope = 2;
	};
  class fnf_module_objective: Module_F {};
  class fnf_module_destroyObj: fnf_module_objective
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Destroy Objective";
    scope = 2;
    class Attributes: AttributesBase
    {
      class ObjectiveType: Combo
      {
        property = "fnf_objectiveType";
        expression = "_this setVariable ['fnf_objectiveType',_value, true];";
        displayName = "Objective Type";
        typeName = "STRING";
				defaultValue = Destroy;
        class Values
        {
          class Destroy { name = "Destroy Object"; value = "des";};
          class Protect { name = "Protect Object"; value = "pro";};
        };
      };
      class ZoneKnown: Checkbox
      {
        property = "fnf_zoneKnown";
        expression = "_this setVariable ['fnf_zoneKnown',_value, true];";
        displayName = "Is hiding zone known";
        tooltip = "If checked, when object is in a linked hiding zone the zone it is in will have the task attached to it";
        typeName = "BOOL";
        defaultValue = "true";
      };
    };
	};
  class fnf_module_sectorCaptureObj: fnf_module_objective
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Capture Sector Objective";
    scope = 2;
    class Attributes: AttributesBase
    {
      class ObjectiveType: Combo
      {
        property = "fnf_objectiveType";
        expression = "_this setVariable ['fnf_objectiveType',_value, true];";
        displayName = "Objective Type";
        typeName = "STRING";
				defaultValue = "cap";
        class Values
        {
          class Capture { name = "Capture Sector"; value = "cap";};
          class Defend { name = "Defend Sector"; value = "def";};
        };
      };
      class Prefix: Edit
      {
        property = "fnf_prefix";
        expression = "_this setVariable ['fnf_prefix',_value, true];";
        displayName = "Marker Prefix";
        typeName = "STRING";
				defaultValue = "fnf_marker_sector_";
      };
      class TimeToCapture: Edit
      {
        property = "fnf_TimeToCapture";
        expression = "_this setVariable ['fnf_TimeToCapture',_value, true];";
        displayName = "Time to Capture";
        typeName = "NUMBER";
				defaultValue = "60";
      };
    };
	};
  class fnf_module_sectorHoldObj: fnf_module_objective
	{
		author = "Mallen";
    category = "fnf_standardCategory";
    displayName = "FNF Hold Sector Objective";
    scope = 2;
    class Attributes: AttributesBase
    {
      class ObjectiveType: Combo
      {
        property = "fnf_objectiveType";
        expression = "_this setVariable ['fnf_objectiveType',_value, true];";
        displayName = "Objective Type";
        typeName = "STRING";
				defaultValue = "cap";
        class Values
        {
          class Capture { name = "Capture Sector"; value = "cap";};
          class Defend { name = "Defend Sector"; value = "def";};
        };
      };
    };
	};
};

class CfgEditorCategories
{
	class fnf_Kits
	{
		displayName = "FNF - Kits";
	};
  class fnf_Objectives
	{
		displayName = "FNF - Objectives";
	};
  class fnf_Systems
	{
		displayName = "FNF - Systems";
	};
};

class CfgEditorSubcategories
{
	class fnf_Blufor
	{
		displayName = "Blufor";
	};
  class fnf_Opfor
	{
		displayName = "Opfor";
	};
  class fnf_Indfor
	{
		displayName = "Independant";
	};
  class fnf_CaptureSector
	{
		displayName = "Capture Sector";
	};
  class fnf_Destroy
	{
		displayName = "Destroy Object";
	};
  class fnf_SafeZones
	{
		displayName = "Safe Zones";
	};
  class fnf_PlayZones
	{
		displayName = "Play Zones";
	};
  class fnf_HidingZones
	{
		displayName = "Hiding Zones";
	};
};

class Cfg3DEN
{
  class Compositions
	{
    //play zones

    class fnf_PlayZone_1 // one class per composition
		{
			path = "fnf_eden\systems\PlayZonePreset[1]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_PlayZones";				// link to CfgEditorSubcategories
			displayName = "Play Zone Preset [ 1 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_PlayZone_2 // one class per composition
		{
			path = "fnf_eden\systems\PlayZonePreset[2]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_PlayZones";				// link to CfgEditorSubcategories
			displayName = "Play Zone Preset [ 2 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_PlayZone_3 // one class per composition
		{
			path = "fnf_eden\systems\PlayZonePreset[3]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_PlayZones";				// link to CfgEditorSubcategories
			displayName = "Play Zone Preset [ 3 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    //hiding zones

    class fnf_HidingZone_1 // one class per composition
		{
			path = "fnf_eden\systems\HidingZonePreset[1]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_HidingZones";				// link to CfgEditorSubcategories
			displayName = "Hiding Zone Preset [ 1 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_HidingZone_2 // one class per composition
		{
			path = "fnf_eden\systems\HidingZonePreset[2]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_HidingZones";				// link to CfgEditorSubcategories
			displayName = "Hiding Zone Preset [ 2 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_HidingZone_3 // one class per composition
		{
			path = "fnf_eden\systems\HidingZonePreset[3]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_HidingZones";				// link to CfgEditorSubcategories
			displayName = "Hiding Zone Preset [ 3 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    //safe zones

    class fnf_BluforSafeZone_1 // one class per composition
		{
			path = "fnf_eden\systems\(Blufor)SafeZonePreset[1]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Blufor) Safe Zone Preset [ 1 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_BluforSafeZone_2 // one class per composition
		{
			path = "fnf_eden\systems\(Blufor)SafeZonePreset[2]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Blufor) Safe Zone Preset [ 2 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_BluforSafeZone_3 // one class per composition
		{
			path = "fnf_eden\systems\(Blufor)SafeZonePreset[3]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Blufor) Safe Zone Preset [ 3 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    class fnf_IndforSafeZone_1 // one class per composition
		{
			path = "fnf_eden\systems\(Indfor)SafeZonePreset[1]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Indfor) Safe Zone Preset [ 1 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_IndforSafeZone_2 // one class per composition
		{
			path = "fnf_eden\systems\(Indfor)SafeZonePreset[2]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Indfor) Safe Zone Preset [ 2 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_IndforSafeZone_3 // one class per composition
		{
			path = "fnf_eden\systems\(Indfor)SafeZonePreset[3]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Indfor) Safe Zone Preset [ 3 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    class fnf_OpforSafeZone_1 // one class per composition
		{
			path = "fnf_eden\systems\(Opfor)SafeZonePreset[1]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Opfor) Safe Zone Preset [ 1 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_OpforSafeZone_2 // one class per composition
		{
			path = "fnf_eden\systems\(Opfor)SafeZonePreset[2]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Opfor) Safe Zone Preset [ 2 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_OpforSafeZone_3 // one class per composition
		{
			path = "fnf_eden\systems\(Opfor)SafeZonePreset[3]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Systems";						// link to CfgEditorCategories
			editorSubcategory = "fnf_SafeZones";				// link to CfgEditorSubcategories
			displayName = "(Opfor) Safe Zone Preset [ 3 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    //objectives

    class fnf_DestroyObjective // one class per composition
		{
			path = "fnf_eden\objectives\DestroyObjectivePreset";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Objectives";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Destroy";				// link to CfgEditorSubcategories
			displayName = "Destroy Objective Preset";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    class fnf_CaptureSectorObjective_1 // one class per composition
		{
			path = "fnf_eden\objectives\CaptureSectorObjectivePreset[1]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Objectives";						// link to CfgEditorCategories
			editorSubcategory = "fnf_CaptureSector";				// link to CfgEditorSubcategories
			displayName = "Capture Sector Objective Preset [ 1 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_CaptureSectorObjective_2 // one class per composition
		{
			path = "fnf_eden\objectives\CaptureSectorObjectivePreset[2]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Objectives";						// link to CfgEditorCategories
			editorSubcategory = "fnf_CaptureSector";				// link to CfgEditorSubcategories
			displayName = "Capture Sector Objective Preset [ 2 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_CaptureSectorObjective_3 // one class per composition
		{
			path = "fnf_eden\objectives\CaptureSectorObjectivePreset[3]";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;
			editorCategory = "fnf_Objectives";						// link to CfgEditorCategories
			editorSubcategory = "fnf_CaptureSector";				// link to CfgEditorSubcategories
			displayName = "Capture Sector Objective Preset [ 3 ]";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};

    //#################################################################################################################################
    //KITS START HERE
    //#################################################################################################################################

		/*class fnf_NATOUSArmy2020 // one class per composition
		{
			path = "fnf_eden\kits_blufor\[NATO]USArmy(2020)";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Blufor";				// link to CfgEditorSubcategories
			displayName = "[NATO] US Army (2020)";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_RURussianMSV2020 // one class per composition
		{
			path = "fnf_eden\kits_opfor\[RU]RussianMSV(2020)";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Opfor";				// link to CfgEditorSubcategories
			displayName = "[RU] Russian MSV (2020)";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_INDFORSyrianArmy2020_indfor // one class per composition
		{
			path = "fnf_eden\kits_indfor\[INDFOR]SyrianArmy(2020)";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Indfor";				// link to CfgEditorSubcategories
			displayName = "[INDFOR] Syrian Army (2020)";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    /*class fnf_INDFORSyrianArmy2020_opfor // one class per composition
		{
			path = "fnf_eden\kits_indfor\[INDFOR]SyrianArmy(2020)";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Opfor";				// link to CfgEditorSubcategories
			displayName = "[INDFOR] Syrian Army (2020)";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_INDFORSyrianArmy2020_blufor // one class per composition
		{
			path = "fnf_eden\kits_indfor\[INDFOR]SyrianArmy(2020)";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Blufor";				// link to CfgEditorSubcategories
			displayName = "[INDFOR] Syrian Army (2020)";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};*/
    class fnf_WW2Germany // one class per composition
		{
			path = "fnf_eden\kits_blufor\[WW2]Germany";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Blufor";				// link to CfgEditorSubcategories
			displayName = "[WW2] Germany";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_WW2SovietWinter // one class per composition
		{
			path = "fnf_eden\kits_opfor\[WW2]SovietWinter(EARLY)";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Opfor";				// link to CfgEditorSubcategories
			displayName = "[WW2] Soviet Winter (EARLY)";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_WW2NorwegianArmy // one class per composition
		{
			path = "fnf_eden\kits_indfor\[WW2]NorwegianArmy";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Indfor";				// link to CfgEditorSubcategories
			displayName = "[WW2] Norwegian Army";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
    class fnf_WW2FinnishJaegers // one class per composition
		{
			path = "fnf_eden\kits_blufor\[WW2]FinnishJaegers";	// pbo path to a folder containing header.sqe/composition.sqe files
			side = 8;											// 0 opfor, 1 blufor, 2 indfor, 3 civ, 8 Empty/Props
			editorCategory = "fnf_Kits";						// link to CfgEditorCategories
			editorSubcategory = "fnf_Blufor";				// link to CfgEditorSubcategories
			displayName = "[WW2] Finnish Jaegers";
			useSideColorOnIcon = 1;								// 1 == icon is always colored in faction color
		};
	};



  class Object
  {
    class AttributeCategories
    {
      class fnf_properties
      {
        displayName = "FNF Properties";
        collapsed = 1;
        class Attributes
        {
          class fnf_autoMarkExclude
          {
            property = "FNF_MarkingExclude";
            control = "Checkbox";
            displayName = "Exclude from Map Auto-Mark";
            tooltip = "If checked, this object will be excluded from the FNF custom object marking script.";
            expression = "_this setVariable ['%s',_value, true];";
            typeName = "BOOL";
            condition = "1 - objectControllable - objectVehicle";
            defaultValue = "false";
          };
          class fnf_clearInventory
          {
            property = "FNF_InventoryAutoClear";
            control = "Checkbox";
            displayName = "Clear Inventory";
            tooltip = "If checked, the vehicle's inventory will be cleared.";
            expression = "_this setVariable ['%s',_value, true];";
            typeName = "BOOL";
            condition = "objectVehicle";
            defaultValue = "true";
          };
          class fnf_vehicleLoadouts_useDefault
          {
            property = "FNF_vehicleLoadouts_useDefault";
            control = "Checkbox";
            displayName = "Use Default Loadout";
            tooltip = "If checked, the vehicle will be given a standardized FNF weapon set (if one is defined).";
            expression = "_this setVariable ['%s',_value, true];";
            typeName = "BOOL";
            condition = "objectVehicle";
            defaultValue = "true";
          };
        };
      };
    };
  };
};
