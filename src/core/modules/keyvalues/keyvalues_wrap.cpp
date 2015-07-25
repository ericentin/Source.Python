/**
* =============================================================================
* Source Python
* Copyright (C) 2012-2015 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/

//---------------------------------------------------------------------------------
// Includes.
//---------------------------------------------------------------------------------
#include "export_main.h"
#include "modules/memory/memory_tools.h"
#include "tier1/KeyValues.h"
#include "modules/keyvalues/keyvalues.h"


//---------------------------------------------------------------------------------
// Forward declarations.
//---------------------------------------------------------------------------------
void export_keyvalues(scope);


//---------------------------------------------------------------------------------
// Declare the _keyvalues module.
//---------------------------------------------------------------------------------
DECLARE_SP_MODULE(_keyvalues)
{
	export_keyvalues(_keyvalues);
}


//---------------------------------------------------------------------------------
// Exports KeyValues.
//---------------------------------------------------------------------------------
void export_keyvalues(scope _keyvalues)
{
	class_<KeyValues,  boost::shared_ptr<KeyValues>, boost::noncopyable>("_KeyValues", no_init)
		.def("__init__", make_constructor(&KeyValuesExt::__init__1))
		.def("__init__", make_constructor(&KeyValuesExt::__init__2))
		.def("__init__", make_constructor(&KeyValuesExt::__init__3))
		.def("__init__", make_constructor(&KeyValuesExt::__init__4))
		.def("__init__", make_constructor(&KeyValuesExt::__init__5))

		.def("get_name",
			&KeyValues::GetName,
			"Returns the name of the keyvalues object."
		)

		.def("set_name", 
			&KeyValues::SetName,
			"Sets the name of the keyvalues object.",
			args("name")
		)

		.def("get_name_symbol",
			&KeyValues::GetNameSymbol,
			"Gets the name as a unique integer.",
			args("key_symbol")
		)

		.def("uses_escape_sequences",
			&KeyValues::UsesEscapeSequences,
			"Sets whether or not this keyvalues object uses escape sequences.",
			args("uses_escape_sequences")
		)

		.def("load_from_file",
			&KeyValuesExt::LoadFromFile,
			"Loads KeyValues data from a file into this KeyValues instance.",
			args("file_name")
		)

		.def("save_to_file",
			&KeyValuesExt::SaveToFile,
			args("file_name"),
			"Saves the data in this KeyValues instance to the given file path."
		)

		.def("find_key",
			GET_METHOD(KeyValues *, KeyValues, FindKey, const char *, bool),
			"Finds a KeyValue. Creates it if create_key is set.",
			("key_name", arg("create_key")=false),
			reference_existing_object_policy()
		)

		.def("find_key_by_symbol",
			GET_CONST_METHOD(KeyValues*, KeyValues, FindKey, int),
			"Finds a subkey by an integer identifier.",
			args("key"),
			reference_existing_object_policy()
		)

		.def("create_new_key",
			&KeyValues::CreateNewKey,
			"Creates a new child key with an autogenerated name. The name is guaranteed to be\
			an integer, of value 1 higher than the highest other integer key name.",
			reference_existing_object_policy()
		)
		
		.def("add_sub_key",
			&KeyValues::AddSubKey,
			"Adds a sub key. Make sure the subkey isn't a child of some other KeyValues.",
			args("sub_key")
		)

		.def("remove_sub_key",
			&KeyValues::RemoveSubKey,
			"Removes a subkey from the list. DOES NOT DELETE IT!",
			args("sub_key")
		)

		.def("get_first_sub_key",
			&KeyValues::GetFirstSubKey,
			"Returns the first subkey in the list. Will iterate over the keys AND the\
			values.",
			reference_existing_object_policy()
		)

		.def("get_next_key",
			&KeyValues::GetNextKey,
			"Returns the next subkey. Will iterate the keys AND the values.",
			reference_existing_object_policy()
		)

		.def("get_first_true_sub_key",
			&KeyValues::GetFirstTrueSubKey,
			"Returns the first subkey (both key and value).",
			reference_existing_object_policy()
		)

		.def("get_next_true_sub_key",
			&KeyValues::GetNextTrueSubKey,
			"Returns the next subkey (both key and value).",
			reference_existing_object_policy()
		)

		.def("get_first_value",
			&KeyValues::GetFirstValue,
			"Returns the first value in the tree.",
			reference_existing_object_policy()
		)

		.def("get_next_value",
			&KeyValues::GetNextValue,
			"Returns the next value in the tree.",
			reference_existing_object_policy()
		)

		.def("get_int",
			GET_METHOD(int, KeyValues, GetInt, const char *, int),
			"Returns the integer value for the given key name.",
			("key_name", arg("default_value")=0)
		)

		.def("get_uint64",
			GET_METHOD(uint64, KeyValues, GetUint64, const char *, uint64),
			"Gets the 64-bit integer value for the given key name.",
			("key_name", arg("default_value")=0)
		)

		.def("get_float",
			GET_METHOD(float, KeyValues, GetFloat, const char *, float),
			"Returns the floating point value for the given key name.",
			("key_name", arg("default_value")=0.0f)
		)

		.def("get_string",
			GET_METHOD(const char *, KeyValues, GetString, const char *, const char *),
			"Returns the string value for the given key name.",
			("key_name", arg("default_value")="")
		)

		.def("get_color",
			&KeyValuesExt::GetColor,
			"Returns the color value of the given key name.",
			("key_name", arg("default_value")=object())
		)

		.def("get_bool",
			&KeyValuesExt::GetBool,
			"Returns the boolean value for the given key name.",
			("key_name", arg("default_value")=false)
		)

		.def("is_empty",
			GET_METHOD(bool, KeyValues, IsEmpty, const char *),
			"Returns true if this key or the given key is empty.",
			(arg("key_name")=object())
		)

		.def("set_string",
			&KeyValues::SetString,
			"Sets the given key's string value.",
			args("key_name", "value")
		)

		.def("set_int",
			&KeyValues::SetInt,
			"Sets the given key's integer value.",
			args("key_name", "value")
		)

		.def("set_uint64",
			&KeyValues::SetUint64,
			"Sets the given key's 64-bit integer value.",
			args("key_name", "value")
		)

		.def("set_float",
			&KeyValues::SetFloat,
			"Sets the given key's floating point value.",
			args("key_name", "value")
		)

		.def("set_color",
			&KeyValues::SetColor,
			"Sets the given key's color value.",
			args("key_name", "value")
		)

		.def("set_bool",
			&KeyValuesExt::SetBool,
			"Sets the given key's boolean value.",
			args("key_name", "value")
		)

		ADD_MEM_TOOLS(KeyValues)
	;
}