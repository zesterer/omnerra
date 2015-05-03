import sys

if __name__ == "__main__":
	for arg in sys.argv:
		print("Converting file %s..." % arg)

		filer = open(arg)
		lines = filer.readlines()
		
		vertices = []
		texcoords = []
		normals = []
		faces[]

		for line in lines:
			line = line[:-1] #Strip newline

			while line[0] in [" ", "	"] && len(line) > 0: #Strip initial whitespace
				line = line[1:]

			parts = line.split(" ")
			
			if len(line) > 0:
				if parts[0[0]] != "#":
					if parts[0] == "v":
						vertices.append([float(parts[1]), float(parts[2]), float(parts[3]), float(parts[4]), float(parts[5]), float(parts[6])])
					elif parts[0] == "vt":
						texcoords.append([float(parts[1]), float(parts[2])])
					elif parts[0] == "vn":
						normals.append([float(parts[1]), float(parts[2]), float(parts[3])])
					elif parts[0] == "f":
						faces.append([float(parts[1]), float(parts[2]), float(parts[3])])

			print(line[:-1])
