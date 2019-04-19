string = "HHHHHHHHHHHHHHHHHHHHHHH"
f = open("compressor comparison.txt","w")
f.write(string)
f.write("\n")

hexstr = ""
# Creates the hexstring version of the string.
for c in string:
	# ord(c) gives ASCCI code.
	# {:08b} prints int as a unsigned 8 bit.
	hexstr += hex(ord(c))[2:]

print(hexstr)

initial_len_hexstr = len(hexstr)
print(initial_len_hexstr)

# Starting size will be just one bigger of half of the length but its capped at 65636. This is because that is the max distance the marker FFXXYY can do.
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

# Goes from the starting size to 6 because the marker itself is 6 hexes long because anything less than 7 will not compressed or just make it bigger.
for block in range(starting_size(len(hexstr)), 6, -1):
	print("block size: {}".format(block))	

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

# Here takes the hexstr and maps them to their assci char. You will get characters that don't exist.
compressed_hexstr = ""
for i in range(0, len(hexstr)-1,  2):
	print("hex: {}\tasci:i {}\tchar: {}".format(hexstr[i:i+2], int(hexstr[i:i+2], 16), chr(int(hexstr[i:i+2], 16))))
	compressed_hexstr += chr(int(hexstr[i:i+2], 16))

# Results
print(string)
print(hexstr)
print(compressed_hexstr)
print("hex length before: {}\nhex length after: {}\ncompressed hex to char length: {}".format(initial_len_hexstr, len(hexstr), len(compressed_hexstr)))

# Writes Results to text and gives the output for the decompressor.
f.write(hexstr)
f.write("\n")
f.write(compressed_hexstr)
f.close()
output = open("compressor_output_py.txt", "w")
output.write(compressed_hexstr)
output.close()