// This file contains deobfuscation mappings for different versions of the game

#pragma once
#include "il2cpp-appdata.h"

#define GAME_VERSION_2020_9_22s 20209220
#define GAME_VERSION_2020_10_22s 202010220
#define GAME_VERSION_2020_11_4s 202011040
#ifndef GAME_VERSION
	#define GAME_VERSION GAME_VERSION_2020_10_22s
#endif

using namespace app;

// Deobfuscate game bindings, depending on version
#if GAME_VERSION == GAME_VERSION_2020_9_22s
	#define version_text "2020.9.22s"
	using InnerNetClient_GameState__Enum = InnerNetClient_IFLBIJFJPMK__Enum;
	using Player_Die_Reason__Enum = NPLMBOLMMLB__Enum;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = InnerNetClient_IFLBIJFJPMK__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = InnerNetClient_IFLBIJFJPMK__Enum_Ended;
	#define PlayerControl_FixedUpdate_Trampoline PlayerControl_FixedUpdate
	#define PlayerControl_GetTruePosition_Trampoline PlayerControl_GetTruePosition
	#define PlayerControl_Die_Trampoline PlayerControl_Die
	#define MeetingHud_Close_Trampoline MeetingHud_Close
	#define MeetingHud_Start_Trampoline MeetingHud_Start
	#define InnerNetClient_FixedUpdate_Trampoline InnerNetClient_FixedUpdate
#elif GAME_VERSION == GAME_VERSION_2020_10_22s
	#define version_text "2020.10.22s"
	using InnerNetClient_GameState__Enum = DNAFMCDBMCI_JPCEFDHGHAK__Enum;
	using PlayerControl = GLHCHLEDNBA;
	using Player_Die_Reason__Enum = CCCHKEBONBN__Enum;
	using MeetingHud = GPOHFPAIEMA;
	using InnerNetClient = DNAFMCDBMCI;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Ended;
	#define PlayerControl_FixedUpdate_Trampoline GLHCHLEDNBA_FixedUpdate
	#define PlayerControl_GetTruePosition_Trampoline GLHCHLEDNBA_GetTruePosition
	#define PlayerControl_Die_Trampoline GLHCHLEDNBA_Die
	#define MeetingHud_Close_Trampoline GPOHFPAIEMA_Close
	#define MeetingHud_Start_Trampoline GPOHFPAIEMA_Start
	#define InnerNetClient_FixedUpdate_Trampoline DNAFMCDBMCI_FixedUpdate
#elif GAME_VERSION == GAME_VERSION_2020_11_4s
	#define version_text "2020.11.4s"
	using InnerNetClient_GameState__Enum = DBDDAJAICFN_DKEKFCCGGEO__Enum;
	using PlayerControl = APNNOJFGDGP;
	using Player_Die_Reason__Enum = LKBAAGPFMCB__Enum;
	using MeetingHud = LFBAPIAFCFM;
	using InnerNetClient = DBDDAJAICFN;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = DBDDAJAICFN_DKEKFCCGGEO__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = DBDDAJAICFN_DKEKFCCGGEO__Enum_Ended;
	#define PlayerControl_FixedUpdate_Trampoline APNNOJFGDGP_FixedUpdate
	#define PlayerControl_GetTruePosition_Trampoline APNNOJFGDGP_GetTruePosition
	#define PlayerControl_Die_Trampoline APNNOJFGDGP_Die
	#define MeetingHud_Close_Trampoline LFBAPIAFCFM_Close
	#define MeetingHud_Start_Trampoline LFBAPIAFCFM_Start
	#define InnerNetClient_FixedUpdate_Trampoline DBDDAJAICFN_FixedUpdate
#else
	#error Unknown game version!
#endif

#pragma message("Compiling for game version " version_text)