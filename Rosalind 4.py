
count = 1

for line in open('/Users/Bora/Downloads/input.txt', 'r'):
    if count%2 == 0:
        print(line)
    count += 1