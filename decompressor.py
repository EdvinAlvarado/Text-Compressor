f = open("test.czip", "r")
counter = 0


compressed_str = f.read()
# print(compressed_str)

dic = {}

for itempair in compressed_str.split("/"): # limit the list to avoid the '' end line.
	print(itempair)
	itempairlist = itempair.split("|")
	dic[itempairlist[0]] = []
	print(itempairlist)
	try:
		for hex_location in itempairlist[1].split(","):
			print(hex_location)
			dic[itempairlist[0]].append(int(hex_location, 16))
	except IndexError:
		pass


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