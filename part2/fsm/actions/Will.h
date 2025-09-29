#pragma once

template <typename... Handlers>
class will : Handlers...
{
public:
	using Handlers::handle...;
};

