using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class ClassMatchChain : MatchBase<ClassDeclarationSyntax>
    {
        private readonly List<FieldMatch> _fieldMatches = new();
        private readonly List<MethodMatch> _methodMatches = new();

        public ClassMatchChain()
        {
            AddPred("has fields",delegate(ClassDeclarationSyntax cls)
            {
                var fl = new List<FieldDeclarationSyntax?>(cls.ChildNodes().OfType<FieldDeclarationSyntax>());
                foreach (var fieldMatch in _fieldMatches)
                {
                    var matched = false;
                    for (var i = 0; i < fl.Count; i++)
                    {
                        
                        var f = fl[i];
                        if(f == null) continue;
                        if(Program.Debug)Console.WriteLine("Trying field {" + f + "}");
                        if (!fieldMatch.Matches(f, false))
                        {
                            if(Program.Debug)Console.WriteLine("Wrong field");
                            continue;
                        }
                        if(Program.Debug)Console.WriteLine("Field good");
                        matched = true;
                        fl[i] = null;
                        break;
                    }

                    if (!matched) return false;
                }

                return true;
            });
            
            AddPred("has methods",delegate(ClassDeclarationSyntax cls)
            {
                var ml = new List<MethodDeclarationSyntax?>(cls.ChildNodes().OfType<MethodDeclarationSyntax>());
                foreach (var methodMatch in _methodMatches)
                {
                    var matched = false;
                    for (var i = 0; i < ml.Count; i++)
                    {
                        
                        var m = ml[i];
                        if(m == null) continue;
                        if(Program.Debug)Console.WriteLine("Trying Method {" + m + "}");
                        if (!methodMatch.Matches(m, false))
                        {
                            if(Program.Debug)Console.WriteLine("Wrong Method");
                            continue;
                        }
                        if(Program.Debug)Console.WriteLine("Method good");

                        matched = true;
                        ml[i] = null;
                        break;
                    }

                    if (!matched) return false;
                }

                return true;
            });
        }

        public ClassMatchChain OfName(string name)
        {
            AddPred($"name : {name}",c => c.Identifier.ToString() == name);
            return this;
        }

        public ClassMatchChain OfSuperClass(ClassMatchChain superClass)
        {
            AddPred("subtype matches",delegate(ClassDeclarationSyntax c)
            {
                return c.BaseList?.Types.Any(
                    bc => superClass.Matches(Registry.GetClass(bc.ToString()))) ?? false;
            });
            return this;
        }
        
        public ClassMatchChain WithTag(string tag)
        {
            return SetTag(tag) as ClassMatchChain ?? throw new InvalidOperationException();
        }

        public FieldMatch WithField()
        {
            FieldMatch f = new(this);
            _fieldMatches.Add(f);
            return f;
        }
        
        public MethodMatch WithMethod()
        {
            MethodMatch m = new(this);
            _methodMatches.Add(m);
            return m;
        }
    }
}