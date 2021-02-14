#ifndef SRC_LOG_DEBUG_PPH_
#define SRC_LOG_DEBUG_PPH_

#include "TipoLog.hpp"

class Debug : public TipoLog{
	public:
		Debug()= default;
		~Debug() override= default;

	//Hace todas las opciones, no sobreescribe ninguna
};


#endif /* SRC_LOG_DEBUG_PPH_ */