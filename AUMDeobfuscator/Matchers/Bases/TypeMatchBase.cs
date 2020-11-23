using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers.Bases
{
    public class TypeMatchBase<T> : MatchBase<T> where T : BaseTypeDeclarationSyntax
    {
        

        public ClassMatch? ParentClass => Parent as ClassMatch;

        
    }
}