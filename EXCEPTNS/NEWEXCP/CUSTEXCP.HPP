#ifndef _CUSTEXCP_
#define _CUSTEXCP_
//************************************************************
// Error Handling - New Exception Class
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include <iexcbase.hpp>
#include <ibase.hpp>

class CustomException : public IException
{
public:

  CustomException ( const char*   errorText,
                    unsigned long errorId = 0,
                    Severity      sev = unrecoverable );

virtual
 ~CustomException ( );

  CustomException ( const CustomException& excp);

virtual const char
 *name ( ) const;

private:
operator = ( const CustomException& );
};
#endif // _CUSTEXCP_
