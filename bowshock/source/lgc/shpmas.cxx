// Copyright 2022-2023 Gabriel Jensen.

#include <bow/lgc.hxx>

auto ::bow::shpmas([[maybe_unused]] ::bow::shp const id) noexcept -> double {
	double mas = 0x100p0;
	mas /= ::bow::masmod;
	
	return mas;
}
