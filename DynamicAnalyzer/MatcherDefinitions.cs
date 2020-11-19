using AUMDeobfuscator.Matchers;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator
{
    internal static class MatcherDefinitions
    {
        public static bool IsPlayerControl(ClassDeclarationSyntax? cls)
        {

            if (cls == null) return false;

            ClassMatchChain matchChain = new ClassMatchChain()
                .WithTag("PlayerControl")
                .OfSuperClass(new ClassMatchChain().WithTag("PlayerControlBaseClass"))
                .WithField()
                .OfName("MaxReportDistance")
                .OfType("float")
                .And()
                .WithMethod()
                .OfNameContains("FixedUpdate")
                .And();

            return matchChain.Matches(cls);
        }
    }
}