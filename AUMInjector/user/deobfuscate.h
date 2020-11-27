// This file contains deobfuscation mappings for different versions of the game

#pragma once
#include "il2cpp-appdata.h"
#include "version.h"

using namespace app;

// Deobfuscate game bindings, depending on version
#if GAME_VERSION == GAME_VERSION_2020_9_22s
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
	using InnerNetClient_GameState__Enum = DNAFMCDBMCI_JPCEFDHGHAK__Enum;
	using PlayerControl = GLHCHLEDNBA;
	using Player_Die_Reason__Enum = CCCHKEBONBN__Enum;
	using MeetingHud = GPOHFPAIEMA;
	using InnerNetClient = DNAFMCDBMCI;
	using InnerNet_DisconnectReasons__Enum = NCBONGGBCNE__Enum;
	using HqHudOverrideTask = MMPIJGKLMDC;
	using HudOverrideTask = GFBKIHICFNI;
	using ChatController = MLINJDBIIEC;
	using AmongUsClient = JNFEHNLGIFF;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Ended;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Started = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Started;
	#define PlayerControl_FixedUpdate_Trampoline GLHCHLEDNBA_FixedUpdate
	#define PlayerControl_GetTruePosition_Trampoline GLHCHLEDNBA_GetTruePosition
	#define PlayerControl_Die_Trampoline GLHCHLEDNBA_Die
	#define MeetingHud_Close_Trampoline GPOHFPAIEMA_Close
	#define MeetingHud_Start_Trampoline GPOHFPAIEMA_Start
	#define InnerNetClient_FixedUpdate_Trampoline DNAFMCDBMCI_FixedUpdate
	#define InnerNetClient_Disconnect_Trampoline DNAFMCDBMCI_GPKBCOKMFHK
	#define HqHudOverrideTask_Initialize_Trampoline MMPIJGKLMDC_Initialize
	#define HqHudOverrideTask_Complete_Trampoline MMPIJGKLMDC_Complete
	#define HudOverrideTask_Initialize_Trampoline GFBKIHICFNI_Initialize
	#define HudOverrideTask_Complete_Trampoline GFBKIHICFNI_Complete
	#define ChatController_AddChat_Trampoline MLINJDBIIEC_AddChat
	#define InnerNetClient_StartRpc_Trampoline DNAFMCDBMCI_StartRpc
	#define MessageWriter_Write_String_Trampoline MessageWriter_Write_6
	#define AmongUsClient_OnPlayerJoined_Trampoline JNFEHNLGIFF_IKDNNJNBKBO
#elif GAME_VERSION == GAME_VERSION_2020_11_4s
	using InnerNetClient_GameState__Enum = DBDDAJAICFN_DKEKFCCGGEO__Enum;
	using PlayerControl = APNNOJFGDGP;
	using Player_Die_Reason__Enum = LKBAAGPFMCB__Enum;
	using MeetingHud = APFHIONIINA;
	using InnerNetClient = DBDDAJAICFN;
	using InnerNet_DisconnectReasons__Enum = OBELNHOKKLD__Enum;
	using HqHudOverrideTask = OFCAMODPCOA;
	using HudOverrideTask = MHKPCHGHHOK;
	using ChatController = LOGKEMANPPL;
	using AmongUsClient = HJNEPPHDLBA;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = DBDDAJAICFN_DKEKFCCGGEO__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = DBDDAJAICFN_DKEKFCCGGEO__Enum_Ended;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Started = DBDDAJAICFN_DKEKFCCGGEO__Enum_Started;
	#define PlayerControl_FixedUpdate_Trampoline APNNOJFGDGP_FixedUpdate
	#define PlayerControl_GetTruePosition_Trampoline APNNOJFGDGP_GetTruePosition
	#define PlayerControl_Die_Trampoline APNNOJFGDGP_Die
	#define MeetingHud_Close_Trampoline APFHIONIINA_Close
	#define MeetingHud_Start_Trampoline APFHIONIINA_Start
	#define InnerNetClient_FixedUpdate_Trampoline DBDDAJAICFN_FixedUpdate
	#define InnerNetClient_Disconnect_Trampoline DBDDAJAICFN_LJKOGKNHGGA
	#define HqHudOverrideTask_Initialize_Trampoline OFCAMODPCOA_Initialize
	#define HqHudOverrideTask_Complete_Trampoline OFCAMODPCOA_Complete
	#define HudOverrideTask_Initialize_Trampoline MHKPCHGHHOK_Initialize
	#define HudOverrideTask_Complete_Trampoline MHKPCHGHHOK_Complete
	#define ChatController_AddChat_Trampoline LOGKEMANPPL_AddChat
	#define InnerNetClient_StartRpc_Trampoline DBDDAJAICFN_StartRpc
	#define MessageWriter_Write_String_Trampoline MessageWriter_Write_6
	#define AmongUsClient_OnPlayerJoined_Trampoline HJNEPPHDLBA_LKMONKFOADB
