//
// GKPearsonHash.h
//
// Pearson hashing in C++
// Based on an example from http://en.wikipedia.org/wiki/Pearson_hashing
//
// Copyright 2014 Greg M. Krsak (greg.krsak@gmail.com)
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef GKPearsonHash_h
#define GKPearsonHash_h

//#include <Ardunio.h>

namespace GK {
  uint8_t pearsonLookupTable[256] = {
    98, 6, 85, 150, 36, 23, 112, 164, 135, 207, 169, 5, 26, 64, 165, 219,
    61, 20, 68, 89, 130, 63, 52, 102, 24, 229, 132, 245, 80, 216, 195, 115,
    90, 168, 156, 203, 177, 120, 2, 190, 188, 7, 100, 185, 174, 243, 162, 10,
    237, 18, 253, 225, 8, 208, 172, 244, 255, 126, 101, 79, 145, 235, 228, 121,
    123, 251, 67, 250, 161, 0, 107, 97, 241, 111, 181, 82, 249, 33, 69, 55,
    59, 153, 29, 9, 213, 167, 84, 93, 30, 46, 94, 75, 151, 114, 73, 222,
    197, 96, 210, 45, 16, 227, 248, 202, 51, 152, 252, 125, 81, 206, 215, 186,
    39, 158, 178, 187, 131, 136, 1, 49, 50, 17, 141, 91, 47, 129, 60, 99,
    154, 35, 86, 171, 105, 34, 38, 200, 147, 58, 77, 118, 173, 246, 76, 254,
    133, 232, 196, 144, 98, 124, 53, 4, 108, 74, 223, 234, 134, 230, 157, 139,
    189, 205, 199, 128, 176, 19, 211, 236, 127, 192, 231, 70, 233, 88, 146, 44,
    183, 201, 22, 83, 13, 214, 116, 109, 159, 32, 95, 226, 140, 220, 57, 12,
    221, 31, 209, 182, 143, 92, 149, 184, 148, 62, 113, 65, 37, 27, 106, 166,
    3, 14, 204, 72, 21, 41, 56, 66, 28, 193, 40, 217, 25, 54, 179, 117,
    238, 87, 240, 155, 180, 170, 242, 212, 191, 163, 78, 218, 137, 194, 175, 110,
    43, 119, 224, 71, 122, 142, 42, 160, 104, 48, 247, 103, 15, 11, 138, 239
  };

  
  uint8_t pearsonHash(String message, uint8_t* lookupTable) {
    uint8_t result = 0;
    for (uint8_t byte : message) {
      result = lookupTable[result ^ byte];
    }
    return result;
  }
  uint8_t pearsonHash(byte message[], uint8_t* lookupTable) {
    uint8_t result = 0;
    for (int i = 0; i < sizeof(message); i++) {
      result = lookupTable[result ^ message[i]];
    }
    return result;
  }
  
  
  uint64_t pearsonHash64(String message) {
    uint64_t result = 0;
    uint8_t correctedFirstMessageByte = message[0];
    for (int iteration = 0; iteration < 8; ++iteration) {
      uint8_t iterationResult = GK::pearsonHash(message, GK::pearsonLookupTable);
      result += (iterationResult << (iteration << 3));
      message[0] += 1;
    }
    message[0] = correctedFirstMessageByte;
    return result;
  }

  uint64_t pearsonHash64(byte message[]) {
    uint64_t result = 0;
    uint8_t correctedFirstMessageByte = message[0];
    for (int iteration = 0; iteration < 8; ++iteration) {
      uint8_t iterationResult = GK::pearsonHash(message, GK::pearsonLookupTable);
      result += (iterationResult << (iteration << 3));
      message[0] += 1;
    }
    message[0] = correctedFirstMessageByte;
    return result;
  }
} // namespace GK

#endif
