string = "hello"

binstring = ""
for c in string:
	# ord(c) gives ASCCI code.
	# {:08b} prints int as a unsigned 8 bit.
	binstring += "{:08b}".format(ord(c))

print(binstring)
discrete_sizes = [4, 8, 16, 32, 64, 128, 256]
len_bitstring = len(binstring)
print("length {}".format(len_bitstring))
tempsizes = [len_bitstring // size for size in discrete_sizes]
# print(tempsizes)
# starting_size = discrete_sizes[tempsizes.index(2)]

bit_sizes = discrete_sizes[:tempsizes.index(2)+1:][::-1]
print(bit_sizes)


length_counter = len(binstring)
binstring_list = []
for bitsize in bit_sizes:
	while length_counter > bitsize:
		print(binstring[])