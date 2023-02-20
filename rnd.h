#pragma once
#include <cassert>
#include <random>
// ... don't worry how this all works
// ... member functions that you may want to use:
//       random01() returns a random double between 0 and 1
//       randomInt(max) returns a random int between 0 and max-1 (inclusive)

class rnd {
private:
  // nuts and bolts.. should not need to touch this.
  std::default_random_engine generator;
  int genMax;
  std::uniform_int_distribution<unsigned char> intmax;
  std::uniform_real_distribution<double> real01;
  std::vector<unsigned char> intCache;
  const std::size_t cacheThis = 10000000;
  unsigned long count = 0;

public:
  // constructor
  rnd() {
    genMax = 255;
    // cout << "genMax is " << generator.max() << endl;
    intmax = std::uniform_int_distribution<unsigned char>(0, 255);
    real01 = std::uniform_real_distribution<double>(0.0, 1.0);
    intCache.resize(cacheThis);
    count = cacheThis;
  }

  // set the random seed
  void setSeed(int seed) { generator.seed(seed); }
  // member functions for generating random double in [0,1] and random integer
  // in [0,max-1]
  double random01() {
    // ~5k
    //++count;
    return real01(generator);
  }
  int randomInt(int max) {
    assert(max < genMax);
    // assert(intCache.size()) == cacheThis);
    if (count == cacheThis) {
      for (auto &el : intCache) {
        el = intmax(generator);
      }
      count = 0;
    }

    const auto ret = intCache.at(count);
    ++count;
    // return intmax(generator) % max;
    return ret % max;
  }
};
