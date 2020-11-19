using System.Collections.Generic;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator
{
    internal static class Program
    {

        public const bool Debug = false;
        
        private static void Main(string[] args)
        {
            // parsing all classes
            Parser.AddAllClassesIn(Path);
            
            //Search for classes
            List<ClassDeclarationSyntax> cl = Searching.SearchFor(MatcherDefinitions.IsPlayerControl);
            Searching.DisplayMatches("PlayerControl",cl);
            
            
        }

        public const string SearchFolder = "Assembly-CSharp";

        private const string Path = @"Sources";
    }
}