#pragma once

#include <cstdint>
#include <iosfwd>
#include "IO/Commands/Command.hpp"

namespace sw::io {
	struct CreateMap : public Command {
		constexpr static const char* Name = "CREATE_MAP";

		uint32_t width{};
		uint32_t height{};

		void execute(const std::shared_ptr<game::Controller>& controller) override;

		template <typename Visitor>
		void visit(Visitor& visitor)
		{
			visitor.visit("width", width);
			visitor.visit("height", height);
		}
	};
}
