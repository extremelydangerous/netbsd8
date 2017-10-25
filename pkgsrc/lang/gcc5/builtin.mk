BUILTIN_PKG:=	gcc5

.include "../../mk/buildlink3/bsd.builtin.mk"

.if !empty(CC_VERSION:Mgcc-5.4.*)
IS_BUILTIN.gcc5=	yes
USE_BUILTIN.gcc5=	yes
.else
IS_BUILTIN.gcc5=	no
USE_BUILTIN.gcc5=	no
.endif

MAKEVARS+=	IS_BUILTIN.gcc5
MAKEVARS+=	USE_BUILTIN.gcc5

.include "../../mk/x11.builtin.mk"
