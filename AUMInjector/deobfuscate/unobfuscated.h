using InnerNetClient = InnerNetClient;
using InnerNetClient_GameState__Enum = InnerNetClient_GameStates__Enum;
using InnerNet_DisconnectReasons__Enum = DisconnectReasons__Enum;
using Player_Die_Reason__Enum = DeathReason__Enum;
using PlayerControl = PlayerControl;
#define PlayerControl__TypeInfo PlayerControl__TypeInfo
using GameData = GameData;
#define Palette__TypeInfo Palette__TypeInfo
using MeetingHud = MeetingHud;
using HqHudOverrideTask = HqHudOverrideTask;
using HudOverrideTask = HudOverrideTask;
using ChatController = ChatController;
using AmongUsClient = AmongUsClient;
using PlayerInfo = GameData_PlayerInfo;
using ModManager = ModManager;
#define PlayerControl_GetTruePosition_Trampoline PlayerControl_GetTruePosition
#define PlayerControl_Die_Trampoline PlayerControl_Die
#define PlayerControl_GetData_Trampoline PlayerControl_get_Data
#define PlayerControl_FixedUpdate_Trampoline PlayerControl_FixedUpdate

__declspec(selectany) InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = InnerNetClient_GameStates__Enum::Joined;
__declspec(selectany) InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Started = InnerNetClient_GameStates__Enum::Started;
__declspec(selectany) InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = InnerNetClient_GameStates__Enum::Ended;

__declspec(selectany) Color32__Array* Palette__StaticFields::* PlayerColors = &Palette__StaticFields::PlayerColors;
__declspec(selectany) LightSource* PlayerControl__Fields::* MyLight = &PlayerControl__Fields::myLight;

#define GameData_Awake_Trampoline GameData_Awake
#define GameData_GetPlayerById_Trampoline GameData_GetPlayerById
#define GameData_UpdateColor_Trampoline GameData_UpdateColor
#define GameData_GetPlayerCount_Trampoline GameData_get_PlayerCount
#define GameData_HandleDisconnect_Trampoline GameData_HandleDisconnect
#define GameData_CompleteTask_Trampoline GameData_CompleteTask
#define InnerNetClient_FixedUpdate_Trampoline InnerNetClient_FixedUpdate
#define InnerNetClient_Disconnect_Trampoline InnerNetClient_DisconnectInternal
#define InnerNetClient_HandleGameData_Trampoline InnerNetClient_HandleGameData
#define InnerNetClient_StartRpc_Trampoline InnerNetClient_StartRpc
#define MeetingHud_Close_Trampoline MeetingHud_Close
#define MeetingHud_Start_Trampoline MeetingHud_Start
#define HqHudOverrideTask_Initialize_Trampoline HqHudOverrideTask_Initialize
#define HqHudOverrideTask_Complete_Trampoline HqHudOverrideTask_Complete
#define HudOverrideTask_Initialize_Trampoline HudOverrideTask_Initialize
#define HudOverrideTask_Complete_Trampoline HudOverrideTask_Complete
#define MessageWriter_Write_Byte_Trampoline MessageWriter_Write_1
#define AmongUsClient_OnPlayerJoined_Trampoline AmongUsClient_OnPlayerJoined
#define ModManager_LateUpdate ModManager_LateUpdate
#define ModManager_ShowModStamp ModManager_ShowModStamp