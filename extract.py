import argparse

try:
    parser = argparse.ArgumentParser(description="Minimal cpput extract script.")
    parser.add_argument("--include", type=str, help="Comma separated list of included files (without extensions)", default="");
    parser.add_argument("--exclude", type=str, help="Comma separated list of excluded files (without extensions)", default="");


    print("cpput extract ready!")
except Exception  as e:
    print(e);
    pass