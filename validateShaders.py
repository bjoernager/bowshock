#!/usr/bin/env python

from subprocess import PIPE,run

def validate(path:str):
	print("validating \"",path,"\"... ",end='',sep='')

	path  = "bowshock/shader/" + path + ".glsl"
	prog = "glslangValidator"

	status = run([prog,path],stdout=PIPE)

	result = status.returncode
	if result != 0x0:
		print("\x1B[38;5;161merror\x1B[0m")
		print()
		print(status.stdout.decode("utf-8"))
		quit(0x1)

	print("\x1B[38;5;77mokay\x1B[0m")

if __name__ == "__main__":
	print("validating shaders...")

	shaders = [
		"main.frag",
		"main.vert",
	]

	for shader in shaders:
		validate(shader)

	print("success")
