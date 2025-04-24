#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>

// A dummy function so that loop_callback, which gets eliminated, is not the
// first subprogram; the repro does not work if it is.
__attribute__((noinline))
__attribute__((optnone))
static int dummy(u32 i)
{
	return i+42;
}

static int loop_callback(__u32 index, u32 *key)
{
	return 1;
}

SEC("tracepoint")
int entrypoint(__attribute__((unused)) void* ctx) {
	u32 key = dummy(0);
	bpf_loop(0, loop_callback, &key, 0);
	return 0;
}
