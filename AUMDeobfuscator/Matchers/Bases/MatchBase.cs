using System;
using System.Collections.Generic;
using AUMDeobfuscator.Output;
using Microsoft.CodeAnalysis.CSharp;

namespace AUMDeobfuscator.Matchers.Bases
{
    public abstract class MatchBase<T> where T : CSharpSyntaxNode
    {
        
        protected object? Parent { get; set; }

        protected MatchBase(object? parent)
        {
            Tag = GetType().ToString();
            Parent = parent;
        }

        
        public string Tag { get; private set; }
        
        protected MatchBase(): this(null)
        {
            
        }

        protected MatchBase<T> SetTag(string tag)
        {
            Tag = tag;
            return this;
        }

        private readonly List<String> _predStrings = new();
        private List<Predicate<T>> Predicates { get; } = new();

        protected void AddPred(string s, Predicate<T> pred)
        {
            Predicates.Add(pred);
            _predStrings.Add(s);
        }

        public bool Matches(T? f)
        {
            var verbose = Program.Debug;

            var stringtag = UsingDirective.FindFullTag(this);
            var stringname = f == null ? "" : UsingDirective.FindFullName(f);
            
            for (var i = 0; i < Predicates.Count; i++)
            {
                if (verbose)
                {
                    Program.WriteLine("Checking predicate {" + _predStrings[i] + "} for {" + stringname + "}" );
                    Program.IndentLevel++;
                }
                var p = Predicates[i];
                if (f != null && !p.Invoke(f))
                {
                    if (verbose)
                    {
                        Program.WriteLine(ConsoleColor.Red,"Failed, stopping chain");
                        Program.IndentLevel--;
                    }
                    return false;
                }

                if (f == null)
                {
                    Program.WriteLine("[WARNING] Null value");
                }

                if (verbose)
                {
                    Program.WriteLine(ConsoleColor.Green,"Good, checking next");
                    Program.IndentLevel--;
                }
            }

            return true;
        }
    }
}