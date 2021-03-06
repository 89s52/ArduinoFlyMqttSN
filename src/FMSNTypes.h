﻿/*
   The MIT License (MIT)

   Copyright (C) 2014 John Donovan
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

#ifndef __INCLUDED_FDCE12F8526A11E7AA6EA088B4D1658C
#define __INCLUDED_FDCE12F8526A11E7AA6EA088B4D1658C

#include <Arduino.h>

#define FMSN_PROTOCOL_ID 0x01

#define FMSN_FLAG_DUP                 0x80
#define FMSN_FLAG_QOS_0               0x00
#define FMSN_FLAG_QOS_1               0x20
#define FMSN_FLAG_QOS_2               0x40
#define FMSN_FLAG_QOS_M1              0x60
#define FMSN_FLAG_RETAIN              0x10
#define FMSN_FLAG_WILL                0x08
#define FMSN_FLAG_CLEAN               0x04
#define FMSN_FLAG_TOPIC_NAME          0x00
#define FMSN_FLAG_TOPIC_PREDEFINED_ID 0x01
#define FMSN_FLAG_TOPIC_SHORT_NAME    0x02

#define FMSN_QOS_MASK   (FMSN_FLAG_QOS_0 | FMSN_FLAG_QOS_1 | FMSN_FLAG_QOS_2 | \
                         FMSN_FLAG_QOS_M1)
#define FMSN_TOPIC_MASK (FMSN_FLAG_TOPIC_NAME | FMSN_FLAG_TOPIC_PREDEFINED_ID | \
                         FMSN_FLAG_TOPIC_SHORT_NAME)

// Recommended values for timers and counters. All timers are in seconds.
#define FMSN_T_ADV       960
#define FMSN_N_ADV       3
#define FMSN_T_SEARCH_GW 5
#define FMSN_T_GW_INFO   5
#define FMSN_T_WAIT      360
#define FMSN_T_RETRY     15
#define FMSN_N_RETRY     5

#define FMSN_INVALID_TOPIC_ID 0xFFFF

#define FMSN_STRUCT_PACKED __attribute__ ((__packed__))

enum FMSNReturnCode
{
  FMSNRC_ACCEPTED,
  FMSNRC_REJECTED_CONGESTION,
  FMSNRC_REJECTED_INVALID_TOPIC_ID,
  FMSNRC_REJECTED_NOT_SUPPORTED
};

enum FMSNMsgType
{
  FMSNMT_ADVERTISE,
  FMSNMT_SEARCHGW,
  FMSNMT_GWINFO,
  FMSNMT_CONNECT = 0x04,
  FMSNMT_CONNACK,
  FMSNMT_WILLTOPICREQ,
  FMSNMT_WILLTOPIC,
  FMSNMT_WILLMSGREQ,
  FMSNMT_WILLMSG,
  FMSNMT_REGISTER,
  FMSNMT_REGACK,
  FMSNMT_PUBLISH,
  FMSNMT_PUBACK,
  FMSNMT_PUBCOMP,
  FMSNMT_PUBREC,
  FMSNMT_PUBREL,
  FMSNMT_SUBSCRIBE = 0x12,
  FMSNMT_SUBACK,
  FMSNMT_UNSUBSCRIBE,
  FMSNMT_UNSUBACK,
  FMSNMT_PINGREQ,
  FMSNMT_PINGRESP,
  FMSNMT_DISCONNECT,
  FMSNMT_WILLTOPICUPD = 0x1a,
  FMSNMT_WILLTOPICRESP,
  FMSNMT_WILLMSGUPD,
  FMSNMT_WILLMSGRESP,

  /// Reserved value in mqtt, but we use as invalid value.
  FMSNMT_INVALID = 0xff,
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgHeader struct
 */
struct FMSNMsgHeader
{
  uint8_t     length;
  FMSNMsgType type;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgAdvertise struct
 */
struct FMSNMsgAdvertise : public FMSNMsgHeader
{
  uint8_t  gwId;
  uint16_t duration;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgSearchGw struct
 */
struct FMSNMsgSearchGw : public FMSNMsgHeader
{
  uint8_t radius;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgGwInfo struct
 */
struct FMSNMsgGwInfo : public FMSNMsgHeader
{
  uint8_t gwId;
  char    gwAdd[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgConnect struct
 */
struct FMSNMsgConnect :  public FMSNMsgHeader
{
  uint8_t  flags;
  uint8_t  protocolId;
  uint16_t duration;
  char     clientId[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgConnAck struct
 */
struct FMSNMsgConnAck :  public FMSNMsgHeader
{
  FMSNReturnCode returnCode;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgWillTopic struct
 */
struct FMSNMsgWillTopic :  public FMSNMsgHeader
{
  uint8_t flags;
  char    willTopic[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgWillMsg struct
 */
struct FMSNMsgWillMsg :  public FMSNMsgHeader
{
  char willmsg[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgRegister struct
 */
struct FMSNMsgRegister :  public FMSNMsgHeader
{
  uint16_t topicId;
  uint16_t messageId;
  char     topicName[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgRegAck struct
 */
struct FMSNMsgRegAck :  public FMSNMsgHeader
{
  uint16_t       topicId;
  uint16_t       messageId;
  FMSNReturnCode returnCode;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgPublish struct
 */
struct FMSNMsgPublish :  public FMSNMsgHeader
{
  uint8_t  flags;
  uint16_t topicId;
  uint16_t messageId;
  char     data[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgPubAck struct
 */
struct FMSNMsgPubAck :  public FMSNMsgHeader
{
  uint16_t       topicId;
  uint16_t       messageId;
  FMSNReturnCode returnCode;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgPubQos2 struct
 */
struct FMSNMsgPubQos2 :  public FMSNMsgHeader
{
  uint16_t messageId;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgSubscribe struct
 */
struct FMSNMsgSubscribe :  public FMSNMsgHeader
{
  uint8_t  flags;
  uint16_t messageId;

  union
  {
    char     topicName[0];
    uint16_t topicId;
  };
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgSubAck struct
 */
struct FMSNMsgSubAck :  public FMSNMsgHeader
{
  uint8_t        flags;
  uint16_t       topicId;
  uint16_t       messageId;
  FMSNReturnCode returnCode;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgUnsubscribe struct
 */
struct FMSNMsgUnsubscribe :  public FMSNMsgHeader
{
  uint8_t  flags;
  uint16_t messageId;

  union
  {
    char     topicName[0];
    uint16_t topicId;
  } FMSN_STRUCT_PACKED;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgUnsubAck struct
 */
struct FMSNMsgUnsubAck :  public FMSNMsgHeader
{
  uint16_t messageId;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgPingReq struct
 */
struct FMSNMsgPingReq :  public FMSNMsgHeader
{
  char clientId[0];
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgDisconnect struct
 */
struct FMSNMsgDisconnect :  public FMSNMsgHeader
{
  uint16_t duration;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgWillTopicResp struct
 */
struct FMSNMsgWillTopicResp :  public FMSNMsgHeader
{
  FMSNReturnCode returnCode;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNMsgWillMsgResp struct
 */
struct FMSNMsgWillMsgResp :  public FMSNMsgHeader
{
  FMSNReturnCode returnCode;
} FMSN_STRUCT_PACKED;

/**
 * @brief The FMSNTopic struct
 */
struct FMSNTopic
{
  const char *name;
  uint16_t    id;
};

#endif // __INCLUDED_FDCE12F8526A11E7AA6EA088B4D1658C
