using System.Linq;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class MethodMatch : MemberMatchBase<MethodDeclarationSyntax>
    {
        public MethodMatch OfName(string name)
        {
            AddPred($"name : {name}",m => m.Identifier.ToString() == name);
            return this;
        }
        
        public MethodMatch OfReturnType(string type)
        {
            AddPred($"return type : {type}",m => m.ReturnType.ToString() == type);
            return this;
        }
        
        public MethodMatch OfNameContains(string contains)
        {
            AddPred($"name contains : {contains}",m => m.Identifier.ToString().Contains(contains));
            return this;
        }
        
        public MethodMatch WithModifier(string mod)
        {
            AddPred($"has modifier : {mod}",m => m.Modifiers.Any(mo => mo.ToString() == mod));
            return this;
        }
        
        public MethodMatch WithTag(string tag)
        {
            return SetTag(tag) as MethodMatch;
        }


        public MethodMatch(ClassMatchChain thisClass) : base(thisClass)
        {
        }
    }
}