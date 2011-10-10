#include <new>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

static int bytes = 0;

struct alloc_frame {
    char    *result;
    size_t   size;
    void    *dummy; // Force alignment
};
    

void *operator new(size_t n)
{
    void *vp = malloc(n + sizeof(alloc_frame));
    alloc_frame *p = static_cast<alloc_frame *>(vp);
    if (p == NULL) {
	bad_alloc e;
	throw e;
    }
    p->size = n;
    p->result = static_cast<char *>(vp) + sizeof(alloc_frame);
    bytes += n;
    return p->result;
}

void operator delete(void *p)
{
    if (!p) return;
    void *rp = static_cast<char *>(p) - sizeof(alloc_frame);
    alloc_frame *af = static_cast<alloc_frame *>(rp);
    if (af->result != p) {
	cerr << "Delete called on bad pointer/corrupted block\n";
	assert(0);
    }
    af->result = 0;
    bytes -= af->size;
    free(af);
}

int bytes_allocated()
{
    return bytes;
}
