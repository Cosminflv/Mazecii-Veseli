#include "Routing.h"

void Routing::Run(GameStorage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "Meow";
		});
	m_app.port(18080).multithreaded().run();
}
