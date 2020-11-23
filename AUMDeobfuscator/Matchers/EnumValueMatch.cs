using AUMDeobfuscator.Matchers.Bases;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class EnumValueMatch : MemberMatchBase<EnumMemberDeclarationSyntax,EnumDeclarationSyntax>
    {
        
        public EnumMatch Enum
        {
            get => (Parent as EnumMatch)!;
            set => Parent = value;
        }

        public new EnumMatch And()
        {
            return Enum;
        }
        
        public EnumValueMatch(EnumMatch parent) : base(parent)
        {
            
        }

        public EnumValueMatch OfName(string name)
        {
            if (Tag == GetType().ToString()) Tag = name;
            AddPred($"has name {{{name}}}",m => m.Identifier.ToString() == name);
            return this;
        }
        
        public EnumValueMatch OfValue(string value)
        {
            AddPred($"has value {{{value}}}",m => m.EqualsValue?.Value.ToString() == value);
            return this;
        }

    }
}