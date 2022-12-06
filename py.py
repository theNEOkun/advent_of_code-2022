def main():
    with open('resources/input_day5') as file:
        stacks, commands = file.read().strip().split('\n\n')
        stacks = ["".join(list(row)).strip() for row in list(
            zip(*stacks.split("\n")[:-1][::-1]))[1::4]]
        commands = [[int(x) for x in line.split(" ")[1::2]]
                    for line in commands.split('\n')]

    #test1= ['NZ', 'DCM', 'P']
    #test2= [[1, 2, 1], [3, 1, 3], [2, 2, 1], [1, 1, 2]]

    def rearrange(q, a, b, s):
        new_stacks = s[:]
        p = s[a-1][:q]
        new_stacks[a-1] = new_stacks[a-1][q:]
        new_stacks[b-1] = p[::-1] + new_stacks[b-1]
        return new_stacks

    for move in commands:
        stacks = rearrange(*move, stacks)
    part_one = ''

    for each in stacks:
        part_one = part_one+each[0]

    print(part_one)
    return


if __name__ == '__main__':
    main()
