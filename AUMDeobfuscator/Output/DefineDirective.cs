using System;
using System.Linq;
using AUMDeobfuscator.Matchers;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Output
{
    public class DefineDirective
    {
        private MethodMatch _name;
        private MethodDeclarationSyntax _realname;
        
        public bool Multiple = false;
        public bool Separator = false;

        public DefineDirective(MethodMatch name, MethodDeclarationSyntax realname)
        {
            _name = name;
            _realname = realname;
        }

        public static string Define(string name, string val)
        {
            return $"#define {name} {val}";
        }

        public override string ToString()
        {

            string mname = UsingDirective.BuildFullMemberTag(_name) + "_Trampoline";
            string classrealname = UsingDirective.BuildFullMemberName(_realname);
            return Define(mname, classrealname);
        }
    }
}