// Copyright 2022-2023 Gabriel Jensen.

#pragma once

#include <bow/run.h>

#include <glad/glad.h>

typedef struct {
	char const * savPth;
	bool         hasSavPth:0x1u;
	bool         newSav:0x1u;
	bool         skip:0x1u;
} bow_termOpts;

char const * bow_getSavPth(void);
bool         bow_getQuot(  char const * * quot,char const * * src,zap_i8 id);

void bow_priQuot(void);

[[noreturn]] void bow_cred(void);
[[noreturn]] void bow_help(char const * progNm);

void bow_chkParams(bow_termOpts * opts,int argc,char const * const * argv);

bool bow_compShd(GLuint * refPtr,char const * nm,GLenum typ);

void bow_compShdProg(GLuint * shdProg,char const * nm);

void bow_initGfx(bow_gfxDat * dat);
void bow_initRnd(void);
void bow_initSig(void);

[[noreturn]] void bow_init(int argc,char const * const * argv);
