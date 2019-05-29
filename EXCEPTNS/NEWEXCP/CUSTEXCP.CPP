//************************************************************
// Error Handling - New Exception Class
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// Copyright (c) 1997 John Wiley & Sons, Inc. 
// All Rights Reserved.
//************************************************************
#include "custexcp.hpp"

CustomException::CustomException ( const char*   errorText,
                                   unsigned long errorId,
                                   Severity      sev )
         : IException(errorText, errorId, sev)
{ }

CustomException::~CustomException ( )    
{ }

CustomException::CustomException ( const CustomException& excp)
         : IException(excp)
{ }

const char* CustomException::name ( ) const
{ 
   return "CustomException"; 
}
