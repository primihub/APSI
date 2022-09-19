// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

// #pragma once
#ifndef COMMON_APSI_OPRF_ECPOINT_H__
#define COMMON_APSI_OPRF_ECPOINT_H__
// STD
#include <array>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <memory>

// GSL
#include "gsl/span"

// FourQ
#include "apsi/fourq/FourQ.h"
// FourQ
#include "apsi/fourq/FourQ_api.h"
#include "apsi/fourq/FourQ_internal.h"
#include "apsi/fourq/random.h"

// SEAL
#include "seal/randomgen.h"
#include "seal/util/blake2.h"

using namespace std;
using namespace seal;

namespace apsi {
    namespace oprf {


        class ECPoint {
        public:
            static constexpr std::size_t save_size = sizeof(f2elm_t);
            static constexpr std::size_t point_size = sizeof(point_t);
            static constexpr std::size_t order_size = sizeof(digit_t) * NWORDS_ORDER;

            using scalar_type = std::array<unsigned char, order_size>;
            using scalar_const_type = const scalar_type;

            using scalar_span_type = gsl::span<unsigned char, order_size>;
            using scalar_span_const_type = gsl::span<const unsigned char, order_size>;

            using input_span_const_type = gsl::span<const unsigned char>;

            using point_save_span_type = gsl::span<unsigned char, save_size>;
            using point_save_span_const_type = gsl::span<const unsigned char, save_size>;

            // Output hash size is 32 bytes: 16 for item hash and 16 for label encryption key
            static constexpr std::size_t hash_size = 32;

            using hash_span_type = gsl::span<unsigned char, hash_size>;

            // Initializes the ECPoint with the neutral element
            ECPoint() = default;

            ECPoint &operator=(const ECPoint &assign);

            ECPoint(const ECPoint &copy)
            {
                operator=(copy);
            }

            // This function applies Blake2b on value and hashes the output to
            // a uniformly random elliptic curve point.
            ECPoint(input_span_const_type value);

            // Creates a random non-zero number modulo the prime order subgroup
            // order and computes its inverse.
            // static void MakeRandomNonzeroScalar(scalar_span_type out) {
                 
            //     // Loop until we find a non-zero element
            //     do {
            //         random_scalar(out);
            //     } while (!is_nonzero_scalar(out));
        
            // }


            static void InvertScalar(scalar_span_const_type in, scalar_span_type out);

            bool scalar_multiply(scalar_span_const_type scalar, bool clear_cofactor);

            void save(std::ostream &stream) const;

            void load(std::istream &stream);

            void save(point_save_span_type out) const;

            void load(point_save_span_const_type in);

            void extract_hash(hash_span_type out) const;

        private:
            // Initialize to neutral element
            point_t pt_ = { { { { 0 } }, { { 1 } } } }; // { {.x = { 0 }, .y = { 1 } }};
        };        
        
                                              // class ECPoint
        // namespace {
            // void random_scalar(ECPoint::scalar_span_type value);
           
            // digit_t is_nonzero_scalar(ECPoint::scalar_span_type value);
        // }

        static   void random_scalar(ECPoint::scalar_span_type value)
            {
                random_bytes(value.data(), seal::util::safe_cast<unsigned int>(value.size()));
                modulo_order(
                    reinterpret_cast<digit_t *>(value.data()),
                    reinterpret_cast<digit_t *>(value.data()));
            }

          static  digit_t is_nonzero_scalar(ECPoint::scalar_span_type value)
            {
                const digit_t *value_ptr = reinterpret_cast<digit_t *>(value.data());
                digit_t c = 0;

                for (size_t i = 0; i < NWORDS_ORDER; i++) {
                    c |= value_ptr[i];
                }

                sdigit_t first_nz = -static_cast<sdigit_t>(c & 1);
                sdigit_t rest_nz = -static_cast<sdigit_t>(c >> 1);
                return static_cast<digit_t>((first_nz | rest_nz) >> (8 * sizeof(digit_t) - 1));
            }


        // Creates a random non-zero number modulo the prime order subgroup
        // order and computes its inverse.
        static void MakeRandomNonzeroScalar(ECPoint::scalar_span_type out) {
                 
            // Loop until we find a non-zero element
            do {
                    random_scalar(out);
                } while (!is_nonzero_scalar(out));
        
            }
    }                                                   // namespace oprf
} // namespace apsi

#endif  // COMMON_APSI_OPRF_ECPOINT_H__
