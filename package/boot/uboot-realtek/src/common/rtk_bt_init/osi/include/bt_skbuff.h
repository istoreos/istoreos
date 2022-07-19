/******************************************************************************
 *
 *  Copyright (C) 2016 Realtek Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/
/******************************************************************************
*
*	Module Name:
*	    bt_skbuff.h
*
*	Abstract:
*	    Data buffer managerment through whole bluetooth stack.
*
*	Major Change History:
*	      When             Who       What
*	    --------------------------------------------------------------
*	    2016-08-29      caicheng     Created.
*
*	Notes:
*	      To reduce memory copy when pass data buffer to other layers,
*       RTK_BUFFER is designed referring to linux socket buffer.
*       But I still wonder its effect, since RTK_BUFFER is much bigger
*       than original data buffer.RTK_BUFFER will reduce its member if
*       it would not reach what i had expected.
*
******************************************************************************/


#ifndef BT_SKBUFF_H
#define BT_SKBUFF_H
#include "bt_list.h"
#include "osi_data_types.h"

#ifndef EXTERN
#define EXTERN
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif
/*----------------------------------------------------------------------------------
    CONSTANT DEFINITION
----------------------------------------------------------------------------------*/
#define RTK_CONTEXT_SIZE 12

#define RTB_QUEUE_ID_LENGTH          64

/*----------------------------------------------------------------------------------
    STRUCTURE DEFINITION
----------------------------------------------------------------------------------*/
/**
    Rtk buffer definition
      Head -->|<---Data--->|<-----Length------>| <---End
                     _________________________________
                    |_____________|___________________|
                    |<-headroom->|<--RealDataBuffer-->|

    Compared to socket buffer, there exists no tail and end pointer and tailroom as tail is rarely used in bluetooth stack
    \param List             : List structure used to list same type rtk buffer and manipulate rtk buffer like list.
    \param Head           : Pointer to truely allocated data buffer. It point to the headroom
    \param Data           : Pointer to real data buffer.
    \param Length        : currently data length
    \param HeadRoom  : Record initialize headroom size.
    \param RefCount    : Reference count. zero means able to be freed, otherwise somebody is handling it.
    \param Priv            : Reserved for multi-device support. Record Hci pointer which will handles this packet
    \param Contest      : Control buffer, put private variables here.
*/
typedef struct _RTK_BUFFER
{
    RT_LIST_ENTRY List;
    u8 *Head;
    u8 *Data;
    u8 *Tail;
    u8 *End;
    u32 Length;
    u32 HeadRoom;
//    RT_U16 TailRoom;
    signed char   RefCount;

    void* Priv;
    u8 Context[RTK_CONTEXT_SIZE];
}RTK_BUFFER, *PRTK_BUFFER;

/**
    RTK_BUFFER Control Buffer Context
    \param  PacketType      : HCI data types, Command/Acl/...
    \param  LastFrag          : Is Current Acl buffer the last fragment.(0 for no, 1 for yes)
    \param  TxSeq             : Current packet tx sequence
    \param  Retries            : Current packet retransmission times
    \param  Sar                 : L2cap control field segmentation and reassembly bits
*/
struct BT_RTB_CONTEXT{
    u8   PacketType;
    u16 Handle;
};

///definition to get rtk_buffer's control buffer context pointer
#define BT_CONTEXT(_Rtb) ((struct BT_RTB_CONTEXT *)((_Rtb)->Context))

/**
    Since RTBs are always used into/from list, so abstract this struct and provide APIs to easy process on RTBs
*/
typedef struct _RTB_QUEUE_HEAD  RTB_QUEUE_HEAD;
/*----------------------------------------------------------------------------------
    EXTERNAL FUNCTION
----------------------------------------------------------------------------------*/
/**
    Allocate a RTK_BUFFER with specified data length and reserved headroom.
    If caller does not know actual headroom to reserve for further usage, specify it to zero to use default value.
    \param [IN]     Length            <u32>        : current data buffer length to allcated
    \param [IN]     HeadRoom     <u32>         : if caller knows reserved head space, set it; otherwise set 0 to use default value
    \return pointer to RTK_BUFFER if succeed, null otherwise
*/
RTK_BUFFER*
RtbAllocate(
    IN u32 Length,
    IN u32 HeadRoom
    );

/**
    Free specified Rtk_buffer
    \param [IN]     RtkBuffer            <RTK_BUFFER*>        : buffer to free
*/
void
RtbFree(
    IN RTK_BUFFER* RtkBuffer
    );

/**
    increament reference count
*/
void
RtbIncreaseRefCount(
    IN RTK_BUFFER* RtkBuffer
);

/**
    Recycle a rtk_buffer after its usage if specified rtb could
    if rtb total length is not smaller than specified rtbsize to be recycled for, it will succeeded recycling
    \param [IN OUT]     RtkBuffer            <RTK_BUFFER*>        : buffer to recycle
    \param [IN]             RtbSize              <u32>                 : size of buffer to be recycled for
*/
/*
BOOLEAN
RtbCheckRecycle(
    IN OUT RTK_BUFFER* RtkBuffer,
    IN u32   RtbSize
    );
*/
/**
    Add a specified length protocal header to the start of data buffer hold by specified rtk_buffer.
    This function extends used data area of the buffer at the buffer start.
    \param [IN OUT]     RtkBuffer            <RTK_BUFFER*>        : data buffer to add
    \param [IN]            Length                <u32>                 : header length
    \return  Pointer to the first byte of the extra data is returned
*/
u8*
RtbAddHead(
    IN OUT RTK_BUFFER* RtkBuffer,
    IN u32                 Length
    );

