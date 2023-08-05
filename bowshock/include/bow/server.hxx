// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/logic.hxx>

#include <atomic>
#include <cstdint>
#include <thread>

namespace bow {
	class ServerInstance {
	public:
		explicit ServerInstance(::std::atomic_flag* stop_flag) noexcept;

		static auto run(::bow::ServerInstance* server) noexcept -> void;

	private:
		::std::atomic_flag* stop_flag;

		template<::bow::ObjectLike T>
		auto add_object(::bow::ObjectRoot& root, T const& object) -> void;

		auto delete_objects(::bow::ObjectRoot const& root) noexcept -> void;

		auto generate_system(::bow::ObjectRoot& system, ::std::uint64_t identifier, ::std::uint64_t time) -> void;

		auto gravitate(::bow::ObjectRoot& system)                                   noexcept -> void;
		auto gravitate(::bow::ObjectRoot& objects, ::bow::ObjectRoot const& system) noexcept -> void;

		auto move(::bow::ObjectRoot& root) noexcept -> void;

		auto simulate(::bow::ObjectRoot& system, ::std::uint64_t duration) noexcept -> void;

		auto loop() -> void;
	};

	class Server {
	public:
		static auto start() -> ::bow::Server*;

		~Server() noexcept;

	private:
		::std::thread* thread;

		::bow::ServerInstance* instance;

		::std::atomic_flag* stop_flag;
	};

	auto start_server() -> ::bow::Server;

	auto stop_server(::bow::ServerInstance& server) -> void;
}

template<>
auto bow::ServerInstance::add_object<::bow::Object>(::bow::ObjectRoot& root, ::bow::Object const& object_value) -> void = delete;
