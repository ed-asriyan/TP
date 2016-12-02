import string
from sys import stderr
from random import choice


def test_command(command=None, value=None, items=None):
    if command == '+':
        if value in items:
            return False
        else:
            items.append(value)
            return True

    if command == '-':
        if value in items:
            items.remove(value)
            return True
        else:
            return False

    if command == '?':
        return value in items

    return '+-?'


def generate_string(length):
    dictionary = string.digits + string.ascii_uppercase + string.ascii_lowercase
    return ''.join([choice(dictionary) for _ in range(length)])


def generate_tests(count, item_len, equality_level):
    dictionary = [generate_string(item_len) for _ in range(int(count * equality_level))]

    items = []

    input = []
    output = []

    for _ in range(count):
        command = choice(test_command())
        value = choice(dictionary)
        test = test_command(command, value, items)

        input.append(command + ' ' + value)
        output.append('OK' if test else 'FAIL')

    return input, output

if __name__ == '__main__':
    _input, _output = generate_tests(10, 5, 0.5)

    print('\n'.join(_input))

    for i in _output:
        print(input(), i, file=stderr)


