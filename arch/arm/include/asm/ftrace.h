//arch/arm/include/asm/ftrace.h
#ifndef _ASM_ARM_FTRACE
#define _ASM_ARM_FTRACE

#ifdef CONFIG_FUNCTION_TRACER
#define MCOUNT_ADDR		((unsigned long)(__gnu_mcount_nc))
#define MCOUNT_INSN_SIZE	4 /* sizeof mcount call */

#ifndef __ASSEMBLY__
extern void mcount(void);
extern void __gnu_mcount_nc(void);

#ifdef CONFIG_DYNAMIC_FTRACE
struct dyn_arch_ftrace {
#ifdef CONFIG_OLD_MCOUNT
	bool	old_mcount;
#endif
};

static inline unsigned long ftrace_call_adjust(unsigned long addr)
{
	/* With Thumb-2, the recorded addresses have the lsb set */
	return addr & ~1;
}

extern void ftrace_caller_old(void);
extern void ftrace_call_old(void);
#endif

#endif

#endif

#ifndef __ASSEMBLY__

#if defined(CONFIG_FRAME_POINTER) && !defined(CONFIG_ARM_UNWIND)
/*
 * return_address uses walk_stackframe to do it's work.  If both
 * CONFIG_FRAME_POINTER=y and CONFIG_ARM_UNWIND=y walk_stackframe uses unwind
 * information.  For this to work in the function tracer many functions would
 * have to be marked with __notrace.  So for now just depend on
 * !CONFIG_ARM_UNWIND.
 */

void *return_address(unsigned int);

#else

static inline void *return_address(unsigned int level)
{
	return NULL;
}

#endif

#define HAVE_ARCH_CALLER_ADDR

#define CALLER_ADDR0 ((unsigned long)__builtin_return_address(0))
#define CALLER_ADDR1 ((unsigned long)return_address(1))
#define CALLER_ADDR2 ((unsigned long)return_address(2))
#define CALLER_ADDR3 ((unsigned long)return_address(3))
#define CALLER_ADDR4 ((unsigned long)return_address(4))
#define CALLER_ADDR5 ((unsigned long)return_address(5))
#define CALLER_ADDR6 ((unsigned long)return_address(6))

#endif /* ifndef __ASSEMBLY__ */

#endif /* _ASM_ARM_FTRACE */
