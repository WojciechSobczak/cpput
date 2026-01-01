# This is "you do you" file and it is intended to give head start
# and be edited as your project need
# It will give you basic usage and is intended to be used as build script 
# for the project and be part of the repository
# It should be downloaded by setup.py script from build_tools repo, but use
# it as you like
# HF

#START: SCRIPT CONFIG AND SETUP
import os, sys, subprocess, platform
WORKSPACE_DIR = f'{os.path.dirname(os.path.realpath(__file__))}/.workspace'
PROJECT_DIR = f'{os.path.dirname(os.path.realpath(__file__))}/'
sys.path.append(WORKSPACE_DIR)
if not os.path.exists(f'{WORKSPACE_DIR}/build_tools/'): 
    link = "https://github.com/WojciechSobczak/build/releases/download/0.0.2/setup.py"
    if platform.system() == "Windows": 
        subprocess.run(args=f"powershell -command Invoke-WebRequest {link} -OutFile setup.py; python3 setup.py -w .workspace", cwd=PROJECT_DIR, shell=True)
    if platform.system() == "Linux": 
        subprocess.run(args=f"curl --output setup.py {link} && python3 setup.py -w .workspace", cwd=PROJECT_DIR, shell=True)
#END: SCRIPT CONFIG AND SETUP

import argparse
import build_tools #type: ignore

def setup_toolset() -> tuple[str, str, str]:
    if not build_tools.cmake.is_cmake_in_workspace_toolset(WORKSPACE_DIR):
        build_tools.cmake.download_cmake(WORKSPACE_DIR)
    if not build_tools.ninja.is_ninja_in_workspace_toolset(WORKSPACE_DIR):
        build_tools.ninja.download_ninja(WORKSPACE_DIR)
    if not build_tools.conan.is_conan_in_workspace_toolset(WORKSPACE_DIR):
        build_tools.conan.download_conan(WORKSPACE_DIR)
    cmake_exe = build_tools.cmake.get_toolset_cmake_exe_path(WORKSPACE_DIR)
    ninja_exe = build_tools.ninja.get_toolset_ninja_exe_path(WORKSPACE_DIR)
    conan_exe = build_tools.conan.get_toolset_conan_exe_path(WORKSPACE_DIR)
    return (cmake_exe, conan_exe, ninja_exe)

def load_environment():
    with open(f"{PROJECT_DIR}/.env", "r", encoding="UTF-8") as file:
        for line in file.readlines():
            key, value = [text.strip() for text in line.split('=')]
            os.environ[key] = value
    
    if platform.system() == "Windows":
        process = subprocess.run(
            f'{os.environ['VC_VARSALL']} x64 > nul && SET',
            env=os.environ.copy(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            shell=True
        )
        for line in process.stdout.decode().splitlines():
            key, value = [text.strip() for text in line.split('=')]
            os.environ[key] = value

def main():
    os.makedirs(WORKSPACE_DIR, exist_ok=True)
    cmake_exe, conan_exe, ninja_exe = setup_toolset()

    parser = argparse.ArgumentParser(description="Cpp Useful Things Build Script")
    parser.add_argument('-c', '--config', default=False, action='store_true', help="Build cmake config.")
    parser.add_argument('-b', '--build', default=False, action='store_true', help="CMake build.")
    parser.add_argument('-r', '--rebuild', default=False, action='store_true', help="CMake delete cache and rebuild.")
    parser.add_argument('-m', '--mode', default="debug", choices=['debug', 'release'], help="Build mode. [debug, release]")
    parser.add_argument('-d', '--dependencies', default=False, action='store_true', help="Download dependencies")
    args = parser.parse_args()

    cmake_config = build_tools.cmake.CMakeConfig(
        cmake_exe = cmake_exe,
        cmake_build_folder = f'{WORKSPACE_DIR}/cmake/build',
        cmake_list_dir = f'{PROJECT_DIR}',
        cmake_build_type = args.mode
    )
        
    if args.rebuild:
        build_tools.cmake.delete_cache(cmake_config)
    if args.dependencies:
        build_tools.conan.create_profiles(conan_exe, cmake_exe, PROJECT_DIR, WORKSPACE_DIR, ninja_exe)
        build_tools.conan.download_dependencies(conan_exe, args.mode, PROJECT_DIR, WORKSPACE_DIR, ninja_exe)

    if args.config or args.rebuild or args.build:
        load_environment()
    if args.config or args.rebuild:
        build_tools.cmake.configure(cmake_config, WORKSPACE_DIR, ninja_exe)
    if args.build or args.rebuild:
        build_tools.cmake.build_project(cmake_config)

if __name__ == "__main__":
    main()



