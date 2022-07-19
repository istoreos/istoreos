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
*	    bt_list.h
*
*	Abstract:
*	    To implement list data structure
*
*	Major Change History:
*	      When             Who         What
*	    --------------------------------------------------------------
*	    2016-08-029         caicheng       Created
*
*	Notes:
*
******************************************************************************/

#ifndef BT_LIST_H
#define BT_LIST_H

/**
\file  bt_list.h
\brief  Implement bluetooth list data structure. Has referred to Linux list implementation
          You could add your new list manipulation here.
*/


/**
 List entry structure, could be header or node.

                  Prev<-----Header---->Next

Every List has an additional header, and list tail will be list header's previous node.
You can use list to form a queue or a stack data structure
queue:
    ListAddToTail----->LIST_FOR_EACH iterate--->manipulate on the list entry
Stack:
    ListAddToHead--- >LIST_FOR_EACH iterate--->manipulate on the list entry
*/

///RT list structure definition
typedef struct _RT_LIST_ENTRY {
    struct _RT_LIST_ENTRY *Next;   ///< Entry's next element
    struct _RT_LIST_ENTRY *Prev;   ///< Entry's previous element
} RT_LIST_ENTRY, *PRT_LIST_ENTRY;

///List head would be another name of list entry, and it points to the list header
typedef RT_LIST_ENTRY       RT_LIST_HEAD, *PRT_LIST_HEAD;

/*----------------------------------------------------------------------------------
    EXTERNAL FUNCTION
----------------------------------------------------------------------------------*/

///Initialize a list with its header
void ListInitializeHeader(PRT_LIST_HEAD ListHead);

/**
    Add a new entry to the list.
    Insert a new entry after the specified head. This is good for implementing stacks.
    \param [IN]        ListNew     <RT_LIST_ENTRY>                 : new entry to be added
    \param [IN OUT] ListHead    <RT_LIST_ENTRY>                 : List header after which to add new entry
*/
void ListAddToHead(PRT_LIST_ENTRY ListNew, PRT_LIST_HEAD ListHead);

/**
    Add a new entry to the list.
    Insert a new entry before the specified head. This is good for implementing queues.
    \param [IN]        ListNew     <RT_LIST_ENTRY>                 : new entry to be added
    \param [IN OUT] ListHead    <RT_LIST_ENTRY>                 : List header before which to add new entry
*/
void ListAddToTail(PRT_LIST_ENTRY ListNew, PRT_LIST_HEAD ListHead);

/**
    Get entry in the head of the list
     \param [IN ] ListHead    <RT_LIST_ENTRY>                 : List header
     \return entry in the head , otherwise NULL
*/
RT_LIST_ENTRY* ListGetTop(PRT_LIST_HEAD ListHead);

/**
    Get entry in the tail of the list
     \param [IN ] ListHead    <RT_LIST_ENTRY>                 : List header
     \return entry in the tail , otherwise NULL
*/
RT_LIST_ENTRY*
ListGetTail(
    PRT_LIST_HEAD ListHead
);

/**
    Delete entry from the list
    Note: ListIsEmpty() on this list entry would not return true, since its state is undefined
    \param [IN] ListToDelete     <RT_LIST_ENTRY>                 : list entry to be deleted
*/
void ListDeleteNode(PRT_LIST_ENTRY ListToDelete);

/**
    Tell whether the list is empty
    \param [IN] ListHead          <RT_LIST_ENTRY>                 : List header of which to be test
*/
unsigned char ListIsEmpty(PRT_LIST_HEAD ListHead);

//EXTERN void ListEmpty(PRT_LIST_HEAD ListHead);

void
    ListAdd(
    PRT_LIST_ENTRY New,
    PRT_LIST_ENTRY Prev,
    PRT_LIST_ENTRY Next
    );

/*----------------------------------------------------------------------------------
    MACRO
----------------------------------------------------------------------------------*/

/**
    Macros to iterate over the list.
    \param _Iter          : struct PRT_LIST_ENTRY type iterator to use as a loop cursor
    \param _ListHead   : List head of which to be iterated
*/
#define LIST_FOR_EACH(_Iter, _ListHead) \
        for ((_Iter) = (_ListHead)->Next; (_Iter) != (_ListHead); (_Iter) = (_Iter)->Next)

/**
    Macros to iterate over the list safely against removal of list entry.
    If you would delete any list entry from the list while iterating the list, should use this macro
    \param _Iter          : Struct PRT_LIST_ENTRY type iterator to use as a loop cursor
    \param _Temp       : Another Struct PRT_LIST_ENTRY type to use as a temporary storage
    \param _ListHead   : List head of which to be iterated
*/
#define LIST_FOR_EACH_SAFELY(_Iter, _Temp, _ListHead) \
        for ((_Iter) = (_ListHead)->Next, (_Temp) = (_Iter)->Next; (_Iter) != (_ListHead);  \
               (_Iter) = (_Temp), (_Temp) = (_Iter)->Next)

/**
    Macros to get the struct pointer of this list entry
    You could make every RT_LIST_ENTRY at the first place of your structure to avoid the macro, which will be dangerouse.
    Copy from winnt.h.
    BUG:if offset of field in type larger than 32 bit interger, which is not likely to happen, it will error
    \param _Ptr               : Struct RT_LIST_ENTRY type pointer
    \param _Type            : The type of structure in which the RT_LIST_ENTRY embedded in
    \param _Field            : the name of the RT_LIST_ENTRY within the struct
*/
#define LIST_ENTRY(_Ptr, _Type, _Field) ((_Type *)((char *)(_Ptr)-(unsigned long)(&((_Type *)0)->_Field)))


#endif /*BT_LIST_H*/
