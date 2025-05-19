#pragma once

#include <cstdint>
#include <iosfwd>
#include "IO/Commands/Command.hpp"

namespace sw::io {
	struct March : public Command {
		constexpr static const char* Name = "MARCH";

		uint32_t unitId{};
		uint32_t targetX{};
		uint32_t targetY{};

		void execute(const std::shared_ptr<game::Controller>& controller) override;

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("unitId", unitId);
			visitor.visit("targetX", targetX);
			visitor.visit("targetY", targetY);
		}
	};
}
