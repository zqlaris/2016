#pragma once

#if defined(_MSC_VER) && _MSC_VER < 1700
#define ARKIV_CODE_SEG_ZERO
#else
#define ARKIV_CODE_SEG_ZERO __declspec(code_seg(".zero"))
#endif

namespace RBX{ namespace Security {

    ARKIV_CODE_SEG_ZERO bool patchMain();
}
}

