using System;
using System.Collections.Generic;
using System.Linq;
using AUMDeobfuscator.Matchers;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Output;
using CliFx;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Search
{
    public static class Searching
    {
        public static List<ClassDeclarationSyntax> SearchForClass(ClassMatch classMatch)
        {
            if (Program.Debug)
            {
                Program.WriteLine(ConsoleColor.Yellow,$"Trying to find {{{UsingDirective.BuildFullTypeTag(classMatch)}}}");
                Program.IndentLevel++;
            }


            List<ClassDeclarationSyntax> ls = Registry.GetMatchedType(classMatch);

            if (!Program.SkipOne)
                ls = Registry.AssemblyCs.Values.Where(c => c is ClassDeclarationSyntax cl && classMatch.Matches(cl))
                    .Cast<ClassDeclarationSyntax>().ToList();

            List<ClassDeclarationSyntax> toRemove = new();
            
            foreach (var classDeclarationSyntax in ls)
            {
                if (Registry.Fullmatches.Contains(classDeclarationSyntax))
                {
                    toRemove.Add(classDeclarationSyntax);
                }
                else
                {
                    Registry.AddMatchedType(classMatch, classDeclarationSyntax);
                }
            }
            
            foreach (var torm in toRemove)
            {
                ls.Remove(torm);
            }

            if (ls.Count == 1)
            {
                Registry.Fullmatches.Add(ls[0]);
            }

            

            if (Program.Debug)
            {
                Program.IndentLevel--;
            }

            return ls;
        }

        public static List<EnumDeclarationSyntax> SearchForEnum(EnumMatch enumMatch)
        {
            if (Program.Debug)
            {
                Program.WriteLine(ConsoleColor.Yellow,$"Trying to find {{{UsingDirective.BuildFullTypeTag(enumMatch)}}}");
                Program.IndentLevel++;
            }

            List<EnumDeclarationSyntax> ls = Registry.GetMatchedType(enumMatch);

            if (!Program.SkipOne)
                ls = Registry.AssemblyCs.Values.Where(c => c is EnumDeclarationSyntax e && enumMatch.Matches(e))
                    .Cast<EnumDeclarationSyntax>().ToList();

            foreach (var enumDeclarationSyntax in ls)
            {
                Registry.AddMatchedType(enumMatch, enumDeclarationSyntax);
            }

            if (Program.Debug)
            {
                Program.IndentLevel--;
            }

            return ls;
        }
        
        public static List<FieldDeclarationSyntax> SearchForField(this ClassDeclarationSyntax type,FieldMatch fieldMatch)
        {
            if (Program.Debug)
            {
                Program.WriteLine(ConsoleColor.Yellow,$"Trying to find {{{UsingDirective.BuildFullMemberTag(fieldMatch)}}}");
                Program.IndentLevel++;
            }

            List<FieldDeclarationSyntax> s = Registry.GetMatchedMember(fieldMatch);
            if (!Program.SkipOne)
                s = type.Members.OfType<FieldDeclarationSyntax>().Where(fieldMatch.Matches)
                    .ToList();


            if (Program.Debug)
            {
                Program.IndentLevel--;
            }

            return s;
        }

        public static List<MethodDeclarationSyntax> SearchForMethod(this ClassDeclarationSyntax classDeclaration,
            MethodMatch methodMatch)
        {
            if (Program.Debug)
            {
                Program.WriteLine(ConsoleColor.Yellow,$"Trying to find {{{UsingDirective.BuildFullMemberTag(methodMatch)}}}");
                Program.IndentLevel++;
            }

            List<MethodDeclarationSyntax> s = Registry.GetMatchedMember(methodMatch);

            if(!Program.SkipOne)
            {
                Program.WriteLine(ConsoleColor.Red, "Skipping for speed");
                s = classDeclaration.Members.OfType<MethodDeclarationSyntax>().Where(methodMatch.Matches)
                    .ToList();
            }

            if (Program.Debug)
            {
                Program.IndentLevel--;
            }

            return s;
        }


        public static List<EnumMemberDeclarationSyntax> SearchForEnumValue(this EnumDeclarationSyntax enumDeclaration,
            EnumValueMatch valueMatch)
        {
            if (Program.Debug)
            {
                Program.WriteLine(ConsoleColor.Yellow,$"Trying to find {{{UsingDirective.BuildFullMemberTag(valueMatch)}}}");
                Program.IndentLevel++;
            }

            List<EnumMemberDeclarationSyntax> s = Registry.GetMatchedMember(valueMatch);
            if (!Program.SkipOne)
                s = enumDeclaration.Members.Where(m => valueMatch.Matches(m))
                    .ToList();

            if (Program.Debug)
            {
                Program.IndentLevel--;
            }

            return s;
        }

        public static void DisplayMatches<T>(TypeMatchBase<T> name, IEnumerable<T> cl)
            where T : BaseTypeDeclarationSyntax
        {
            DisplayMatchesString(name, UsingDirective.BuildFullTypeTag(name),
                cl.Select(UsingDirective.BuildFullTypeName).ToList());
        }

        public static void DisplayMatches<T, TU>(MemberMatchBase<T, TU> name, IEnumerable<MemberDeclarationSyntax> cl)
            where T : MemberDeclarationSyntax where TU : BaseTypeDeclarationSyntax
        {
            DisplayMatchesString(name, UsingDirective.BuildFullMemberTag(name),
                cl.Select(UsingDirective.BuildFullMemberName).ToList());
        }

        private static void DisplayMatchesString<T>(MatchBase<T> matcher, string name, IReadOnlyList<string> ids)
            where T : CSharpSyntaxNode
        {
            var kind = matcher switch
            {
                MethodMatch => "Method",
                FieldMatch => "Field",

                ClassMatch => "Class",
                EnumMatch => "Enum",

                EnumValueMatch => "Enum Value",
                _ => throw new ArgumentOutOfRangeException(nameof(matcher))
            };

            switch (ids.Count)
            {
                case 0:
                    Program.WriteLine(ConsoleColor.Red,$"No Match for [{kind}] {name} found");
                    break;
                case 1:
                    Program.WriteLine(ConsoleColor.Green,$"[{kind}] {name} is {ids[0]}");
                    break;
                default:
                {
                    Program.WriteLine(ConsoleColor.DarkGreen,$"[{kind}] {name} might be :");
                    foreach (var aSyntax in ids)
                    {
                        Program.WriteLine(ConsoleColor.DarkGreen,$"     - {aSyntax}");
                    }

                    break;
                }
            }
        }
    }
}