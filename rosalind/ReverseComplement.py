str = ''
reverse = ''
for i in str:
    if i == 'A':
        reverse = 'T' + reverse
    elif i == 'C':
        reverse = 'G' + reverse
    elif i == 'G':
        reverse = 'C' + reverse
    elif i == 'T':
        reverse = 'A' + reverse
print(reverse)