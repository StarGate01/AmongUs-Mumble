using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator
{
    internal static class Searching
    {
        public static List<ClassDeclarationSyntax> SearchFor(Predicate<ClassDeclarationSyntax> predicate)
        {
            return Registry.AssemblyCs.Values.Where(predicate.Invoke).ToList();
        }

        public static void DisplayMatches(string name, List<ClassDeclarationSyntax> cl)
        {
            switch (cl.Count)
            {
                case 0:
                    Console.WriteLine($"No Match for {name} found");
                    break;
                case 1:
                    Console.WriteLine($"{name} is {cl[0].Identifier}");
                    break;
                default:
                {
                    foreach (var aSyntax in cl)
                    {
                        Console.WriteLine($"{name} might be {aSyntax.Identifier}");
                    }

                    break;
                }
            }
        }
    }
}