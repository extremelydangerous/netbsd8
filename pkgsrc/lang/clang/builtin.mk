BUILTIN_PKG:=	clang

.include "../../mk/buildlink3/bsd.builtin.mk"

.if !empty(CC_VERSION:clang-4.0.*)
IS_BUILTIN.clang=	yes
USE_BUILTIN.clang=	yes
.else
IS_BUILTIN.clang=	no
USE_BUILTIN.clang=	no
.endif

MAKEVARS+=	IS_BUILTIN.clang
MAKEVARS+=	USE_BUILTIN.clang

.include "../../mk/x11.builtin.mk"
