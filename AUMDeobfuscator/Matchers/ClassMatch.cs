using System;
using System.Collections.Generic;
using System.Linq;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Output;
using AUMDeobfuscator.Search;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class ClassMatch : TypeMatchBase<ClassDeclarationSyntax>
    {
        private readonly List<FieldMatch> _fieldMatches = new();
        private readonly List<MethodMatch> _methodMatches = new();

        
        public ClassMatch? Class => Parent as ClassMatch;
        public ClassMatch()
        {
             AddPred("has fields",delegate(ClassDeclarationSyntax cls)
            {
                
                var fl = new List<FieldDeclarationSyntax?>(cls.Members.OfType<FieldDeclarationSyntax>());
                foreach (var fieldMatch in _fieldMatches)
                {
                    if (Program.Debug)
                    {
                        
                        Program.WriteLine(ConsoleColor.Yellow,$"Trying to find [Field] {{{UsingDirective.BuildFullMemberTag(fieldMatch)}}}");
                        Program.IndentLevel++;
                    }
                    var matched = false;
                    for (var i = 0; i < fl.Count; i++)
                    {
                        
                        var f = fl[i];
                        if(f == null) continue;
                        if (Program.Debug)
                        {
                            Program.WriteLine("Trying field {" + UsingDirective.BuildFullMemberName(f)+"}");
                            Program.IndentLevel++;
                        }
                        if (!fieldMatch.Matches(f))
                        {
                            if (Program.Debug)
                            {
                                Program.WriteLine(ConsoleColor.Gray,"Wrong field");
                                Program.IndentLevel--;
                            }
                            continue;
                        }

                        Registry.AddMatchedMember(fieldMatch, f);


                        if (Program.Debug)
                        {
                            Program.WriteLine(ConsoleColor.Green,"Field good");
                            Program.IndentLevel--;
                        }
                        matched = true;
                        fl[i] = null;
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
            
            AddPred("has methods",delegate(ClassDeclarationSyntax cls)
            {
                var ml = new List<MethodDeclarationSyntax?>(cls.ChildNodes().OfType<MethodDeclarationSyntax>());
                foreach (var methodMatch in _methodMatches)
                {
                    if (Program.Debug)
                    {
                        Program.WriteLine($"Trying to find [Method] {{{UsingDirective.BuildFullMemberTag(methodMatch)}}}");
                        Program.IndentLevel++;
                    }
                    var matched = false;
                    for (var i = 0; i < ml.Count; i++)
                    {
                        
                        var m = ml[i];
                        if(m == null) continue;
                        if (Program.Debug)
                        {
                            Program.WriteLine("Trying Method {" + UsingDirective.BuildFullMemberName(m) + "}");
                            Program.IndentLevel++;
                        }
                        if (!methodMatch.Matches(m))
                        {
                            if (Program.Debug)
                            {
                                Program.WriteLine(ConsoleColor.Gray,"Wrong Method");
                                Program.IndentLevel--;
                            }
                            continue;
                        }
                        
                        Registry.AddMatchedMember(methodMatch, m);

                        if (Program.Debug)
                        {
                            Program.WriteLine(ConsoleColor.Green,"Method good");
                            Program.IndentLevel--;
                        }

                        matched = true;
                        ml[i] = null;
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

        public ClassMatch OfSuperClass(ClassMatch superClass)
        {
            AddPred("subtype matches",delegate(ClassDeclarationSyntax c)
            {
                return c.BaseList?.Types.Any(
                    bc => superClass.Matches(Registry.GetClass(bc.ToString()) as ClassDeclarationSyntax)) ?? false;
            });
            return this;
        }
        
        public ClassMatch OfName(string name)
        {
            AddPred($"name : {name}",c => c.Identifier.ToString() == name);
            return this;
        }

        public ClassMatch WithTag(string tag)
        {
            return SetTag(tag) as ClassMatch ?? throw new InvalidOperationException();
        }

        public FieldMatch WithField()
        {
            FieldMatch f = new(this);
            _fieldMatches.Add(f);
            return f;
        }
        
        public FieldMatch WithField(FieldMatch f)
        {
            f.Class = this;
            _fieldMatches.Add(f);
            return f;
        }
        
        public MethodMatch WithMethod()
        {
            MethodMatch m = new(this);
            _methodMatches.Add(m);
            return m;
        }
        
        public MethodMatch WithMethod(MethodMatch m)
        {
            m.Class = this;
            _methodMatches.Add(m);
            return m;
        }
    }
}