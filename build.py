#START: SCRIPT CONFIG AND SETUP
import os, sys, subprocess, platform
WORKSPACE_DIR = os.path.normpath(f'{os.path.dirname(os.path.realpath(__file__))}/.workspace').replace('\\', '/')
PROJECT_DIR = os.path.normpath(f'{os.path.dirname(os.path.realpath(__file__))}/').replace('\\', '/')
if not os.path.exists(f'{WORKSPACE_DIR}/build_tools/'): 
    link = "https://github.com/WojciechSobczak/build/releases/download/0.0.4/setup.py"
    if platform.system() == "Windows": 
        subprocess.run(args=f"powershell -command Invoke-WebRequest {link} -OutFile setup.py; python3 setup.py -w .workspace", cwd=PROJECT_DIR, shell=True)
    if platform.system() == "Linux": 
        subprocess.run(args=f"curl --output setup.py {link} && python3 setup.py -w .workspace", cwd=PROJECT_DIR, shell=True)
sys.path.append(f'{WORKSPACE_DIR}/build_tools/')
#END: SCRIPT CONFIG AND SETUP


import shutil
import argparse
import build_tools #type: ignore

def setup_toolset(args: argparse.Namespace) -> build_tools.BuildToolsConfig:
    os.makedirs(WORKSPACE_DIR, exist_ok=True)
    if not build_tools.cmake.is_cmake_in_workspace_toolset(WORKSPACE_DIR):
        build_tools.cmake.download_cmake(WORKSPACE_DIR)
    if not build_tools.ninja.is_ninja_in_workspace_toolset(WORKSPACE_DIR):
        build_tools.ninja.download_ninja(WORKSPACE_DIR)
        
    cmake_exe = build_tools.cmake.get_toolset_cmake_exe_path(WORKSPACE_DIR)
    ninja_exe = build_tools.ninja.get_toolset_ninja_exe_path(WORKSPACE_DIR)

    # If you have all tools in path, just replace it with plain names as here
    # this is disabled by default as it requires environment setup
    if False:
        cmake_exe = shutil.which("cmake")
        ninja_exe = shutil.which("ninja")
        conan_exe = shutil.which("conan")
        vcpkg_exe = shutil.which("vcpkg")

    assert(cmake_exe is not None)
    assert(ninja_exe is not None)
    assert(args.mode is not None)

    return build_tools.BuildToolsConfig(cmake_exe, None, None, ninja_exe, WORKSPACE_DIR, PROJECT_DIR, args.mode)

def main():
    parser = argparse.ArgumentParser(description="cpput build utilities")
    parser.add_argument('-c', '--config', default=False, action='store_true', help="Build cmake config.")
    parser.add_argument('-b', '--build', default=False, action='store_true', help="CMake build.")
    parser.add_argument('-r', '--rebuild', default=False, action='store_true', help="CMake delete cache and rebuild.")
    parser.add_argument('-m', '--mode', default="debug", help="Build mode. [debug, release, ...]")
    parser.add_argument('-d', '--dependencies', default=False, action='store_true', help="Download dependencies")
    parser.add_argument('--clion', default=False, action='store_true', help="Create CLion configurations for the project")
    args = parser.parse_args()

    toolset_config = setup_toolset(args)
    cmake_config = build_tools.cmake.Config(
        build_dir = f'{toolset_config.workspace_dir}/cmake/build',
        list_dir = f'{toolset_config.project_dir}',
        build_type = args.mode
    )
    if args.rebuild or args.config or args.build:
        build_tools.vcvarsall.load_vcvarsall_env_if_possible(WORKSPACE_DIR, PROJECT_DIR)
    if args.rebuild:
        build_tools.cmake.delete_cache(cmake_config)
    if args.config or args.rebuild:
        build_tools.cmake.configure(cmake_config, toolset_config)
    if args.build or args.rebuild:
        build_tools.cmake.build_project(cmake_config, toolset_config)
    if args.clion:
        build_tools.clion.create_build_tools_configurations(cmake_config, toolset_config)

if __name__ == "__main__":
    main()



