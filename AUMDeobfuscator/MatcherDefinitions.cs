using AUMDeobfuscator.Matchers;
using Microsoft.CodeAnalysis.CSharp.Syntax;
// ReSharper disable MemberCanBePrivate.Global

namespace AUMDeobfuscator
{
    internal static class MatcherDefinitions
    {
        public static class PlayerControl
        {

            public static readonly EnumMatch DieReason =
                new EnumMatch()
                    .WithTag("Player_Die_Reason")
                    .WithMember()
                    .OfName("Exile")
                    .OfValue("0")
                    .And();

            public static readonly MethodMatch GetTruePosition =
                new MethodMatch(null!)
                    .WithTag("GetTruePosition")
                    .OfName("GetTruePosition")
                    .WithNamedReturnType("Vector2");

            public static readonly MethodMatch Die =
                new MethodMatch(null!)
                    .WithTag("Die")
                    .WithModifier("public")
                    .WithNamedReturnType("void")
                    .OfName("Die");
            
            public static readonly MethodMatch FixedUpdate =
                new MethodMatch(null!)
                    .WithTag("FixedUpdate")
                    .OfName("FixedUpdate")
                    .WithNamedReturnType("void");
            
            public static readonly ClassMatch ClassPlayerControl =
                new ClassMatch()
                    .WithTag("PlayerControl")
                    .OfSuperClass(new ClassMatch().WithTag("PlayerControlBaseClass"))
                    .WithField()
                    .WithTag("MaxReportDistance")
                    .OfName("MaxReportDistance")
                    .WithNamedType("float")
                    .And()
                    .WithMethod(FixedUpdate)
                    .And()
                    .WithMethod(GetTruePosition)
                    .And()
                    .WithMethod(Die)
                    .And();


            


        }

        public static class InnerNetClient
        {

            public static readonly EnumValueMatch Joined = 
                new EnumValueMatch(null!)
                    .OfName("Joined")
                    .OfValue("1");
            
            public static readonly EnumValueMatch Started = 
                new EnumValueMatch(null!)
                    .OfName("Started")
                    .OfValue("2");
            
            public static readonly EnumValueMatch Ended = 
                new EnumValueMatch(null!)
                    .OfName("Ended")
                    .OfValue("3");

            

            public static readonly MethodMatch FixedUpdate =
                new MethodMatch(null!)
                    .OfName("FixedUpdate")
                    .WithTag("FixedUpdate")
                    .WithNamedReturnType("void");

            public static readonly MethodMatch Disconnect =
                new MethodMatch(null!)
                    .WithTag("Disconnect")
                    .WithNamedReturnType("void")
                    .WithModifier("protected")
                    .WithParameter()
                    .WithNamedType("string")
                    .WithDefaultValue("null")
                    .And()
                    .WithParameter()
                    .WithType(new EnumMatch().WithMember().OfName("Kicked").And())
                    .And();

            public static readonly MethodMatch HandleGameDataInner =
                new MethodMatch(null!)
                    .WithTag("HandleGameDataInner")
                    .WithParameter()
                    .WithNamedType("MessageReader")
                    .And()
                    .WithParameter()
                    .WithNamedType("int")
                    .And()
                    .WithNumberOfParameters(2);

            public static readonly MethodMatch StartRPC =
                new MethodMatch(null!)
                    .WithTag("StartRpc")
                    .WithModifier("public")
                    .WithNamedReturnType("MessageWriter")
                    .WithParameter()
                    .WithNamedType("uint")
                    .And()
                    .WithParameter()
                    .WithNamedType("byte")
                    .And()
                    .WithParameter()
                    .And()
                    .WithNumberOfParameters(3);

            public static readonly ClassMatch ClassInnerNetClient =
                new ClassMatch()
                    .WithTag("InnerNetClient")
                    .OfNamedSuperClass("MonoBehaviour")
                    .WithMethod(Disconnect)
                    .And()
                    .WithMethod(FixedUpdate)
                    .And()
                    .WithMethod(HandleGameDataInner)
                    .And()
                    .WithMethod(StartRPC)
                    .And();

