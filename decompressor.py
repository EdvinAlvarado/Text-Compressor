f = open("test.czip", "r")
lst = []
counter = 0
for line in f.readlines():
	lst = line.split("/")
	print(lst)

dic = {}

for itempair in lst[:len(lst)-1]: # limit the list to avoid the '' end line.
	itempairlist = itempair.split("|")	
	dic[itempairlist[0]] = []
	# print(dic)
	for num in itempairlist[1].split(","):
		print(num)
		dic[itempairlist[0]].append(int(num, 16))


print(dic)

counter = 0
decoded = ""

word_count = 0
for lstval in dic.values():
	# print(vals)
	for vals in lstval:
		word_count = max(word_count, vals)
# print(word_count)

for i in range(word_count):
	for key, val in dic.items():
		for num in val:
			if num == counter:
				decoded += key
				decoded += " "
				counter += 1

print(decoded)

w = open("decompressed test.txt", 'w')
w.write(decoded[:len(decoded)-1])
w.close()