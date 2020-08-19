#include "params.h"
#include "reduce.h"
#include "ntt.h"
#include "poly.h"

/* Roots of unity in order needed by forward ntt */

/* Roots of unity in order needed by inverse ntt */



static const uint32_t zetas[N] = { 4104, 45242, 311997, 223193, 61121, 408733, 57840, 39307, 245523, 60060, 501940, 345637, 117446, 408841, 325602, 155149, 508941, 520903, 382026, 234570, 154077, 686, 187651, 444824, 31453, 284504, 244208, 382135, 236703, 469719, 469496, 214233, 349786, 345959, 276413, 390845, 494231, 190428, 375424, 156751, 414800, 281166, 116021, 60816, 20909, 429328, 399493, 218395, 374161, 509904, 319755, 105508, 427178, 23723, 123784, 449751, 184448, 122015, 86058, 425073, 109790, 386034, 319531, 455120, 230263, 45524, 312784, 351077, 62405, 88276, 38334, 347761, 258839, 40892, 177271, 445920, 63603, 481941, 392163, 229261, 375502, 203368, 448684, 185347, 201601, 240501, 297855, 353057, 149019, 281577, 154, 414363, 234520, 313321, 426785, 10443, 336036, 387779, 426556, 377212, 250022, 230746, 235341, 219782, 383580, 35189, 267225, 177662, 494548, 359739, 162566, 98288, 243795, 437483, 219799, 439613, 253450, 305267, 129418, 392237, 412604, 378887, 379452, 267540, 499284, 450471, 237472, 345102, 258648, 67757, 1501, 191994, 41050, 37043, 149813, 71175, 138538, 712, 484902, 356317, 359856, 361043, 485672, 333024, 13045, 282209, 53924, 277489, 259686, 486669, 416502, 411981, 79140, 279267, 383754, 380924, 391165, 196870, 51647, 24621, 232669, 274763, 100009, 322074, 404090, 367070, 151450, 425031, 429625, 217030, 275072, 173604, 397537, 16357, 77224, 463750, 28889, 283160, 229313, 162692, 375458, 459105, 517884, 3448, 235488, 448654, 475716, 345782, 438044, 31053, 81090, 397138, 450914, 389980, 267393, 439230, 226611, 320615, 294837, 442993, 279486, 112182, 179345, 33542, 154172, 198480, 85858, 63799, 385450, 427572, 468887, 313603, 364342, 262071, 1438, 93906, 275219, 402476, 462000, 166179, 127489, 307062, 244012, 426157, 361052, 28283, 80789, 277680, 17336, 328583, 495381, 434534, 1931, 287823, 296190, 304791, 307536, 236380, 61613, 501326, 192308, 387615, 485534, 492291, 349573, 238804, 135243, 307858, 126949, 64910, 188579, 193636, 373557, 68340, 79280, 322648 };

static const uint32_t zetas_inv[N] = { 201129, 444497, 455437, 150220, 330141, 335198, 458867, 396828, 215919, 388534, 284973, 174204, 31486, 38243, 136162, 331469, 22451, 462164, 287397, 216241, 218986, 227587, 235954, 521846, 89243, 28396, 195194, 506441, 246097, 442988, 495494, 162725, 97620, 279765, 216715, 396288, 357598, 61777, 121301, 248558, 429871, 522339, 261706, 159435, 210174, 54890, 96205, 138327, 459978, 437919, 325297, 369605, 490235, 344432, 411595, 244291, 80784, 228940, 203162, 297166, 84547, 256384, 133797, 72863, 126639, 442687, 492724, 85733, 177995, 48061, 75123, 288289, 520329, 5893, 64672, 148319, 361085, 294464, 240617, 494888, 60027, 446553, 507420, 126240, 350173, 248705, 306747, 94152, 98746, 372327, 156707, 119687, 201703, 423768, 249014, 291108, 499156, 472130, 326907, 132612, 142853, 140023, 244510, 444637, 111796, 107275, 37108, 264091, 246288, 469853, 241568, 510732, 190753, 38105, 162734, 163921, 167460, 38875, 523065, 385239, 452602, 373964, 486734, 482727, 331783, 522276, 456020, 265129, 178675, 286305, 73306, 24493, 256237, 144325, 144890, 111173, 131540, 394359, 218510, 270327, 84164, 303978, 86294, 279982, 425489, 361211, 164038, 29229, 346115, 256552, 488588, 140197, 303995, 288436, 293031, 273755, 146565, 97221, 135998, 187741, 513334, 96992, 210456, 289257, 109414, 523623, 242200, 374758, 170720, 225922, 283276, 322176, 338430, 75093, 320409, 148275, 294516, 131614, 41836, 460174, 77857, 346506, 482885, 264938, 176016, 485443, 435501, 461372, 172700, 210993, 478253, 293514, 68657, 204246, 137743, 413987, 98704, 437719, 401762, 339329, 74026, 399993, 500054, 96599, 418269, 204022, 13873, 149616, 305382, 124284, 94449, 502868, 462961, 407756, 242611, 108977, 367026, 148353, 333349, 29546, 132932, 247364, 177818, 173991, 309544, 54281, 54058, 287074, 141642, 279569, 239273, 492324, 78953, 336126, 523091, 369700, 289207, 141751, 2874, 14836, 368628, 198175, 114936, 406331, 178140, 21837, 463717, 278254, 484470, 465937, 115044, 462656, 300584, 211780, 478535, 0};

/*************************************************
* Name:        ntt
* 
* Description: Forward NTT, in-place. No modular reduction is performed after
*              additions or subtractions. Hence output coefficients can be up
*              to 16*Q larger than the coefficients of the input polynomial.
*              Output vector is in bitreversed order.
*
* Arguments:   - uint32_t *p: pointer to polynomial to be transformed
**************************************************/
void ntt(uint32_t *p) {
  unsigned int len, start, j, k;
  uint32_t zeta, t;

  k = 1;
  for(len = 128; len > 0; len >>= 1) {
    for(start = 0; start < N; start = j + len) {
      zeta = zetas[k++];
      for(j = start; j < start + len; ++j) {
        t = montgomery_reduce((uint64_t)zeta * p[j + len]);
        p[j + len] = p[j] + 2*Q - t;
        p[j] = p[j] + t;
      }
    }
  }
}

/*************************************************
* Name:        invntt_frominvmont
* 
* Description: Inverse NTT, in-place. No modular reductions after additions or
*              subtractions. Output coefficients can be up to 256*Q larger than
*              input coefficients. Multiplies with Montgomery factor 2^32.
*
* Arguments:   - uint32_t *p: pointer to vector to be transformed
**************************************************/
void invntt_frominvmont(uint32_t *p) {
  unsigned int start, len, j, k;
  uint32_t t, zeta;
  const uint32_t f = (((uint64_t)MONT*MONT % Q) * (Q-1) % Q) * ((Q-1) >> 8) % Q;

  k = 0;
  for(len = 1; len < N; len <<= 1) {
    for(start = 0; start < N; start = j + len) {
      zeta = zetas_inv[k++];
      for(j = start; j < start + len; ++j) {
        t = p[j];
        p[j] = t + p[j + len];
        p[j + len] = t + 256*Q - p[j + len];
        p[j + len] = montgomery_reduce((uint64_t)zeta * p[j + len]);
      }
    }
  }

  for(j = 0; j < N; ++j) {
    p[j] = montgomery_reduce((uint64_t)f * p[j]);
  }
}
