#define CPPUT_DUMMY_VAR(...) CPPUT__DUMMY_NAME_##__VA_ARGS__
#define CPPUT_DUMMY_VAR_DECL(A) CPPUT_DUMMY_VAR(A)
#define _ CPPUT_DUMMY_VAR_DECL(__COUNTER__)
