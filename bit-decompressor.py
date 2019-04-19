f = open("compressor_output_py.txt", "r")

hexstr = ""
for c in f.read():
	hexstr += "{:02x}".format(ord(c))

print(hexstr)
marker_list = []
block_marker_list = []
for i in range(len(hexstr)-1):
	if "ff" == hexstr[i:i+2]:
		# print(hexstr[i:i+6])
		marker_list.append(hexstr[i:i+6])
		block_marker_list.append(int(hexstr[i+4:i+6], 16))

# print(block_marker_list)

for marker_nums in range(len(marker_list)):
	# gives the index for the current marker to replace for the marker list and block marker list.
	next_block_index = block_marker_list.index(min(block_marker_list))
	# current marker position in hexstr.
	marker_pos = hexstr.find(marker_list[next_block_index])
	# position and block length of current marker.
	pos, blk = (int(marker_list[next_block_index][2:4], 16), int(marker_list[next_block_index][4:6], 16))
	print("marker pos: {}\tpos: {}\tblk: {}".format(marker_pos, pos, blk))
	# the string reference of the current marker
	substr_to_copy = hexstr[marker_pos - pos*blk: blk]
	print(substr_to_copy)
	# replace the marker in the hexstr for it's string reference.
	hexstr = hexstr.replace(marker_list[next_block_index], substr_to_copy, 1)
	# Eliminate the current marker from the lists
	marker_list.pop(next_block_index)
	block_marker_list.pop(next_block_index)

print("\n")
print(hexstr)