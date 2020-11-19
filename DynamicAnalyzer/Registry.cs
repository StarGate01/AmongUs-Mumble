using System.Collections.Generic;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator
{
    public static class Registry
    {
        private static readonly Dictionary<string,ClassDeclarationSyntax> Classes = new();
        public static readonly Dictionary<string,ClassDeclarationSyntax> AssemblyCs = new();
        public static ClassDeclarationSyntax? GetClass(string name)
        {
            return Classes.GetValueOrDefault(name);
        }

        public static bool Add(ClassDeclarationSyntax cl, bool asscs = false)
        {
            if (Classes.ContainsKey(cl.Identifier.ToString()) || AssemblyCs.ContainsKey(cl.Identifier.ToString()))
            {
                return false;
            }
            Classes.Add(cl.Identifier.ToString(),cl);
            if (asscs)
            {
                AssemblyCs.Add(cl.Identifier.ToString(),cl);
            }

            return true;
        }
    }
}