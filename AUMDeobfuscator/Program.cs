using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;
using AUMDeobfuscator.Search;
using CliFx;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator
{
    internal static class Program
    {
        public static int IndentLevel
        {
            get => _indentLevel;
            set
            {
                if (value > _indentLevel)
                {
                    //System.Console.WriteLine("Incremented Indent");
                }
                else if (value < _indentLevel)
                {
                    //System.Console.WriteLine("Decremented Indent");
                }

                if (value < 0) throw new InvalidDataException();
                _indentLevel = value;
            }
        }

        public static bool SkipOne { get; set; }

        public static int IndentMaxLevel = 0;
        public static IConsole? Console;
        
        public static bool Debug = false;
        private static int _indentLevel;


        public static async Task<int> Main() => await new CliApplicationBuilder()
            .AddCommandsFromThisAssembly()
            .Build()
            .RunAsync();


        public static void SetColor(ConsoleColor color)
        {
            if (Console != null) Console.ForegroundColor = color;
        }
        
        public static ConsoleColor GetColor()
        {
            return Console?.ForegroundColor ?? ConsoleColor.White;
        }

        public static void WriteLine(ConsoleColor color, string text)
        {
            Console?.WithForegroundColor(color,() => WriteLine(text));
        }
        
        public static void WriteLine(string text)
        {
            
            if(IndentLevel > IndentMaxLevel )
            {
                if (text.StartsWith("[WARNING]") || text.StartsWith("[ERROR]"))
                {
                    var old = IndentLevel;
                    IndentLevel = IndentMaxLevel + 1;
                    SetColor(text.StartsWith("[WARNING]") ? ConsoleColor.Yellow : ConsoleColor.Red);
                    DoWriteLine();
                    SetColor(ConsoleColor.White);
                    IndentLevel = old;

                    return;
                }
                return;
            }
            DoWriteLine();

            void DoWriteLine()
            {
                for (var i = 0; i < IndentLevel; i++)
                {
                    Console?.Output.Write("      ");
                }

                Console?.Output.WriteLine(text);
            }
        }
        
    }
}