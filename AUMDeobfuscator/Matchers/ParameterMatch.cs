using System;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Search;
using Microsoft.CodeAnalysis.CSharp.Syntax;
using ParameterSyntax = Microsoft.CodeAnalysis.CSharp.Syntax.ParameterSyntax;

namespace AUMDeobfuscator.Matchers
{
    public class ParameterMatch : MatchBase<ParameterSyntax>
    {
        public ParameterMatch(MethodMatch methodMatch)
        {
            Parent = methodMatch;
        }

        public MethodMatch And()
        {
            return (Parent as MethodMatch)!;
        }

        public ParameterMatch WithType<T>(TypeMatchBase<T> typeMatchBase) where T : BaseTypeDeclarationSyntax
        {
            AddPred("type matches", p => typeMatchBase.Matches(Registry.GetClass<T>(p.Type?.ToString())));
            return this;
        }
        
        public ParameterMatch WithTag(string tag)
        {
            return SetTag(tag) as ParameterMatch ?? throw new InvalidOperationException();
        }
        
        public ParameterMatch WithNamedType(string type)
        {
            AddPred("named type matches", p => p.Type?.ToString() == type);
            return this;
        }

        public ParameterMatch WithName(string name)
        {
            AddPred("has name",p => p.Identifier.ToString() == name);
            return this;
        }

        public ParameterMatch WithDefaultValue(string defaultValue)
        {
            AddPred("has default value",p => p.Default?.Value.ToString() == defaultValue);
            return this;
        }
        
    }
}