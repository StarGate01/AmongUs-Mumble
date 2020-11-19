using System;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class FieldMatch : MemberMatchBase<FieldDeclarationSyntax>
    {
        public FieldMatch(ClassMatchChain thisClass) : base(thisClass)
        {
        }

        public FieldMatch OfType(string type)
        {
            AddPred($"type : {type}",f => f.Declaration.Type.ToString() == type);
            return this;
        }

        public FieldMatch WithTag(string tag)
        {
            return SetTag(tag) as FieldMatch ?? throw new InvalidOperationException();
        }

        public FieldMatch OfName(string name)
        {
            AddPred($"name : {name}",f => f.Declaration.Variables[0].Identifier.ToString() == name);
            return this;
        }
    }
}