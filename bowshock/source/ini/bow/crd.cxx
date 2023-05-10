// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <ly/io>
#include <ly/fs>
#include <cstdlib>
#include <stdexcept>

auto ::bow::bow::crd() noexcept -> void {
	char const * const pth = bow_datdir "/CREDITS.txt";

	::zp::siz const filsiz = [&pth]() {
		::ly::pthinf pthinf;
		::ly::sttpth(pthinf,pth);

		return pthinf.siz;
	}();

	::ly::fil fil;
	::ly::err err = fil.opn(pth,::ly::mod::red,::ly::kep);

	if (err != ::ly::err::ok) [[unlikely]] {
		bow_logerr("unable to open credits file");

		::std::exit(EXIT_FAILURE);
	}

	char * crd;

	try {crd = new char[filsiz + 0x3u];}
	catch (::std::bad_alloc const & e) {
		bow_logerr("unable to allocate memory");
		
		::std::exit(EXIT_FAILURE);
	}

	char * const credsrt = crd;

	*crd++ = '\n';

	fil.red(crd,filsiz);
	fil.cls();
	crd += filsiz;

	*crd++ = '\n';
	*crd++ = '\x00';

	crd = credsrt;

	::ly::dflout.wrt(crd,filsiz + 0x3u);

	if (err != ::ly::err::ok) {
		bow_logerr("unable to write to defout");

		::std::exit(EXIT_FAILURE);
	}

	delete[] crd;

	::std::exit(EXIT_SUCCESS);
}
