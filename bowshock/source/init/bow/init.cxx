// Copyright 2022-2023 Gabriel Jensen.

#include <bow/init.hxx>
#include <bow/lgc.hxx>
#include <bow/run.hxx>
#include <bow/sav.hxx>

#include <cinttypes>

void ::bow::bow::init(int const argc,char const * const * const argv) noexcept {
	::bow::termOpts opts;
	chkParams(opts,argc,argv);
	
	priQuot();
	
	bow_logRaw("\x1B[0m\x1B[1mBowshock\x1B[0m %" PRIX64 ".%" PRIX64 ".%" PRIX64 " \u2013 Copyright 2022\u20102023 \x1B[1mGabriel Jensen\x1B[0m.\n\n",::bow::verMaj,::bow::verMin,::bow::verPat);
	
	bow_log("initialising");
	
	bow_logDbg("debug mode is enabled");
	bow_logDbg("data directory at \"" bow_datDir "\"");
	bow_logDbg("angle unit:             %.3f radians",0x1p0f);
	bow_logDbg("distance unit:          %.3f metres",::bow::distMod);
	bow_logDbg("mass unit:              %.3f kilograms",::bow::massMod);
	bow_logDbg("time unit:              %.3f seconds",::bow::tmMod);
	bow_logDbg("gravitational constant: %f (factor: %f))",::bow::gravConst,::bow::gravConstFac);

	initRnd();
	initSig();
	initGfx();
	
	if (opts.skip || !intro()) [[likely]] {
		if (!opts.hasSavPth) {opts.savPth = getSavPth();}

		if (opts.newSav) ::bow::newSav(plDat);
		else             ::bow::cont(plDat,opts.savPth);

		loop();

		::bow::sav(opts.savPth,plDat);

		if (!opts.hasSavPth) delete[] const_cast<char *>(opts.savPth);
	}
}
