using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers.Bases
{
    public class MemberMatchBase<T,TU> : MatchBase<T> where T : MemberDeclarationSyntax where TU : BaseTypeDeclarationSyntax
    {

        public TypeMatchBase<TU> ParentType
        {
            get => (Parent as TypeMatchBase<TU>)!;
            set => Parent = value;
        }
        public TypeMatchBase<TU> And()
        {
            return (Parent as TypeMatchBase<TU>)!;
        }

        protected MemberMatchBase(TypeMatchBase<TU> parent) : base(parent)
        {
            
        }
    }
}