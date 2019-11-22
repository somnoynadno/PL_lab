def read_triags(n):
	arr = []
	for i in range(n):
		arr.append(list(map(int, input().split())))
	return arr


def to_vector(arr):
	vec = []
	for elem in arr:
		x1, x2, x3, x4, x5, x6 = elem
		vec.append([x3-x1, x4-x2, x5-x3, x6-x4, x1-x5, x2-x6])
	return vec


def mult(arr, k):
	ans = []
	for elem in arr:
		ans.append(list(map(lambda x: x*k, elem)))
	return ans


def my_awesome_print(arr):
	for elem in arr:
		print(*elem)


my_awesome_print(mult(to_vector(read_triags(int(input()))), int(input())))
