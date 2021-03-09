using System;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Search;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class FieldMatch : ClassMemberMatchBase<FieldDeclarationSyntax>
    {
        public FieldMatch(ClassMatch parent) : base(parent)
        {
        }

        public FieldMatch WithNamedType(string type)
        {
            AddPred($"named type : {type}",f => f.Declaration.Type.ToString() == type);
            return this;
        }
        
        public FieldMatch WithType<T>(TypeMatchBase<T> typeMatchBase) where T : BaseTypeDeclarationSyntax
        {
            AddPred("type matches", p => typeMatchBase.Matches(Registry.GetClass<T>(p.Declaration.Type.ToString())));
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

        public FieldMatch OfNameContains(string contains)
        {
            AddPred($"name contains : {contains}",f => f.Declaration.Variables[0].Identifier.ToString().Contains(contains));
            return this;
        }

    }
}