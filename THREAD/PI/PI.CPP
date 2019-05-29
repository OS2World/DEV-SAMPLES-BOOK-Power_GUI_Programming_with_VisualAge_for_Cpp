/***************************************************************
* FILE NAME: pi.cpp                                            *
*                                                              *
* DESCRIPTION:                                                 *
*   This file contains the implementation of                   *
*   classes/functions declared in pi.hpp.                      *
*                                                              *
* COPYRIGHT:                                                   *
*   Licensed Materials - Property of Solution Frameworks       *
*   Copyright (C) 1996, Solution Frameworks                    *
*   All Rights Reserved                                        *
***************************************************************/
#include "pi.hpp"

#ifndef _ISTRING_
  #include <istring.hpp>
#endif

/*-------------------------- Number ----------------------------
| Objects of this class basically represent integers with      |
| arbitrary numbers of digits.  Note that only a limited set   |
| of operations are guaranteed to work (but that set includes  |
| all we need in this program).                                |
--------------------------------------------------------------*/
class Number {
public:
Number ( unsigned int numDigits ) {
  // All Numbers == "1.00000000..." initially.
  value = IString::leftJustify( "1", numDigits, '0' );
}
Number ( const Number &source ) {
  // Force copy of source value.
  this->value = IString( (char*)source.value, 
                         source.value.length() );
}

/*------------------------ Operators -------------------------*/
IString asString ( ) const {
  // Insert decimal point and drop last digit (since it 
  // probably isn't right, anyway).
  return IString( (char*)value, 1, 
                  ".", 1,
                  (char*)value+1, value.length()-1 );
}

Number &operator= ( const Number &rhs ) {
  // Force copy of rhs value.
  this->value = IString( (char*)rhs.value, rhs.value.length() );
  return *this;
}

operator const void* () const {
  // Return 0 iff all digits are zero.
  const char
   *p = value;
  int
    limit = value.length();
  for( int i = 0; i < limit; i++ )
    if ( p[i] != '0' )
      return p+i;
  return 0;
}

Number &operator+= ( const Number &rhs ) {
  // Add each element of rhs to *this.
  char
   *result = value,
   *addend = rhs.value;
  char
    carry = 0;
  for( int i = value.length()-1; i >= 0; i-- ) {
    // If rhs is too short, effectively pad with zeros.
    if ( i >= rhs.value.length() )
      continue;
    // Next digit is sum of result, addend, and carry.
    int
      digit = (result[i]-'0') + (addend[i]-'0') + carry;
    // Calculate new carry and result digit.
    carry = (char)( digit / 10 );
    digit = digit % 10;
    // Store result digit.
    result[i] = (char)( digit + '0' );
  }
  return *this;
}

Number &operator-= ( const Number &rhs ) {
  // Subtract each element of rhs from *this.
  char
   *result = value,
   *delta  = rhs.value;
  char
    borrow = 0;
  for( int i = value.length()-1; i >= 0; i-- ) {
    // If rhs is too short, effectively pad with zeros.
    if ( i >= rhs.value.length() )
      continue;
    // Next digit is result digit - borrow - delta digit.
    int
      digit = (result[i]-'0') - borrow - (delta[i] - '0');
    // Calculate new borrow and result digit.
    borrow = (char)( digit < 0 );
    digit += 10 * borrow;
    // Store result digit.
    result[i] = (char)( digit + '0' );
  }
  return *this;
}

Number &operator*= ( int factor ) {
  // Multiply each element of *this by factor.
  int
    carry = 0;
  char
   *result = value;
  for( int i = value.length()-1; i >= 0; i-- ) {
    int
      digit = (result[i] - '0') * factor + carry;
    // Calculate new carry and digit.
    carry = digit / 10;
    digit = digit % 10;
    // Store result digit.
    result[i] = (char)( digit + '0' );
  }
  return *this;
}

Number &operator/= ( int divisor ) {
  // Divide each element of *this by divisor.
  int
    remainder = 0;
  char
   *result = value;
  int
    limit = value.length();
  for( int i = 0; i < limit; i++ ) {
    // Get next digit and add in remainder from 
    // previous digit calculation.
    int
      digit = (result[i] - '0') + 10 * remainder;
    // Calculate digit and remainder.
    remainder = digit % divisor;
    digit = digit / divisor;
    // Store result digit.
    result[i] = (char)( digit + '0' );
  }
  return *this;
}

private:
IString
  value;
}; // class Number

/*------------------- arcTangentOfOneOverX ---------------------
| This function returns a Number with value equal to the       |
| arc tangent of 1/x.  The result is valid to numDigits        |
| decimal places (maybe off in the last few digits, though).   |
|                                                              |                
| The result is calculated by using the power series           |
| expansion for arc tangent:                                   |                                 
|   arctan(x) = x - pow(x,3)/3 + pow(x,5)/5 - pow(x,7)/7 ...   |                
--------------------------------------------------------------*/
static Number arcTangentOfOneOverX( int x, int numDigits ) {
  Number
   sum( numDigits + 1 ); // "1.00000...."
  sum /= x;              // "1/x"

  Number
    oneOverXToTheK = sum;

  /* Continue until delta won't change sum. */
  for ( int k = 1; oneOverXToTheK; k++ ) {
    /* Calculate next term in series. */
    oneOverXToTheK /= x*x;

    Number
      delta = oneOverXToTheK;
    delta /= k + k + 1; // 3, 5, 7, ...
 
    /* Adjust sum. */
    if ( k%2 ) {
      // Subtract odd terms.
      sum -= delta;
    } else {
      // Add even terms.
      sum += delta;
    }
  }
  return sum;
}

/*---------------------------- pi ------------------------------
| Calculate pi to the requested number of decimal places.      |
|                                                              |
| We use Machin's formula:                                     |
|   pi/4 == 4 * arctan( 1/5 ) - arctan( 1/239 )                |
--------------------------------------------------------------*/
IString pi( unsigned digits ) {
  Number
    pi = arcTangentOfOneOverX( 5, digits );
  pi *= 4;
  pi -= arcTangentOfOneOverX( 239, digits );
  pi *= 4;

  return pi.asString();
}
