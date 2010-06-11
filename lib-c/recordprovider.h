// To customize:
// Create, and link a C file implementing these 4 methods
void* rp_initialize(const char* zone);
const char* rp_get_a_record(void* handle, const char* zone);
const char* rp_get_aaaa_record(void* handle, const char* zone);
int rp_shutdown(void* handle);
