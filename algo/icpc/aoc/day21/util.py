"""
Utility functions and classes for Advent of Code
"""

# import shapely.geometry
# import shapely.affinity
import math
import copy
import parse

#
# DEBUGGING/LOGGING
#

DEBUG=False

def set_debug(debug):
    """
    Enables/disables debug messages
    """
    global DEBUG
    DEBUG = debug


def log(*args):
    """
    Prints a debugging message (if debugging messages are enabled)
    """
    if DEBUG: 
        print('\x1b[7;30;47m', end="")
        print(*args, end="")
        print('\x1b[0m')


def call_and_print(fn, *args):
    """
    Call a function with some parameters, and print the
    function call and the return value.
    """
    str_args = ", ".join(repr(arg) for arg in args)

    if len(str_args) > 20:
        str_args = str_args[:20] + "..."

    print("{}({}) = {}".format(fn.__name__, str_args, fn(*args)))


#
# FILE I/O
#

def read_strs(filename, sep=None, sep2=None):
    """
    Read strings from a file, separated by whitespace or by the
    specified separator.
    """
    with open(filename) as f:
        txt = f.read().strip()
        strs = txt.split(sep=sep)  

    if sep2 is not None:
        strs = [s.split(sep=sep2) for s in strs]

    return strs


def read_ints(filename, sep=None, sep2=None):
    """
    Read integers from a file, separated by whitespace or by the
    specified separator.
    """
    strs = read_strs(filename, sep, sep2)
    
    if sep2 is not None:
        return [[int(x) for x in s] for s in strs]
    else:
        return [int(x) for x in strs]


def iter_parse(strings, fmt):
    """
    Generator function that iterates over a sequence of strings,
    and returns the values parsed according to a format string
    """
    p = parse.compile(fmt)

    for s in strings:
        yield p.parse(s)


#
# UTILITY FUNCTIONS / CLASSES
#

class Grid:
    """
    Used to manipulate grids with one character per position,
    using (x,y) coordinates (where the top-left position is 0,0)
    """
    
    # Useful for problems that require checking adjacent positions
    DIRECTIONS = [(-1, -1), (0, -1), (+1,-1),
                  (-1,  0),          (+1, 0),
                  (-1, +1), (0, +1), (+1,+1)]

    CARDINAL_DIRS = [          (0, -1),
                     (-1,  0),          (+1, 0),
                               (0, +1)         ]                  

    def __init__(self, grid, infinite_x=False, infinite_y=False):
        self.infinite_x = infinite_x
        self.infinite_y = infinite_y
        self._grid = copy.deepcopy(grid)


    def __str__(self):
        rows = ["".join(str(x) for x in row) for row in self._grid]
        return "\n".join(rows)

    def copy(self):
        return Grid(self._grid, self.infinite_x, self.infinite_y)

    @property
    def max_x(self):
        return len(self._grid[0])

    @property
    def max_y(self):
        return len(self._grid)

    def __validate_coords(self, x, y):
        orig_x = x
        orig_y = y

        if self.infinite_x:
            x = x % self.max_x
        
        if self.infinite_y:
            y = y % self.max_y

        if not 0 <= x < self.max_x or not 0 <= y < self.max_y:
            raise IndexError(f"Invalid position ({x}, {y}). Original: ({orig_x}, {orig_y})")

        return x, y        

    def get(self, x, y):
        x, y = self.__validate_coords(x, y)

        return self._grid[y][x]

    def getdefault(self, x, y, default=None):
        try:
            return self.get(x, y)
        except IndexError:
            return default

    def valid(self, x, y):
        try:
            self.__validate_coords(x, y)
            return True
        except IndexError:
            return False

    def set(self, x, y, value):
        x, y = self.__validate_coords(x, y)

        self._grid[y][x] = value

    @classmethod
    def _from_lines(cls, lines, cast=None):
        # We convert each line to a list, in case we
        # need to modify the contents of the grid
        grid = [list(line) for line in lines]

        if cast is not None:
            grid = [[cast(v) for v in row] for row in grid]

        return cls(grid)

    @classmethod
    def from_file(cls, filename, cast=None):
        lines = read_strs(filename, sep="\n")

        return cls._from_lines(lines, cast)

    @classmethod
    def from_string(cls, grid_str, cast=None):
        lines = grid_str.strip().split(sep="\n")

        return cls._from_lines(lines, cast)

    @classmethod
    def empty(cls, max_x, max_y, char=" "):
        grid = [[char] * max_x for _ in range(max_y)]

        return cls(grid)        


