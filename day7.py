import sys


class Folder:
    def __init__(self, char=""):
        self.size = 0;
        self.files = {}
        self.sub_folders = {}
        self.name = char
        self.parent = None

    def insertFolder(self, name):
        self.sub_folders[name] = Folder(name)
        self.sub_folders[name].parent = self

    def insertFile(self, name, size):
        self.files[name] = File(name, size)
        self.addSize(size)

    def addSize(self, size):
        self.size += int(size)
        if self.parent is not None:
            self.parent.addSize(size)

    def print(self):
        for folder_name in self.sub_folders:
            print(self.sub_folders[folder_name].name)
        for file_name in self.files:
            print(self.files[file_name].name)

    def print_all(self):
        for folder_name in self.sub_folders:
            print(self.name + ": " + self.sub_folders[folder_name].name + " " + str(self.sub_folders[folder_name].size))
            self.sub_folders[folder_name].print_all()
        for file_name in self.files:
            print(self.name + ": " + self.files[file_name].name)


class File:
    def __init__(self, name, size):
        self.name = name
        self.size = size


class Tree:
    def __init__(self):
        self.root = Folder("/")
        self.all_folders = []
        self.all_folders.append(self.root)

    def print_folder_size(self):
        for f in self.all_folders:
            print(f.name + " " + str(f.size))


def readInput():
    result = []
    with open("data/day7.txt") as f:
        for line in f:
            result.append(list(line.strip('\n').split(' ')))
    return result


def buildTree():
    commands = readInput()
    my_tree = Tree()
    current_node = my_tree.root
    for command in commands:
        if command[0] == "$":
            if command[1] == "cd":
                if command[2] == "/":
                    current_node = my_tree.root
                elif command[2] == "..":
                    current_node = current_node.parent
                else:
                    current_node = current_node.sub_folders[command[2]]
        elif command[0] == "dir":
            current_node.insertFolder(command[1])
            my_tree.all_folders.append(current_node.sub_folders[command[1]])
        else:
            current_node.insertFile(command[1], command[0])
    return my_tree


my_tree = buildTree()
# my_tree.root.print_all()
# my_tree.print_folder_size()
# ans1 = 0
# for f in my_tree.all_folders:
#     if f.size <= 100000:
#         ans1 += f.size
# print(ans1)

free_size = 70000000 - my_tree.root.size
need_delete_size = 30000000 - free_size
ans2 = 70000000
for f in my_tree.all_folders:
    if f.size > need_delete_size:
        if f.size < ans2:
            ans2 = f.size
print(ans2)

