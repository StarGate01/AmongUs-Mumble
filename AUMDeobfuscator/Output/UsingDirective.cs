using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using AUMDeobfuscator.Matchers;
using AUMDeobfuscator.Matchers.Bases;
using Microsoft.CodeAnalysis.CSharp;
using Microsoft.CodeAnalysis.CSharp.Syntax;

namespace AUMDeobfuscator.Output
{
    public class UsingDirective
    {
        private object _type; //i can't c# here, idk how to use generics properly for this use case
        private BaseTypeDeclarationSyntax  _value;

        public UsingDirective(object type, BaseTypeDeclarationSyntax value) 
        {
            _type = type;
            _value = value;
        }

        public override string ToString()
        {
            StringBuilder builder = new();

            builder.Append("using ");

            switch (_type)
            {
                case ClassMatch c:
                    builder.Append(BuildFullTypeTag(c));
                    break;
                case EnumMatch e:
                    builder.Append(BuildFullTypeTag(e));
                    break;
            }
            
            builder.Append(" = ");
            builder.Append(BuildFullTypeName(_value));
            builder.Append(';');

            return builder.ToString();
        }

        public static string BuildFullTypeTag<T>(TypeMatchBase<T> cls) where T : BaseTypeDeclarationSyntax
        {
            StringBuilder builder = new();
            List<string> parents = new() {cls.Tag};
            var cur = cls.ParentClass;
            while (cur!= null)
            {
                parents.Add(cur.Tag);
                cur = cur.ParentClass;
            }

            parents.Reverse();


            builder.Append(string.Join("_", parents));

            if (cls is EnumMatch)
            {
                builder.Append("__Enum");
            }

            return builder.ToString();
        }
        
        public static string BuildFullTypeName(BaseTypeDeclarationSyntax cls)
        {
            StringBuilder builder = new();
            List<string> parents = new() {cls.Identifier.ToString()};
            BaseTypeDeclarationSyntax cur = cls;
            while (cur.Parent is BaseTypeDeclarationSyntax stx)
            {
                
                cur = stx;
                parents.Add(cur.Identifier.ToString());
            }

            parents.Reverse();


            builder.Append(string.Join("_", parents));

            if (cls is EnumDeclarationSyntax)
            {
                builder.Append("__Enum");
            }

            return builder.ToString();
        }

        public static string BuildFullMemberName(MemberDeclarationSyntax m)
        {
            string typeFull =
                BuildFullTypeName(m.Parent as BaseTypeDeclarationSyntax ?? throw new InvalidOperationException());
            return typeFull + "_" + m switch
            {
                FieldDeclarationSyntax f => f.Declaration.Variables[0].Identifier.ToString(),
                MethodDeclarationSyntax md => md.Identifier.ToString(),
                EnumMemberDeclarationSyntax em => em.Identifier,
                _ => ""
            };
        }
        
        public static string BuildFullMemberTag<T,TU>(MemberMatchBase<T,TU> m) where T : MemberDeclarationSyntax where TU : BaseTypeDeclarationSyntax
        {
            string typeFull = BuildFullTypeTag(m.ParentType);
            return typeFull + "_" + m.Tag;
        }


        public static string FindFullTag<T>(MatchBase<T> matchBase) where T : CSharpSyntaxNode
        {
            return matchBase switch
            {
                ClassMatch or EnumMatch => BuildFullTypeTag((dynamic) matchBase),
                EnumValueMatch or FieldMatch or MethodMatch => BuildFullMemberTag((dynamic) matchBase),
                _ => throw new ArgumentOutOfRangeException(nameof(matchBase))
            };
        }

        public static string FindFullName<T>(T cSharpSyntaxNode) where T : CSharpSyntaxNode
        {
            return cSharpSyntaxNode switch
            {
                BaseTypeDeclarationSyntax b => BuildFullTypeName(b),
                MemberDeclarationSyntax m => BuildFullMemberName(m),
                _ => throw new ArgumentOutOfRangeException(nameof(cSharpSyntaxNode), cSharpSyntaxNode, null)
            };
        }
    }
}