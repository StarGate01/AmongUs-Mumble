using System.Text;
using AUMDeobfuscator.Matchers;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Output
{
    public class EnumValueDirective
    {
        private EnumValueMatch _enumMatch;
        private EnumMemberDeclarationSyntax _member;
        
        public bool Multiple = false;
        public bool Separator = false;

        public EnumValueDirective(EnumValueMatch enumMatch, EnumMemberDeclarationSyntax member)
        {
            _enumMatch = enumMatch;
            this._member = member;
        }

        public override string ToString()
        {
            StringBuilder builder = new();

            builder.Append(UsingDirective.BuildFullTypeTag(_enumMatch.Enum));
            builder.Append(' ');

            builder.Append(UsingDirective.BuildFullTypeTag(_enumMatch.Enum));
            builder.Append('_');
            builder.Append(_enumMatch.Tag);

            builder.Append(' ');

            builder.Append(UsingDirective.BuildFullTypeName((_member.Parent as EnumDeclarationSyntax)!));
            builder.Append('_');
            builder.Append(_member.Identifier);

            return builder.ToString();
        }
    }
}