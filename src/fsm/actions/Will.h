#pragma once

template <typename... Handlers>
class will : public Handlers...
{
public:
	using Handlers::handle...;
};

