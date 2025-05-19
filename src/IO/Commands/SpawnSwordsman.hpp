#pragma once

#include <cstdint>
#include <iosfwd>
#include "IO/Commands/Command.hpp"

namespace sw::io {
	struct SpawnSwordsman : public Command {
		constexpr static const char* Name = "SPAWN_SWORDSMAN";

		uint32_t unitId{};
		uint32_t x{};
		uint32_t y{};
		uint32_t hp{};
		uint32_t strength{};

		void execute(const std::shared_ptr<game::Controller>& controller) override;

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("x", x);
			visitor.visit("y", y);
			visitor.visit("hp", hp);
			visitor.visit("strength", strength);
		}
	};
}
