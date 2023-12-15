#include "infclass.h"

#include <base/system.h>

static int s_InfclassConfigDomainId{};

int InfclassConfigDomainId()
{
	dbg_assert(s_InfclassConfigDomainId, "InfclassConfigDomainId accessed before initialization");
	return s_InfclassConfigDomainId;
}

void SetInfclassConfigDomainId(int Id)
{
	s_InfclassConfigDomainId = Id;
}
