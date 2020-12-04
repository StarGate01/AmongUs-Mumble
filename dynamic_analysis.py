import os, pathlib, sys, re


basepath = os.path.join(pathlib.Path(__file__).parent.absolute(), "AUMInjector")
functions_file = os.path.join(basepath, "appdata", "il2cpp-functions.h")
output_file = os.path.join(basepath, "deobfuscate", "dynamic_analysis.h")
if(len(sys.argv) < 2):
    print("Specify search token as first CLI argument, excluding tokens as following arguments")
    exit(1)
needle = sys.argv[1]
exclude = sys.argv[2:]

print("Tool to generate hooking code for dynamic analysis")
print("Using definition file: " + functions_file)
print("Using output file: " + output_file)
print("Matching on: " + needle + "\n")

hooks = []
with open(output_file, "w") as ofp:
    ofp.write("#include \"il2cpp-appdata.h\"\n#include <detours.h>\n#include <cstdio>\n\nusing namespace app;\n\n")
    with open(functions_file) as fp:
        line = fp.readline()
        cnt = 1
        while line:
            if needle in line:
                is_excluded = False
                for ex in exclude: 
                    if ex in line:
                        is_excluded = True
                        break
                if not is_excluded:
                    m = re.search(r',\W*([^,]*),\W*([^,]*)\W*\((.*)\)\);.*', line)
                    returntype = str(m.group(1))
                    name = str(m.group(2))
                    params = str(m.group(3))
                    print(name)
                    hooks.append(name)
                    signature = returntype + " " + name + "_Hook(" + params + ")"
                    paramnames = list(map(lambda x: x.split(" ")[-1], params.split(",")))
                    trampoline_call = name + "(" +  ", ".join(paramnames) + ");"
                    if(returntype != "void"): trampoline_call = "return " + trampoline_call
                    ofp.write(signature + " { printf(\"" + name + "\\n\"); " + str(trampoline_call) + " }\n")
                    # ofp.write(signature + " { " + str(trampoline_call)  + " std::string t((const char*)(" + paramnames[1] + 
                    #     "->fields.m_ChunkChars->vector), " + paramnames[1] + "->fields.m_ChunkLength); std::cout << \"" + name + ": \" << t << \" (\" << (" + 
                    #     paramnames[1] + "->fields.m_ChunkLength) << \")\" << std::endl; }\n")
            line = fp.readline()
            cnt += 1
    ofp.write("\nvoid dynamic_analysis_attach() {\n")
    for hook in hooks: ofp.write("\tDetourAttach(&(PVOID&)" + hook + ", " + hook + "_Hook);\n")
    ofp.write("}\n")
