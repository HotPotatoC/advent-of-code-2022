import argparse
import os
import shutil

PREFIX = "day-"


parser = argparse.ArgumentParser()

parser.add_argument(
    "-i",
    "--input-method",
    help="Input method (file or piped)",
    required=True,
    choices=["file", "piped"],
)

args = parser.parse_args()


def main():
    """
    Sequentially creates a new day_xx directory containing
    the C++ starter code and input files
    """

    dirs = os.listdir()
    days = sorted(filter(lambda s: s.startswith(PREFIX), dirs))

    next_day = int(days[len(days) - 1][4:]) + 1
    next_day_dir = PREFIX

    if next_day < 10:
        next_day_dir += "0"

    next_day_dir += str(next_day)

    if next_day not in days:
        os.mkdir(next_day_dir)
        if args.input_method == "file":
            shutil.copyfile(
                "./.template.file.cpp", os.path.join(next_day_dir, "main.cpp")
            )
        elif args.input_method == "piped":
            shutil.copyfile(
                "./.template.piped.cpp", os.path.join(next_day_dir, "main.cpp")
            )

        fp = open(os.path.join(next_day_dir, "input.in"), "w")
        fp = open(os.path.join(next_day_dir, "input.sample.in"), "w")
        fp.close()


if __name__ == "__main__":
    main()
