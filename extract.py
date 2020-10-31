import os 
import re 
import shutil
import argparse
import collections
import distutils.dir_util as dir_util
from typing import List
from typing import Set

import linecache
import sys

HPP_SRC = "./src/{}.hpp";
CPP_SRC = "./src/{}.cpp";
EXTRACT_PATH = "./extract";
HPP_EXT = EXTRACT_PATH + "/{}.hpp";
CPP_EXT = EXTRACT_PATH + "/{}.cpp";

class OrderedSet:
    def __init__(self):
        self.orderedDict = collections.OrderedDict();

    def contains(self, val:str) -> bool:
        return self.orderedDict.get(val) != None;

    def add(self, val: str):
        if not self.contains(val):
            self.orderedDict[val] = None;

    def addAll(self, other):
        for otherKey in other.orderedDict.keys():
            self.add(otherKey);
            
    def values(self):
        return self.orderedDict.keys();


def parseList(csListStr: str) -> List[str]:
    strList = csListStr.split(",");
    map(lambda fileName: fileName.strip(), strList);
    return strList;

def extractDependencies(filePath: str) -> OrderedSet:
    output = OrderedSet();
    with open(filePath) as file:
        lines = file.readlines();
        for line in lines:
            dependency = re.search("#include\s*\"([\.\w\/]+)\.\w+\"", line);
            if dependency:
                output.add(dependency.group(1))
    return output;


def prepareCMakeLists():
    filesList = [];
    for root, subdirs, files in os.walk(EXTRACT_PATH):
        for file in files:
            path = os.path.join(root, file);
            path = "." + path[len(EXTRACT_PATH):].replace("\\", "/");
            filesList.append(path);
    with open(EXTRACT_PATH + "/CMakeLists.txt", "w") as file:
        file.write("cmake_minimum_required(VERSION 3.8)\n")
        file.write('project("cpput")\n')
        file.write("set(CMAKE_CXX_STANDARD 20)\n")
        file.write("add_library(${PROJECT_NAME} STATIC\n")
        for compileFile in filesList:
            file.write('    "{}"\n'.format(compileFile));
        file.write(")\n");

def prepareBigHeader(bigHeaderIncludes):
    with open(EXTRACT_PATH + "/cpput.hpp", "w") as file:
        file.write("#pragma once\n\n")
        for include in bigHeaderIncludes.values():
            file.writelines("#include <{}.hpp>\n".format(include));


def includeScenario(files: List[str]):
    dir_util.mkpath(EXTRACT_PATH);
    bigHeaderIncludes = OrderedSet();
    for file in files:
        hppFile = HPP_SRC.format(file);
        cppFile = CPP_SRC.format(file);
        dependencies = extractDependencies(hppFile);
        if (os.path.exists(cppFile)):
            dependencies.addAll(extractDependencies(cppFile));
        for dependency in dependencies.values():
            shutil.copyfile(HPP_SRC.format(dependency), HPP_EXT.format(dependency))
            cppDependency = CPP_SRC.format(dependency);
            if (os.path.exists(cppDependency)):
                shutil.copyfile(cppDependency, CPP_EXT.format(dependency))
        shutil.copyfile(hppFile, HPP_EXT.format(file))
        if (os.path.exists(cppFile)):
            shutil.copyfile(cppFile, CPP_EXT.format(file))
        bigHeaderIncludes.addAll(dependencies);
    prepareBigHeader(bigHeaderIncludes);
    prepareCMakeLists();

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
    print(e)
    pass