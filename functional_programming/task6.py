from itertools import cycle, islice

def readCoords(n):
	if n == 0:
		return []
	coords = int(input()), int(input())
	return readCoords(n-2) + [coords]


def readTriags(n):
	triags = []
	for _ in range(n):
		triag = readCoords(6)
		triags.append(triag[::-1])
	return triags


def giveVector(dots):
	if len(dots) == 1:
		return []
	else:
		return giveVector(dots[1:]) + list(y-x for x, y in zip(dots[0], dots[1]))


def main():
	n = int(input())
	triags = readTriags(n)
	k = float(input())
	print(triags)
	# k = 2
	# triags = [[(7, 0), (0, 4), (7, 4)]]
	for triag in triags:
		vector = giveVector(list(islice(cycle(triag), 4)))
		vector = list(map(lambda x: x*k, vector))
		print(*vector)


if __name__ == "__main__":
	main()
