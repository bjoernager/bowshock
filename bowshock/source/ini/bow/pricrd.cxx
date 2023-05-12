// Copyright 2022-2023 Gabriel Jensen.

#include <bow/ini.hxx>

#include <ly/io>
#include <ly/fs>
#include <cstdlib>
#include <stdexcept>

auto ::bow::bow::pricrd() noexcept -> void {
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

	char * pricrd;

	try {pricrd = new char[filsiz + 0x3u];}
	catch (::std::bad_alloc const & e) {
		bow_logerr("unable to allocate memory");
		
		::std::exit(EXIT_FAILURE);
	}

	char * const credsrt = pricrd;

	*pricrd++ = '\n';

	fil.red(pricrd,filsiz);
	fil.cls();
	pricrd += filsiz;

	*pricrd++ = '\n';
	*pricrd++ = '\x00';

	pricrd = credsrt;

	::ly::dflout.wrt(pricrd,filsiz + 0x3u);

	if (err != ::ly::err::ok) {
		bow_logerr("unable to write to defout");

		::std::exit(EXIT_FAILURE);
	}

	delete[] pricrd;

	::std::exit(EXIT_SUCCESS);
}
