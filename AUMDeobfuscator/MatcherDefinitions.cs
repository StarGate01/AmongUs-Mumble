using AUMDeobfuscator.Matchers;
using Microsoft.CodeAnalysis.CSharp.Syntax;
// ReSharper disable MemberCanBePrivate.Global

namespace AUMDeobfuscator
{
    internal static class MatcherDefinitions
    {
        public static class PlayerControl
        {
            public static readonly MethodMatch FixedUpdate =
                new MethodMatch(null!)
                    .WithTag("FixedUpdate")
                    .OfName("FixedUpdate")
                    .OfReturnType("void");
            
            public static readonly ClassMatch ClassPlayerControl =
                new ClassMatch()
                    .WithTag("PlayerControl")
                    .OfSuperClass(new ClassMatch().WithTag("PlayerControlBaseClass"))
                    .WithField()
                    .WithTag("MaxReportDistance")
                    .OfName("MaxReportDistance")
                    .OfType("float")
                    .And()
                    .WithMethod(FixedUpdate)
                    .And();

            

        }
        
    }
}