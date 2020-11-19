using System;
using System.Collections.Generic;
using Microsoft.CodeAnalysis.CSharp;

namespace AUMDeobfuscator.Matchers
{
    public abstract class MatchBase<T> where T : CSharpSyntaxNode
    {
        

        public string Tag { get; private set; }
        
        protected MatchBase()
        {
            Tag = GetType().ToString();
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

        public bool Matches(T? f, bool verbose = Program.Debug)
        {
            
            for (var i = 0; i < Predicates.Count; i++)
            {
                if(verbose)Console.WriteLine("Checking predicate {" + _predStrings[i] + "} for {" + Tag + "}" );
                var p = Predicates[i];
                if (f != null && !p.Invoke(f))
                {
                    if(verbose)Console.WriteLine("Failed");
                    return false;
                }

                if (f == null)
                {
                    Console.WriteLine("[WARNING] Null value");
                }
                if(verbose)Console.WriteLine("Good");
            }

            return true;
        }
    }
}