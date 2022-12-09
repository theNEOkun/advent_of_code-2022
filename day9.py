from dataclasses import dataclass

with open("resources/input_day9") as f_obj:
    lines = [line.rstrip() for line in f_obj.readlines()]


@dataclass
class Point():
    """Class for modeling a point."""
    x: int
    y: int

    def __add__(self, other):
        """Override +"""
        return Point(self.x + other.x, self.y + other.y)

    def __iadd__(self, other):
        """Override +="""
        self.x += other.x
        self.y += other.y
        return self

    def get_coordinates(self):
        """Returns a tuple of current coordinates."""
        return (self.x, self.y)


def print_bridge(head, tail, rows=5, cols=6):
    """Prints bridge."""
    bridge = [list("." * cols) for i in range(rows)]

    bridge[tail.y][tail.x] = "T"
    bridge[head.y][head.x] = "H"

    for row in reversed(bridge):
        print("".join(row))

    print()


def move_tail(head, tail):
    """Moves tail if head and tail are not touching."""
    x_diff = head.x - tail.x
    y_diff = head.y - tail.y

    # Head is 2 steps to the left or right from the tail.
    if abs(x_diff) == 2 and y_diff == 0:
        tail.x += x_diff // 2

    # Head is 2 steps to the up or down from the tail.
    elif abs(y_diff) == 2 and x_diff == 0:
        tail.y += y_diff // 2

    # Handles diagonal movement of tail
    elif (abs(x_diff) + abs(y_diff)) > 2:
        tail.x += x_diff // abs(x_diff)
        tail.y += y_diff // abs(y_diff)


movement = {"U": Point(0, 1), "D": Point(
    0, -1), "L": Point(-1, 0), "R": Point(1, 0)}

head = Point(0, 0)
tail = Point(0, 0)

tail_positions = set()
tail_positions.add(tail.get_coordinates())

for line in lines:
    direction, steps = line.split()

    for i in range(int(steps)):
        head += movement[direction]
        move_tail(head, tail)
        tail_positions.add(tail.get_coordinates())

print(len(tail_positions))
