from cs50 import get_string

s = get_string("Text: ")
letters = 0
sentance = 0
words = 1

for i in range(len(s)):
    if s[i] == ' ' and s[i + 1]:
        words += 1
    elif s[i] == '.' or s[i] == '?' or s[i] == '.':
        sentance += 1
    elif s[i].isalpha():
        letters += 1


L = float(letters / words * 100)
S = float(sentance / words * 100)

# answer = round(0.0588 * (100 * float(letters) // float(words)) - 0.296 * (100 * float(sentance) // float(words)) - 15.8)
index = round((float)(0.0588 * L - 0.296 * S - 15.8))


if index < 16 and index >= 0:
    print(f"Grade {int(index)}")
elif index >= 16:
    print("Grade 16+")
else:
    print("Before Grade 1")
