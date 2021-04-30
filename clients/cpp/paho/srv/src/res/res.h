#ifndef hfc524db4a98b11eb8bdb6fcf0ba184bf
#define hfc524db4a98b11eb8bdb6fcf0ba184bf
#if !defined(_WIN32)||defined(LEADING_UNDERSCORES)
#define RSRPFX(a) extern char _##a[];extern const char*a
#else
#define RSRPFX(a) extern char a[]
#endif
#ifdef __cplusplus
extern "C"{
#endif
RSRPFX(binary_src_res_version_json_size);
RSRPFX(binary_src_res_version_json_start);
RSRPFX(binary_src_res_version_json_end);
#endif
#ifdef __cplusplus
}
#endif
