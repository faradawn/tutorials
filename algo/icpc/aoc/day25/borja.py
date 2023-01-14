"""
Day 25
https://adventofcode.com/2022/day/25
1st star: 00:29:47
2nd star: 00:29:50
As usual, a much less elaborate problem to finish
up Advent of Code, although I did get tripped up
in the decimal-to-SNAFU part and initially followed
an approach that was way more complicated than it
neded to be (and, after staring at the
decimal-to-snafu table long enough, finally realized
the straightforward way to do the conversion)
UPDATE (12/25): I added the implementation of my
original approach, which was originally not working
because I had mixed up roots with logs *facepalm*
(still glad I wasn't that far off target)
"""

import util
import math
import sys
import re

from util import log


def snafu2decimal(snafu):
    """
    Converts a SNAFU number to a decimal number
    """
    DIGITS = {"2": 2, "1": 1, "0": 0, "-": -1, "=": -2}

    dec = 0
    for power, digit in enumerate(reversed(snafu)):
        five = 5**power

        dec += DIGITS[digit] * 5**power

    return dec


def decimal2snafu(dec):
    """
    Converts a decimal number to a SNAFU number
    """
    DIGITS = {4: "2", 3: "1", 2: "0", 1: "-", 0: "="}
    snafu = []

    while dec > 0:
        snafu.append(DIGITS[(dec+2) % 5])
        dec = (dec+2) // 5

    return "".join(reversed(snafu))


def decimal2snafu_alt(dec):
    """
    Alternate (more convoluted) way of computing
    the SNAFU number
    """
    DIGITS = {"2": 2, "1": 1, "0": 0, "-": -1, "=": -2}
    max_power = int(math.log(dec, 5))

    rem = dec
    snafu = ""
    for i in range(max_power, -1, -1):
        for digit, value in DIGITS.items():
            ub = snafu2decimal(digit + "2"*i)
            lb = snafu2decimal(digit + "="*i)
            if lb <= rem <= ub:
                snafu += digit
                rem -= (5**i) * value
                break
            
    return snafu


def task1(input):
    """
    Compute the decimal sum of the snafu numbers,
    and produce the snafu representation of the sum
    """
    s = 0
    for snafu in input:
        s += snafu2decimal(snafu)

    return decimal2snafu(s)


if __name__ == "__main__":
    util.set_debug(False)

    sample = util.read_strs("ex1.txt", sep="\n")
    input = util.read_strs("input1.txt", sep="\n")

    print("TASK 1")
    util.call_and_print(task1, sample)
    util.call_and_print(task1, input)