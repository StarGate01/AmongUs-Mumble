using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator
{
    public static class Parser
    {
        private static IEnumerable<ClassDeclarationSyntax> ParseFile(string path)
        {
            var content = File.ReadAllText(path);
            
            var s = CSharpSyntaxTree.ParseText(content).GetRoot();
            var classDeclarationSyntaxes = s.ChildNodes().OfType<ClassDeclarationSyntax>();
            var declarationSyntaxes = classDeclarationSyntaxes.ToList();
            return declarationSyntaxes;
        }

        public static void AddAllClassesIn(string dir)
        {
            Console.WriteLine($"Doing classes in {dir}");
            var acs = Path.GetFileName(dir) == Program.SearchFolder;
            
            // files
            foreach (var file in Directory.EnumerateFiles(dir))
            {
                if (Path.GetFileName(file) == "AssemblyInfo.cs")
                {
                    Console.WriteLine("Skipping AssemblyInfo.cs");
                    continue;
                }

                //Console.WriteLine($"Parsing {file}...");
                foreach (var cls in Parser.ParseFile(file))
                {
                    if (!Registry.Add(cls, acs))
                    {
                        Console.WriteLine($"[WARNING] Duplicate class, {cls.Identifier.ToString()}");
                    }
                }
            }
            //folders
            foreach (var sub in Directory.EnumerateDirectories(dir))
            {
                AddAllClassesIn(sub);
            }
        }
    }
}