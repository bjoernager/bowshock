// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/logic.hxx>

namespace bow {
	// I chose the default port number (37279) as it's
	// the index number of Proycon in the Hipparcos
	// Catalogue.
	constexpr ::std::uint_least16_t DEFAULT_NETWORK_PORT = UINT16_C(0x919F);
	constexpr ::std::uint_least16_t MINIMUM_NETWORK_PORT = UINT16_C(0x0001);
	constexpr ::std::uint_least16_t MAXIMUM_NETWORK_PORT = UINT16_C(0xFFFF);
}
