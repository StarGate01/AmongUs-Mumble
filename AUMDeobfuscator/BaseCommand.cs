using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using AUMDeobfuscator.Matchers;
using AUMDeobfuscator.Matchers.Bases;
using AUMDeobfuscator.Output;
using AUMDeobfuscator.Search;
using CliFx;
using CliFx.Attributes;
using Microsoft.CodeAnalysis.CSharp.Syntax;
// ReSharper disable MemberCanBePrivate.Global

namespace AUMDeobfuscator.Commands
{
    [Command]
    public class BaseCommand : ICommand
    {
        
        [CommandOption("sources",'s',IsRequired = false, Description = "Name of folder with obfuscated sources, located inside the sources folder.")]
        public string SearchFolder { get; set; } = "Assembly-CSharp";
        
        [CommandOption("gameversion",'g',IsRequired = true, Description = "Version number of the outputted header file")]
        public string GameVersion { get; set; } = null!;
        
        [CommandOption("output",'o',IsRequired = false, Description = "Output header file path, default is <gameversion>.h")]
        public string OutputFileName { get; set; } = "";
        
        [CommandOption("speedup",'u',IsRequired = false, Description = "Tries to speed up the program by not looking in all files for other candidates to already matched values")]
        public bool SpeedUp { get; set; } = false;
        
        [CommandOption("verbose",'v',IsRequired = false, Description = "Verbose max level for matching")]
        public int VerboseLevel { get; set; } = 0;

        [CommandOption("dirverbose", 'd', IsRequired = false, Description = "Verbose max level for directory adding")]
        public int DirVerbose { get; set; } = 0;

        [CommandParameter(1, Name = "path", Description = "Path of folder containing sources folders.")]
        public string Path
        {
            get;
            set;
        } = null!;


        public ValueTask ExecuteAsync(IConsole console)
        {
            Program.Console = console;
            Program.IndentMaxLevel = DirVerbose;
            Program.Debug = true;
            Program.SkipOne = SpeedUp;

            if (OutputFileName == "")
            {
                OutputFileName = GameVersion.Replace('.','_') + ".h";
            }
            
            Program.WriteLine("Options : ");
            Program.WriteLine($"Game version : {GameVersion}");
            Program.WriteLine($"Sources directory : \"{Path}\"");
            Program.WriteLine($"Search directory : \"{SearchFolder}\"");
            Program.WriteLine($"Verbose level : {VerboseLevel}");
            Program.WriteLine($"Directory verbose level : {DirVerbose}");
            Program.WriteLine($"Stop on first match : {SpeedUp}");
            
            // parsing all classes
            Program.WriteLine("Registering all classes in all files");
            Parser.AddAllClassesIn(Path,SearchFolder);
            Program.IndentMaxLevel = VerboseLevel;

            OutputTemplate template = new(GameVersion);
           
                
            Program.WriteLine(ConsoleColor.White,"------------Matches------------");
            
            SearchAll(template);

            Program.WriteLine(ConsoleColor.White,"------------Output------------");

            string output = template.ToString();
            
            Program.WriteLine(output);
            
            Program.WriteLine(ConsoleColor.White,"------------------------------");
            
            Program.WriteLine($"Writing output to {OutputFileName}");
            
            File.WriteAllText(OutputFileName,output);
            
            return default;
        }

        private static void SearchAll(OutputTemplate template)
        {
            var properties = typeof(MatcherDefinitions)
                .GetNestedTypes().SelectMany(nt => nt.GetFields(BindingFlags.Public | BindingFlags.Static)
                    .Select(s => s.GetValue(null)).OrderBy(v => v is EnumMatch or ClassMatch ? 0 : 1)).ToList();

            
            
            foreach (var value in properties)
            {
                //console.Output.WriteLine(value);
                bool multiple;
                bool separator;
                switch (value)
                {
                    case ClassMatch m:
                        List<ClassDeclarationSyntax> classes = Searching.SearchForClass(m);
                        Searching.DisplayMatches(m, classes);
                        multiple = classes.Count > 1;
                        separator = multiple;
                        foreach (var classDeclarationSyntax in classes)
                        {
                            template.UsingDirectives.Add(new UsingDirective(m, classDeclarationSyntax){Multiple = multiple, Separator = separator});
                            if(separator) separator = false;
                        }

                        break;

                    case MethodMatch m:
                        var classDeclarationSyntaxes = Registry.GetMatchedType(m.Class);
                        List<MethodDeclarationSyntax> s = classDeclarationSyntaxes.SelectMany(cls => cls.SearchForMethod(m))
                            .ToList();
                        Searching.DisplayMatches(m, s);
                        multiple = s.Count > 1;
                        separator = multiple;
                        foreach (var methodDeclarationSyntax in s)
                        {
                            template.DefineDirectives.Add(new DefineDirective(m, methodDeclarationSyntax){Multiple = multiple, Separator = separator});
                            if(separator) separator = false;
                        }

                        break;
                    
                    case FieldMatch fm:
                        var cds = Registry.GetMatchedType(fm.Class);
                        List<FieldDeclarationSyntax> fs = cds.SelectMany(cls => cls.SearchForField(fm))
                            .ToList();
                        Searching.DisplayMatches(fm, fs);
                        multiple = fs.Count > 1;
                        separator = multiple;
                        foreach (var fieldDeclarationSyntax in fs)
                        {
                            template.UsingDirectives.Add(new UsingDirective(fm, fieldDeclarationSyntax){Multiple = multiple, Separator = separator});
                            if(separator) separator = false;
                        }

                        break;

                    case EnumMatch m:
                        var enums = Searching.SearchForEnum(m);
                        Searching.DisplayMatches(m, enums);
                        multiple = enums.Count > 1;
                        separator = multiple;
                        foreach (var enumDeclarationSyntax in enums)
                        {
                            template.UsingDirectives.Add(new UsingDirective(m, enumDeclarationSyntax){Multiple = multiple, Separator = separator});
                            if(separator) separator = false;
                        }

                        break;

                    case EnumValueMatch em:
                        var enumDeclarationSyntaxes = Registry.GetMatchedType(em.Enum);
                        List<EnumMemberDeclarationSyntax> enumMemberDeclarationSyntaxes =
                            enumDeclarationSyntaxes.SelectMany(eds => eds.SearchForEnumValue(em)).ToList();
                        Searching.DisplayMatches(em, enumMemberDeclarationSyntaxes);
                        multiple = enumMemberDeclarationSyntaxes.Count > 1;
                        separator = multiple;
                        foreach (var enumDeclarationSyntax in enumMemberDeclarationSyntaxes)
                        {
                            var enumValueDirective = new EnumValueDirective(em, enumDeclarationSyntax)
                            {
                                Multiple = multiple, Separator = separator
                            };
                            template.EnumValueDirectives.Add(enumValueDirective);
                            
                            if(separator) separator = false;
                        }

                        break;
                }
            }
        }
    }
    
}