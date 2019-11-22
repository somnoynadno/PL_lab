from random import randint

N = 100000000

a = []
minim = 2147483647
for i in range(N):
    num = randint(-2147483647, 2147483647)
    if num < minim:
        minim = num
    a.append(str(num))

handler = open('data.txt', 'w')
handler.write(str(N) + " " + " ".join(a) + " " + str(minim))
handler.close()
print(minim)
