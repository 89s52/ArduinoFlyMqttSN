/*
   The MIT License (MIT)

   Copyright (C) 2017 Hong-She Liang <starofrainnight@gmail.com>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 */

#include "FMSNUtils.h"

FMSNMsgType
fmsnGetRespondType(FMSNMsgType requestType)
{
  // Mqtt-SN message have a request-respond pattern, respond message types are
  // numbers followed after request message types except types list below:
  //
  // FMSNMT_ADVERTISE, FMSNMT_DISCONNECT
  if((FMSNMT_ADVERTISE == requestType) || (FMSNMT_DISCONNECT == requestType))
  {
    return requestType;
  }

  return static_cast<FMSNMsgType>(((requestType) + 1));
}

bool
fmsnIsHighQos(uint8_t qos)
{
  return (qos == FMSN_FLAG_QOS_1) || (qos == FMSN_FLAG_QOS_2);
}
