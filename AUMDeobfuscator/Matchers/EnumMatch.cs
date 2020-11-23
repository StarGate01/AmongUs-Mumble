using System;
using System.Collections.Generic;
using System.Linq;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Output;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Matchers
{
    public class EnumMatch : TypeMatchBase<EnumDeclarationSyntax>
    {

        private List<EnumValueMatch> EnumValueMatches = new();

        public EnumMatch()
        {
            AddPred("has values",delegate(EnumDeclarationSyntax cls)
            {
                var ml = new List<EnumMemberDeclarationSyntax?>(cls.Members);
                foreach (var memberMatch in EnumValueMatches)
                {
                    if (Program.Debug)
                    {
                        Program.WriteLine(ConsoleColor.Yellow,$"Trying to find [Enum Member] {{{UsingDirective.BuildFullMemberTag(memberMatch)}}}");
                        Program.IndentLevel++;
                    }
                    var matched = false;
                    for (var i = 0; i < ml.Count; i++)
                    {
                        
                        var m = ml[i];
                        if(m == null) continue;
                        if (Program.Debug)
                        {
                            Program.WriteLine("Trying Member {" + UsingDirective.BuildFullMemberName(m) + "}");
                            Program.IndentLevel++;
                        }
                        if (!memberMatch.Matches(m))
                        {
                            if (Program.Debug)
                            {
                                Program.WriteLine(ConsoleColor.Gray,"Wrong Member");
                                Program.IndentLevel--;
                            }
                            continue;
                        }

                        if (Program.Debug)
                        {
                            Program.WriteLine(ConsoleColor.Green,"Member good");
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
        
        public EnumValueMatch WithMember()
        {
            var enumValueMatch = new EnumValueMatch(this);
            EnumValueMatches.Add(enumValueMatch);
            return enumValueMatch;
        }
        
        
    }
}