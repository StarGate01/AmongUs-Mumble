using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers.Bases
{
    public class ClassMemberMatchBase<T> : MemberMatchBase<T,ClassDeclarationSyntax>  where T : MemberDeclarationSyntax
    {
        public ClassMatch Class
        {
            get => (Parent as ClassMatch)!;
            set => Parent = value;
        }
        public new ClassMatch And()
        {
            return Class;
        }
        
        public ClassMemberMatchBase(ClassMatch parent) : base(parent)
        {
            
        }
        
    }
}