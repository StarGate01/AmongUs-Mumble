using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Search
{
    public static class Parser
    {
        private static IEnumerable<BaseTypeDeclarationSyntax> ParseFile(string path)
        {
            var content = File.ReadAllText(path);
            
            var s = CSharpSyntaxTree.ParseText(content).GetRoot();
            var classDeclarationSyntaxes = s.ChildNodes().OfType<BaseTypeDeclarationSyntax>();
            var declarationSyntaxes = classDeclarationSyntaxes.SelectMany(DoParseFile).ToList();
            return declarationSyntaxes;
        }

        public static List<BaseTypeDeclarationSyntax> DoParseFile(BaseTypeDeclarationSyntax stx)
        {
            List<BaseTypeDeclarationSyntax> declarations = new(){stx};
            foreach (var baseTypeDeclarationSyntax in stx.ChildNodes().OfType<BaseTypeDeclarationSyntax>())
            {
                declarations.AddRange(DoParseFile(baseTypeDeclarationSyntax));
            }
            return declarations;
        }

        public static void AddAllClassesIn(string dir, string searchFolder, string? basedir = null)
        {
            Program.SetColor(ConsoleColor.Yellow);
            basedir ??= dir;   
            var acs = Path.GetFileName(dir) == searchFolder;
            var ind = Path.GetRelativePath(basedir, dir).Split(Path.PathSeparator).Length;
            if (Program.Debug && !acs)
            {

                Program.IndentLevel += ind;
            }
            if(Program.Debug || acs)Program.WriteLine($"Doing classes in {dir}");
            // files
            foreach (var file in Directory.EnumerateFiles(dir))
            {
                if (Path.GetFileName(file) == "AssemblyInfo.cs")
                {
                    if(Program.Debug)Program.WriteLine("Skipping AssemblyInfo.cs");
                    continue;
                }
                
                if (Path.GetFileName(file) == "SR.cs")
                {
                    if(Program.Debug)Program.WriteLine("Skipping SR.cs");
                    continue;
                }

                //Program.WriteLine($"Parsing {file}...");
                foreach (var cls in Parser.ParseFile(file))
                {
                    if (!Registry.Add(cls, acs))
                    {
                        Program.WriteLine($"[WARNING] Duplicate class, {cls.Identifier.ToString()}");
                    }
                }
            }
            //folders
            foreach (var sub in Directory.EnumerateDirectories(dir))
            {
                AddAllClassesIn(sub,searchFolder,basedir);
            }
            
            if (Program.Debug && !acs)
            {

                Program.IndentLevel -= ind;
            }
            Program.SetColor(ConsoleColor.White);
        }
    }
}