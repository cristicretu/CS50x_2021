# DNA Matcher

import csv
import sys

# Problem understanded from:
# https://joseph28robinson.medium.com/cs50-pset-6-dna-4158fb5317ca

def main():
    if len(sys.argv) != 3:
        print('Usage: python dna.py database.csv sequence.txt')
        exit(1)

    # Get the name of the input files
    database_p = sys.argv[1]
    sequence_p = sys.argv[2]

    # Read from the database.csv
    with open(database_p, 'r') as file:
        reader = csv.DictReader(file)
        database_list = list(reader)

    # Read the sequence
    with open(sequence_p, 'r') as file:
        sequence = file.read()

    # Store all the needed sub-sequences
    STR = []
    answer = []
    for i in range(1, len(reader.fieldnames)):
        STR = (reader.fieldnames[i])
        answer.append(0)

        # Go through the sequence
        for j in range(len(sequence)):
            current_count = 0

            if sequence[j:(j + len(STR))] == STR:
                k = 0
                while sequence[(j + k):(j + k + len(STR))] == STR:
                    current_count += 1
                    k += len(STR)

                answer[i - 1] = max(answer[i - 1], current_count)

    # Search for similarities
    for i in range(len(database_list)):
        goal = 0
        for j in range(1, len(reader.fieldnames)):
            if int(answer[j - 1]) == int(database_list[i][reader.fieldnames[j]]):
                goal += 1
            if goal == (len(reader.fieldnames) - 1):
                print(database_list[i]['name'])
                exit(0)
    print("No match")

if __name__ == "__main__":
    main()

