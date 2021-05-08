words = set()

def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip())
    file.close()
    return True

def check(word):
    if word.lower() in words:
        return True
    elif:
        return False

def size()
    return len(words)

def unload()
    return True
