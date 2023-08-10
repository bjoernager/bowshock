// Copyright 2022-2023 Gabriel Bjørnager Jensen.

#pragma once

#include <bow/logic.hxx>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <thread>

namespace bow {
	struct ServerConfiguration final {
		::std::uint_least16_t network_port;
	};

	struct ObjectElement final {
		::bow::Object*        object;
		::bow::ObjectElement* next;
	};

	class ObjectRoot;

	class ObjectIterator final {
	public:
		ObjectIterator(::bow::ObjectRoot const& root) noexcept;

		~ObjectIterator() noexcept = default;

		inline auto operator *()       noexcept -> ::bow::Object&       { return *this->element->object; }
		inline auto operator *() const noexcept -> ::bow::Object const& { return *this->element->object; }

		auto operator ==(::bow::ObjectIterator const& other) const noexcept -> bool;
		auto operator ==(::std::nullptr_t)                   const noexcept -> bool;

		auto operator ++() noexcept -> ::bow::ObjectIterator&;

	private:
		::bow::ObjectElement* element;
	};

	class ObjectRoot final {
	public:
		ObjectRoot() noexcept;

		~ObjectRoot() noexcept;

		auto begin() const noexcept -> ::bow::ObjectIterator;
		auto end()   const noexcept -> ::bow::ObjectIterator;

		inline auto has_objects() const noexcept -> bool { return this->elements != nullptr; }

		template<::bow::ObjectLike T>
		auto add(T const& value) -> T*;

	private:
		friend ::bow::ObjectIterator;

		::bow::ObjectElement* elements;
	};

	class ServerInstance final {
	public:
		explicit ServerInstance(::bow::ServerConfiguration const& configuration, ::std::atomic_flag* stop_flag) noexcept;

		static auto run(::bow::ServerInstance* server) noexcept -> void;

	private:
		::bow::ServerConfiguration configuration;

		::std::atomic_flag* stop_flag;

		auto generate_system(::bow::ObjectRoot& system, ::std::uint64_t identifier, ::std::uint64_t time) -> void;

		auto gravitate(::bow::ObjectRoot& system)                                   noexcept -> void;
		auto gravitate(::bow::ObjectRoot& objects, ::bow::ObjectRoot const& system) noexcept -> void;

		auto move(::bow::ObjectRoot& root) noexcept -> void;

		auto simulate(::bow::ObjectRoot& system, ::std::uint64_t duration) noexcept -> void;

		auto loop() -> void;
	};

	class Server final {
	public:
		static auto start(::bow::ServerConfiguration const& configuration) -> ::bow::Server*;

		~Server() noexcept;

	private:
		Server() noexcept = default;

		::std::thread* thread;

		::bow::ServerInstance* instance;

		::std::atomic_flag* stop_flag;
	};

	auto start_server() -> ::bow::Server;

	auto stop_server(::bow::ServerInstance& server) -> void;
}

template<>
auto bow::ObjectRoot::add<::bow::Object>(::bow::Object const& object_value) -> ::bow::Object* = delete;