            public static readonly EnumMatch GameState =
                new EnumMatch()
                    .WithTag("InnerNetClient_GameState")
                    .WithMember(Joined)
                    .WithMember(Started)
                    .WithMember(Ended);

            public static readonly EnumMatch DisconnectReasons =
                new EnumMatch()
                    .WithTag("InnerNet_DisconnectReasons")
                    .WithMember()
                    .OfName("ExitGame")
                    .OfValue("0")
                    .And()
                    .WithMember()
                    .OfName("GameFull")
                    .OfValue("1")
                    .And()
                    .WithMember()
                    .OfName("GameStarted")
                    .OfValue("2")
                    .And();

        }

        public static class MeetingHud
        {

            public static readonly MethodMatch Close =
                new MethodMatch(null!)
                    .WithTag("Close")
                    .OfName("Close")
                    .WithModifier("public")
                    .WithNumberOfParameters(0);
            
            public static readonly MethodMatch Start =
                new MethodMatch(null!)
                    .WithTag("Start")
                    .OfName("Start")
                    .WithModifier("private")
                    .WithNumberOfParameters(0);
            
            public static readonly ClassMatch ClassMeetingHud =
                new ClassMatch()
                    .WithTag("MeetingHud")
                    .WithField()
                    .WithNamedType("Vector3")
                    .OfName("VoteOrigin")
                    .And()
                    .WithMethod(Close)
                    .And()
                    .WithMethod(Start)
                    .And();
        }

        public static class HqHudOverrideTask
        {

            public static readonly MethodMatch Initialize =
                new MethodMatch(null!)
                    .WithTag("Initialize")
                    .OfName("Initialize");
            
            public static readonly MethodMatch Complete =
                new MethodMatch(null!)
                    .WithTag("Complete")
                    .OfName("Complete");


            public static readonly ClassMatch ClassHqHutOverrideTask =
                new ClassMatch()
                    .WithTag("HqHudOverrideTask")
                    .WithMethod(Initialize)
                    .And()
                    .WithMethod(Complete)
                    .And()
                    .WithField()
                    .WithType(new ClassMatch().WithField().WithNamedType("HashSet<Tuple<byte, byte>>").And())
                    .And()
                    .OfSuperClassCount(2);
            
        }

        public static class HudOverrideTask
        {
            public static readonly MethodMatch Initialize =
                new MethodMatch(null!)
                    .WithTag("Initialize")
                    .OfName("Initialize");
            
            public static readonly MethodMatch Complete =
                new MethodMatch(null!)
                    .WithTag("Complete")
                    .OfName("Complete");
            
            public static readonly ClassMatch ClassHudOverrideTask =
                new ClassMatch()
                    .WithTag("HudOverrideTask")
                    .WithMethod(Initialize)
                    .And()
                    .WithMethod(Complete)
                    .And()
                    .WithField()
                    .WithType(new ClassMatch().WithMethod().WithNumberOfParameters(2).WithParameter().WithNamedType("MessageReader").And().And()) 
                    .And()
                    .OfSuperClassCount(2);
        }

        public static class ChatController
        {

            public static readonly MethodMatch AddChat =
                new MethodMatch(null!)
                    .WithTag("AddChat")
                    .OfName("AddChat")
                    .WithNumberOfParameters(2);
            
            public static ClassMatch ClassChatController =
                new ClassMatch()
                    .WithTag("ChatController")
                    .WithField()
                    .OfName("chatBubPool")
                    .And()
                    .WithMethod(AddChat)
                    .And();
            
            
        }

        public static class AmongUsClient
        {
            public static readonly MethodMatch OnPlayerJoined =
                new MethodMatch(null!)
                    .WithTag("OnPlayerJoined")
                    .WithModifier("private")
                    .WithNamedReturnType("void")
                    .WithNumberOfParameters(1)
                    .WithParameter()
                    .WithNamedType("ClientData")
                    .And();
            
            public static readonly ClassMatch ClassAmongUsClient =
                new ClassMatch()
                    .WithTag("AmongUsClient")
                    .WithField()
                    .OfName("Instance")
                    .And()
                    .WithField()
                    .OfName("MainMenuScene")
                    .WithNamedType("string")
                    .And()
                    .WithMethod(OnPlayerJoined)
                    .And();
        }
    }
}