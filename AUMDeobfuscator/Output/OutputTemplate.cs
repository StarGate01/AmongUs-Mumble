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
                builder.AppendLine(usingDirective.ToString());
            }
            
            foreach (var enumValueDirective in EnumValueDirectives)
            {
                builder.AppendLine(enumValueDirective.ToString());
            }
            
            foreach (var defineDirectives in DefineDirectives)
            {
                builder.AppendLine(defineDirectives.ToString());
            }

            return builder.ToString();
        }
        
    }
}