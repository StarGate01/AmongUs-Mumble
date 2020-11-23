using System.Collections.Generic;
using System.Text;

namespace AUMDeobfuscator.Output
{
    public class OutputTemplate
    {
        // ReSharper disable once InconsistentNaming
        private string version_text;

        public OutputTemplate(string versionText)
        {
            version_text = versionText;
        }

        public readonly List<UsingDirective> UsingDirectives = new();

        public readonly List<EnumValueDirective> EnumValueDirectives = new();

        public readonly List<DefineDirective> DefineDirectives = new();

        public override string ToString()
        {
            
            StringBuilder builder = new();

            builder.AppendLine(DefineDirective.Define(nameof(version_text),$"\"{version_text}\""));
            
            foreach (var usingDirective in UsingDirectives)
            {
                if (usingDirective.Separator)
                {
                  

                    builder.AppendLine("// -------------------");
                }

                if (usingDirective.Multiple)
                {
                    builder.Append('!');
                }
                builder.AppendLine(usingDirective.ToString());

            }


            foreach (var enumValueDirective in EnumValueDirectives)
            {
                if (enumValueDirective.Separator)
                {
                  

                    builder.AppendLine("// -------------------");
                }

                if (enumValueDirective.Multiple)
                {
                    builder.Append('!');
                }
                builder.AppendLine(enumValueDirective.ToString());


            }

            
            foreach (var defineDirectives in DefineDirectives)
            {
                if (defineDirectives.Separator)
                {
                  

                    builder.AppendLine("// -------------------");
                }

                if (defineDirectives.Multiple)
                {
                    builder.Append('!');
                }
                
                builder.AppendLine(defineDirectives.ToString());

            }

            return builder.ToString();
        }
        
    }
}