/**
    Remove a specified length data from the start of data buffer hold by specified rtk_buffer.
    This function returns the memory to the headroom.
    \param [IN OUT]     RtkBuffer            <RTK_BUFFER*>        : data buffer to remove
    \param [IN]            Length                <u32>                 : header length
    \return  Pointer to the next data in the buffer is returned, usually useless
*/
unsigned char
RtbRemoveHead(
    IN OUT RTK_BUFFER* RtkBuffer,
    IN u32                 Length
    );

/**
    Add a specified length protocal header to the end of data buffer hold by specified rtk_buffer.
    This function extends used data area of the buffer at the buffer end.
    \param [IN OUT]     RtkBuffer            <RTK_BUFFER*>        : data buffer to add
    \param [IN]            Length                <u32>                 : header length
    \return  Pointer to the first byte of the extra data is returned
*/
EXTERN u8*
RtbAddTail(
    IN OUT RTK_BUFFER* RtkBuffer,
    IN u32                 Length
    );

/**
    Remove a specified length data from the end of data buffer hold by specified rtk_buffer.
*/
EXTERN unsigned char
RtbRemoveTail(
    IN OUT RTK_BUFFER * RtkBuffer,
    IN     u32       Length
);

/**
    Initialize a rtb queue.
    \return  Initilized rtb queue if succeed, otherwise NULL
*/
EXTERN RTB_QUEUE_HEAD*
RtbQueueInit(void);

/**
    Free a rtb queue.
    \param [IN]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
*/
EXTERN void
RtbQueueFree(
    RTB_QUEUE_HEAD* RtkQueueHead
    );
/**
    Queue specified RtkBuffer into a RtkQueue at list tail.
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \param [IN]            RtkBuffer                <RTK_BUFFER*>                 : Rtk buffer to add
*/
EXTERN void
RtbQueueTail(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead,
    IN RTK_BUFFER*                 RtkBuffer
    );

/**
    Queue specified RtkBuffer into a RtkQueue at list Head.
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \param [IN]            RtkBuffer                <RTK_BUFFER*>                 : Rtk buffer to add
*/
EXTERN void
RtbQueueHead(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead,
    IN RTK_BUFFER*                 RtkBuffer
    );

/**
    Remove a RtkBuffer from specified rtkqueue at list tail.
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \return    removed rtkbuffer if succeed, otherwise NULL
*/
EXTERN RTK_BUFFER*
RtbDequeueTail(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead
    );

/**
    Remove a RtkBuffer from specified rtkqueue at list head.
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \return    removed rtkbuffer if succeed, otherwise NULL
*/
EXTERN RTK_BUFFER*
RtbDequeueHead(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead
    );

/**
    Get current rtb queue's length.
    \param [IN]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \return    current queue's length
*/
EXTERN signed long
RtbGetQueueLen(
    IN RTB_QUEUE_HEAD* RtkQueueHead
    );

/**
    Empty the rtkqueue.
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
*/
EXTERN void
RtbEmptyQueue(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead
    );

/**
    Get the RtkBuffer which is the head of a RtkQueue
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \return head of the RtkQueue , otherwise NULL
*/
EXTERN RTK_BUFFER*
RtbTopQueue(
    IN RTB_QUEUE_HEAD* RtkQueueHead
);

/**
    Insert new Rtkbuffer in the old buffer
    \param [IN OUT]     RtkQueueHead        <RTB_QUEUE_HEAD*>        : Rtk Queue
    \param [IN]            OldRtkBuffer                <RTK_BUFFER*>                 : old rtk buffer
    \param [IN]            NewRtkBuffer                <RTK_BUFFER*>                 : Rtk buffer to add
*/
EXTERN void
RtbInsertBefore(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead,
    IN RTK_BUFFER* pOldRtkBuffer,
    IN RTK_BUFFER* pNewRtkBuffer
);

/**
    check whether the buffer is the last node in the queue
*/
EXTERN unsigned char
RtbNodeIsLast(
    IN RTB_QUEUE_HEAD* RtkQueueHead,
    IN RTK_BUFFER*                 pRtkBuffer
);

/**
    get the next buffer node after the specified buffer in the queue
    if the specified buffer is the last node in the queue , return NULL
    \param [IN]     RtkBuffer        <RTK_BUFFER*>        : Rtk Queue
    \param [IN]     RtkBuffer        <RTK_BUFFER*>        : Rtk buffer
    \return node after the specified buffer
*/
EXTERN RTK_BUFFER*
RtbQueueNextNode(
    IN RTB_QUEUE_HEAD* RtkQueueHead,
    IN RTK_BUFFER*                 pRtkBuffer
);

/**
    check whether queue is empty
*/
/*EXTERN BOOLEAN
RtbQueueIsEmpty(
   IN RTB_QUEUE_HEAD* RtkQueueHead
);
*/

//annie_tmp
EXTERN unsigned char
RtbCheckQueueLen(
   IN RTB_QUEUE_HEAD* RtkQueueHead,
   IN u8 Len
);

EXTERN void
RtbRemoveNode(
    IN OUT RTB_QUEUE_HEAD* RtkQueueHead,
    IN RTK_BUFFER*         RtkBuffer
);

EXTERN RTK_BUFFER*
    RtbCloneBuffer(
    IN RTK_BUFFER* pDataBuffer
    );

#endif /*BT_SKBUFF_H*/