#elif GAME_VERSION == GAME_VERSION_2020_11_17s
	using Player_Die_Reason__Enum = EGEEFBOLHLP__Enum;
	using PlayerControl = PPHGCHMFMLI;
	using InnerNetClient = FIMOOCIGOAO;
	using InnerNetClient_GameState__Enum = FIMOOCIGOAO_KBCHFKCGJKG__Enum;
	using InnerNet_DisconnectReasons__Enum = GIDBHAMOKEA__Enum;
	using MeetingHud = ILMBELNBDMA;
	using HqHudOverrideTask = NPILPHBNAIC;
	using HudOverrideTask = OGOEIBLEPKK;
	using ChatController = KLDOCKJFNJL;
	using AmongUsClient = NJGFKJNAEMN;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = FIMOOCIGOAO_KBCHFKCGJKG__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Started = FIMOOCIGOAO_KBCHFKCGJKG__Enum_Started;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = FIMOOCIGOAO_KBCHFKCGJKG__Enum_Ended;
	#define PlayerControl_GetTruePosition_Trampoline PPHGCHMFMLI_GetTruePosition
	#define PlayerControl_Die_Trampoline PPHGCHMFMLI_Die
	#define PlayerControl_FixedUpdate_Trampoline PPHGCHMFMLI_FixedUpdate
	#define InnerNetClient_FixedUpdate_Trampoline FIMOOCIGOAO_FixedUpdate
	#define InnerNetClient_Disconnect_Trampoline FIMOOCIGOAO_OEIIMGAFPOO
	#define InnerNetClient_StartRpc_Trampoline FIMOOCIGOAO_StartRpc
	#define MeetingHud_Close_Trampoline ILMBELNBDMA_Close
	#define MeetingHud_Start_Trampoline ILMBELNBDMA_Start
	#define HqHudOverrideTask_Initialize_Trampoline NPILPHBNAIC_Initialize
	#define HqHudOverrideTask_Complete_Trampoline NPILPHBNAIC_Complete
	#define HudOverrideTask_Initialize_Trampoline OGOEIBLEPKK_Initialize
	#define HudOverrideTask_Complete_Trampoline OGOEIBLEPKK_Complete
	#define ChatController_AddChat_Trampoline KLDOCKJFNJL_AddChat
	#define AmongUsClient_OnPlayerJoined_Trampoline NJGFKJNAEMN_LOFILOLGOGD
	#define MessageWriter_Write_String_Trampoline MessageWriter_Write_6
#elif GAME_VERSION == GAME_VERSION_2020_11_17s_1
	using Player_Die_Reason__Enum = OOBDLHLDDAF__Enum;
	using PlayerControl = JENJGDMOEOC;
	using InnerNetClient = FMJPJKCNIKM;
	using InnerNetClient_GameState__Enum = FMJPJKCNIKM_ONHEJJJIKDI__Enum;
	using InnerNet_DisconnectReasons__Enum = CLFGKJHHBOK__Enum;
	using MeetingHud = NEOCOBOAGFJ;
	using HqHudOverrideTask = AFFPOFMFHEF;
	using HudOverrideTask = KALDPINPHCD;
	using ChatController = BPPJFAOEOMH;
	using AmongUsClient = MMMGPAPEEBJ;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = FMJPJKCNIKM_ONHEJJJIKDI__Enum_Joined;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Started = FMJPJKCNIKM_ONHEJJJIKDI__Enum_Started;
	InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = FMJPJKCNIKM_ONHEJJJIKDI__Enum_Ended;
	#define PlayerControl_GetTruePosition_Trampoline JENJGDMOEOC_GetTruePosition
	#define PlayerControl_Die_Trampoline JENJGDMOEOC_Die
	#define PlayerControl_FixedUpdate_Trampoline JENJGDMOEOC_FixedUpdate
	#define InnerNetClient_FixedUpdate_Trampoline FMJPJKCNIKM_FixedUpdate
	#define InnerNetClient_Disconnect_Trampoline FMJPJKCNIKM_AAKFLNMJNBJ
	#define InnerNetClient_StartRpc_Trampoline FMJPJKCNIKM_StartRpc
	#define MeetingHud_Close_Trampoline NEOCOBOAGFJ_Close
	#define MeetingHud_Start_Trampoline NEOCOBOAGFJ_Start
	#define HqHudOverrideTask_Initialize_Trampoline AFFPOFMFHEF_Initialize
	#define HqHudOverrideTask_Complete_Trampoline AFFPOFMFHEF_Complete
	#define HudOverrideTask_Initialize_Trampoline KALDPINPHCD_Initialize
	#define HudOverrideTask_Complete_Trampoline KALDPINPHCD_Complete
	#define AmongUsClient_OnPlayerJoined_Trampoline MMMGPAPEEBJ_NDONNDIFBON
	#define MessageWriter_Write_Byte_Trampoline MessageWriter_Write_1
	#define InnerNetClient_HandleGameDataInner_Trampoline FMJPJKCNIKM_AOAKDFPIOOA
#else
	#error Unknown game version!
#endif