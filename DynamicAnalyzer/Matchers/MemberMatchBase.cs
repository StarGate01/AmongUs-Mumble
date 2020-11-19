using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class MemberMatchBase<T> : MatchBase<T> where T : MemberDeclarationSyntax
    {
        private ClassMatchChain thisClass;

        protected MemberMatchBase(ClassMatchChain thisClass)
        {
            this.thisClass = thisClass;
        }

        public ClassMatchChain And()
        {
            return thisClass;
        }
    }
}