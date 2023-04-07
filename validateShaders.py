#!/usr/bin/env python

from subprocess import PIPE,run

def validate(pth:str):
	print("validating \"",pth,"\"... ",end='',sep='')

	pth  = "bowshock/shader/" + pth + ".glsl"
	prog = "glslangValidator"

	stat = run([prog,pth],stdout=PIPE)

	ret = stat.returncode
	if ret != 0x0:
		print("\x1B[38;5;161merror\x1B[0m")
		print()
		print(stat.stdout.decode("utf-8"))
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
