#ifndef FUNCTION_H
#define FUNCTION_H

namespace oj {
class BigInt {
  char *_val;
 public:
  BigInt(char *s);
  ~BigInt();
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);
  char* to_s();
};
}  // namespace oj

#endif
