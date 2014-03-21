#include <flint/fmpz_mat.h>
#include <flint/fmpz.h>

void strassenMultiply(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B, fmpz size);
void commonMultiply(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B);
void copyElements(fmpz_mat_t dest, const fmpz_mat_t source, fmpz a, fmpz b, fmpz c, fmpz d, fmpz length);
