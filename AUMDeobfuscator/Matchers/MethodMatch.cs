using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Search;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class MethodMatch : ClassMemberMatchBase<MethodDeclarationSyntax>
    {

        private List<ParameterMatch> _parameterMatches = new List<ParameterMatch>();
        
        
        
        public MethodMatch OfName(string name)
        {
            AddPred($"name : {name}",m => m.Identifier.ToString() == name);
            return this;
        }
        
        public MethodMatch WithNamedReturnType(string type)
        {
            AddPred($"named return type : {type}",m => m.ReturnType.ToString() == type);
            return this;
        }
        
        public MethodMatch WithReturnType<T>(TypeMatchBase<T> typeMatchBase) where T : BaseTypeDeclarationSyntax
        {
            AddPred("return type matches", p => typeMatchBase.Matches(Registry.GetClass<T>(p.ReturnType.ToString())));
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

        public MethodMatch WithNumberOfParameters(int nb)
        {
            AddPred($"Has == {nb} params",m => m.ParameterList.Parameters.Count == nb);
            return this;
        }
        
        public MethodMatch WithAtLeastParameters(int nb)
        {
            AddPred($"Has >= {nb} params",m => m.ParameterList.Parameters.Count >= nb);
            return this;
        }
        
        public MethodMatch WithNoMoreThanParameters(int nb)
        {
            AddPred($"Has <= {nb} params",m => m.ParameterList.Parameters.Count <= nb);
            return this;
        }

        public ParameterMatch WithParameter()
        {
            var p = new ParameterMatch(this);
            _parameterMatches.Add(p);
            return p;
        }
        
        public MethodMatch WithTag(string tag)
        {
            return SetTag(tag) as MethodMatch ?? throw new InvalidOperationException();
        }




        public MethodMatch(ClassMatch parent) : base(parent)
        {
           AddPred("has parameters",delegate(MethodDeclarationSyntax method)
            {
                var parameters = new List<ParameterSyntax?>(method.ParameterList.Parameters);
                foreach (var paramMatch in _parameterMatches)
                {
                    if (Program.Debug)
                    {
                        Program.WriteLine($"Trying to find [Parameter] {{{paramMatch.Tag}}}");
                        Program.IndentLevel++;
                    }
                    var matched = false;
                    for (var i = 0; i < parameters.Count; i++)
                    {
                        
                        var m = parameters[i];
                        if(m == null) continue;
                        if (Program.Debug)
                        {
                            Program.WriteLine("Trying Parameter {" + m + "}");
                            Program.IndentLevel++;
                        }
                        if (!paramMatch.Matches(m))
                        {
                            if (Program.Debug)
                            {
                                Program.WriteLine(ConsoleColor.Gray,"Wrong Method");
                                Program.IndentLevel--;
                            }
                            continue;
                        }

                        if (Program.Debug)
                        {
                            Program.WriteLine(ConsoleColor.Green,"Method good");
                            Program.IndentLevel--;
                        }

                        matched = true;
                        parameters[i] = null;
                        break;
                    }

                    if (Program.Debug)
                    {
                       
                        Program.IndentLevel--;
                    }
                    if (!matched) return false;
                }

                return true;
            });
        }
    }
}