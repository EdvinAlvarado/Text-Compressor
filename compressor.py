# better text compressor than zip file for repeating words
# can't work with newlines.
f = open("hardtest.txt", "r")
# f = open("repeatingtest.txt", "r")
s = f.readline()
lst = s.split(" ")
setlist = set(lst)
print(lst)
print(setlist)
dic = {}

for word in setlist:
	dic[word] = []

for i in range(len(lst)):
	for unique_word in setlist:
		print("word: {}\tunique word: {}".format(lst[i], unique_word))
		if lst[i] == unique_word:
			dic[unique_word].append(i)
			print(dic)


print(dic)
f.close()
w = open("test.czip", "w")
for keys, values in dic.items():
	w.write("{}|".format(keys))
	for i in range(len(values)):
		w.write(str(hex(values[i])[2:]))
		# w.write(str(values[i]))
		if i != len(values)-1:
			w.write(",")
		else:
			w.write("/")
w.close()
