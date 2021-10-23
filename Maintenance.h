#pragma once

#include "State.h"

class Maintenance final : public State
{
public:
	explicit Maintenance(): State(_comsToPtrs) {}
	Maintenance(const Maintenance& other) = delete;
	Maintenance& operator=(const Maintenance& other) = delete;
	~Maintenance() override {}

	void test(utils::Args) {}

private:
	static std::unordered_map<std::string, State::CommandPtr> _comsToPtrs;
};
