using System;
using System.Collections.Generic;
using System.Linq;
using AUMDeobfuscator.Matchers;
using AUMDeobfuscator.Matchers.Bases;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Search
{
    public static class Registry
    {
        private static readonly Dictionary<string,BaseTypeDeclarationSyntax> ContextClasses = new();
        public static readonly Dictionary<string,BaseTypeDeclarationSyntax> AssemblyCs = new();

        public static readonly List<ClassDeclarationSyntax> Fullmatches = new();
        
        
        private static readonly Dictionary<ClassMatch, List<BaseTypeDeclarationSyntax>?> Classes = new();
        private static readonly Dictionary<EnumMatch,List<BaseTypeDeclarationSyntax>?> Enums = new();
        
        
        private static readonly Dictionary<FieldMatch, List<MemberDeclarationSyntax>?> Fields = new();
        private static readonly Dictionary<MethodMatch, List<MemberDeclarationSyntax>?> Methods = new();
        private static readonly Dictionary<EnumValueMatch, List<MemberDeclarationSyntax>?> EnumMember = new();
        

        
        public static T? GetClass<T>(string? name) where T : BaseTypeDeclarationSyntax
        {
            return name == null ? null : ContextClasses.GetValueOrDefault(name) as T;
        }

        public static void AddMatchedType<T>(TypeMatchBase<T> m, BaseTypeDeclarationSyntax bl) where T : BaseTypeDeclarationSyntax
        {
            switch (m)
            {
                case ClassMatch cm:
                    if (!Classes.ContainsKey(cm))
                    {
                        Classes[cm] = new List<BaseTypeDeclarationSyntax>();
                    }
                    Classes[cm].Add(bl as ClassDeclarationSyntax ?? throw new InvalidOperationException());
                    break;
                
                case EnumMatch em:
                    if (!Enums.ContainsKey(em))
                    {
                        Enums[em] = new List<BaseTypeDeclarationSyntax>();
                    }
                    Enums[em].Add(bl as EnumDeclarationSyntax ?? throw new InvalidOperationException());
                    break;
            }
        }
        
        public static void AddMatchedMember<T,TU>(MemberMatchBase<T,TU> m, MemberDeclarationSyntax bl) where T : MemberDeclarationSyntax where TU : BaseTypeDeclarationSyntax
        {
            switch (m)
            {
                case FieldMatch fm:
                    if (!Fields.ContainsKey(fm))
                    {
                        Fields[fm] = new List<MemberDeclarationSyntax>();
                    }
                    Fields[fm].Add(bl as FieldDeclarationSyntax ?? throw new InvalidOperationException());
                    break;
                
                case MethodMatch mm:
                    if (!Methods.ContainsKey(mm))
                    {
                        Methods[mm] = new List<MemberDeclarationSyntax>();
                    }
                    Methods[mm].Add(bl as MethodDeclarationSyntax ?? throw new InvalidOperationException());
                    break;
                
                case EnumValueMatch evm:
                    if (!EnumMember.ContainsKey(evm))
                    {
                        EnumMember[evm] = new List<MemberDeclarationSyntax>();
                    }
                    EnumMember[evm].Add(bl as EnumMemberDeclarationSyntax ?? throw new InvalidOperationException());
                    break;
            }
        }

        public static List<T> GetMatchedMember<T,TU>(MemberMatchBase<T,TU> m) where T : MemberDeclarationSyntax where TU : BaseTypeDeclarationSyntax
        {
            try
            {
                return (m switch
                {
                    FieldMatch cm => Fields[cm],
                    EnumValueMatch em => EnumMember[em],
                    MethodMatch em => Methods[em],
                    _ => throw new ArgumentOutOfRangeException(nameof(m))
                } ?? new List<MemberDeclarationSyntax>()).Cast<T>().ToList();
            }
            catch (KeyNotFoundException e)
            {
                return new List<T>();
            }
        }

        public static List<T> GetMatchedType<T>(TypeMatchBase<T> m) where T : BaseTypeDeclarationSyntax
        {
            try
            {
                return (m switch
                {
                    ClassMatch cm => Classes[cm],
                    EnumMatch em => Enums[em],
                    _ => throw new ArgumentOutOfRangeException(nameof(m))
                } ?? new List<BaseTypeDeclarationSyntax>()).Cast<T>().ToList();
            }
            catch (KeyNotFoundException e)
            {
                return new List<T>();
            }
        }
        

        public static bool Add(BaseTypeDeclarationSyntax cl, bool asscs = false)
        {
            if (ContextClasses.ContainsKey(cl.Identifier.ToString()) || AssemblyCs.ContainsKey(cl.Identifier.ToString()))
            {
                return false;
            }
            ContextClasses.Add(cl.Identifier.ToString(),cl);
            if (asscs)
            {
                AssemblyCs.Add(cl.Identifier.ToString(),cl);
            }

            return true;
        }
        
        
        
    }
}