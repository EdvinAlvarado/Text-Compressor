string = "HHHHHHHHHHHHHHHHHHHHHHH"
f = open("compressor comparison.txt","w")
f.write(string)
f.write("\n")

hexstr = ""
for c in string:
	# ord(c) gives ASCCI code.
	# {:08b} prints int as a unsigned 8 bit.
	hexstr += hex(ord(c))[2:]

print(hexstr)

initial_len_hexstr = len(hexstr)
print(initial_len_hexstr)

def starting_size(length):
	if length < 65636:
		if (length > 2) and (length % 2 == 0):
			return length // 2
		elif (length > 2) and (length % 2 != 0):
			return (length - 1) // 2
	elif length >= 65636:
		return 65636
	else:
		print("wrong hexstr length.")

# print(starting_size(len_hexstr))

print("\n")

for block in range(starting_size(len(hexstr)), 6, -1):
	print("block size: {}".format(block))	
	# hexstr_list = []
	# n = 0	
	# for n in range(len_hexstr // block + 1):
	# 	print("n: {}".format(n))
	# 	if block * (n+1) > len_hexstr:
	# 		print(hexstr[block*n :])
	# 		hexstr_list.append(hexstr[block*n :])
	# 	else:
	# 		print(hexstr[block*n : block * (n+1)])
	# 		hexstr_list.append(hexstr[block*n : block * (n+1)])
	# print(hexstr_list)
	# print("\n")
	for i in range(block, len(hexstr) - 6):
		if len(hexstr[i:i+block]) == block:
			# print("{:>22}".format(hexstr[i:i+block]))
			print("i = {}\nposition = {}\n{}\n{}\n".format(i, i - block + 1, hexstr[:block], hexstr[i:i+block]))
			if hexstr[:block] == hexstr[i:i+block]:
				print("MATCH")
				print(hexstr[:i])
				print("FF" + "{:02x}".format(i - block + 1) + "{:02x}".format(block))
				print(hexstr[i+block:])
				hexstr = hexstr[:i] + "FF" + "{:02x}".format(i - block + 1) + "{:02x}".format(block) + hexstr[i+block:]
				print(hexstr + "\n")




compressed_str = ""
for i in range(0, len(hexstr)-2,  2):
	print("hex: {}\tint: {}\tchar: {}".format(hexstr[i:i+2], int(hexstr[i:i+2], 16), chr(int(hexstr[i:i+2], 16))))
	compressed_str += chr(int(hexstr[i:i+2], 16))

print(string)
print(hexstr)
print(compressed_str)
print("hex length before: {}\nhex length after: {}\ncompressed hex to char length: {}".format(initial_len_hexstr, len(hexstr), len(compressed_str)))


f.write(hexstr)
f.write("\n")
f.write(compressed_str)
f.close()
output = open("compressor_output_py.txt", "w")
output.write(compressed_str)
output.close()