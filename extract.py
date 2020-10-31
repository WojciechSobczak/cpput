import os 
import re 
import shutil
import argparse
import distutils.dir_util as dir_util
from typing import List
from typing import Set

def extractDependencies(filePath: str) -> Set[str]:
    lines = [];
    output = set({});
    with open(filePath) as file:
        lines = file.readlines();
    for line in lines:
        dependency = re.search("#include\s*\"([\.\w\/]+)\.\w+\"", line);
        if dependency:
            output.add(dependency.group(1));
    return output;

def parseList(csListStr: str) -> List[str]:
    strList = csListStr.split(",");
    map(lambda fileName: fileName.strip(), strList);
    return strList;

def includeScenario(files: List[str]):
    dir_util.mkpath("./extract");
    for file in files:
        hppFile = "./src/{}.hpp".format(file);
        cppFile = "./src/{}.cpp".format(file);
        dependencies = extractDependencies(hppFile);
        if (os.path.exists(cppFile)):
            dependencies.update(extractDependencies(hppFile));
        for dependency in dependencies:
            shutil.copyfile("./src/{}.hpp".format(dependency), "./extract/{}.hpp".format(dependency))
            cppDependency = "./src/{}.cpp".format(dependency);
            if (os.path.exists(cppDependency)):
                shutil.copyfile(cppDependency, "./extract/{}.cpp".format(dependency))
        
        shutil.copyfile(hppFile, "./extract/{}.hpp".format(file))
        if (os.path.exists(cppFile)):
            shutil.copyfile(cppFile, "./extract/{}.cpp".format(file))

def excludeScenario(files: List[str]):
    print(files)


try:
    parser = argparse.ArgumentParser(description="Minimal cpput extract script.")
    parser.add_argument("--include", type=str, help="Comma separated list of included files (without extensions)", default="");
    parser.add_argument("--exclude", type=str, help="Comma separated list of excluded files (without extensions)", default="");

    args = parser.parse_args()

    if (args.include != "" and args.exclude != ""):
        raise Exception("--include and --exclude arguments are mutually exclusive!");
    
    if (args.include != ""):
        includeFiles = parseList(args.include);
        includeScenario(includeFiles);
    elif (args.include != ""):
        excludeFiles = parseList(args.exclude);
        excludeScenario(excludeFiles);

    print("cpput extract ready!")
except Exception as e:
    print(e);
    pass