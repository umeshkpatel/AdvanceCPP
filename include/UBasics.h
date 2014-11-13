#ifndef _UBASICS_H_
#define _UBASICS_H_

namespace utl {
/*! Swap(S& in_a, S& in_b)
 * Basic Swap Operation for template types
 * @param in_a: 1st Argument for swapping
 * @param in_b: 2st Argument for swapping
 * @return (void)
 */
template<typename S>
void Swap(S& in_a, S& in_b) {
  in_a ^= in_b;
  in_b = in_a^in_b;
  in_a ^= in_b;
}

/*! Swap(S*& in_a, S*& in_b)
 * Pointer Swap Operation for template types
 * @param in_a: 1st Argument for swapping
 * @param in_b: 2st Argument for swapping
 * @return (void)
 */
template<typename S>
void Swap(S*& in_a, S*& in_b) {
  S* t_s = in_a;
  in_a = in_b;
  in_b = t_s;
}
} // utl
#endif // _UBASICS_H_
