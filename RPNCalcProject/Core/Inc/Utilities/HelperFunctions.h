#ifndef _HELPER_FUNCTIONS_
#define _HELPER_FUNCTIONS_

#define SET_BIT(word, bit_to_set)     (word |=  (1 << bit_to_set))
#define CLEAR_BIT(word, bit_to_clear) (word &= ~(1 << bit_to_clear))

#endif /* _HELPER_FUNCTIONS_ */
