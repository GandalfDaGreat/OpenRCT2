#pragma region Copyright (c) 2014-2017 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#pragma once

#include "../common.h"

struct rct_object_entry;

struct scenario_highscore_entry
{
    utf8 *      fileName;
    utf8 *      name;
    money32     company_value;
    datetime64  timestamp;
};

struct scenario_index_entry
{
    utf8    path[MAX_PATH];
    uint64  timestamp;

    // Category / sequence
    uint8   category;
    uint8   source_game;
    sint16  source_index;
    uint16  sc_id;

    // Objective
    uint8   objective_type;
    uint8   objective_arg_1;
    sint32  objective_arg_2;
    sint16  objective_arg_3;
    scenario_highscore_entry * highscore;
    
    utf8 internal_name[64]; // Untranslated name
    utf8 name[64];          // Translated name
    utf8 details[256];
};

namespace OpenRCT2
{
    interface IPlatformEnvironment;
}

interface IScenarioRepository
{
    virtual ~IScenarioRepository() = default;

    /**
     * Scans the scenario directories and grabs the metadata for all the scenarios.
     */
    virtual void Scan() abstract;

    virtual size_t GetCount() const abstract;
    virtual const scenario_index_entry * GetByIndex(size_t index) const  abstract;
    virtual const scenario_index_entry * GetByFilename(const utf8 * filename) const abstract;
	/**
	    * Does not return custom scenarios due to the fact that they may have the same name.
	    */
    virtual const scenario_index_entry * GetByInternalName(const utf8 * name) const abstract;
    virtual const scenario_index_entry * GetByPath(const utf8 * path) const abstract;

    virtual bool TryRecordHighscore(const utf8 * scenarioFileName, money32 companyValue, const utf8 * name) abstract;
};

IScenarioRepository * CreateScenarioRepository(OpenRCT2::IPlatformEnvironment * env);
IScenarioRepository * GetScenarioRepository();

void    scenario_repository_scan();
size_t  scenario_repository_get_count();
const   scenario_index_entry *scenario_repository_get_by_index(size_t index);
bool    scenario_repository_try_record_highscore(const utf8 * scenarioFileName, money32 companyValue, const utf8 * name);
void    scenario_translate(scenario_index_entry * scenarioEntry, const struct rct_object_entry * stexObjectEntry);
