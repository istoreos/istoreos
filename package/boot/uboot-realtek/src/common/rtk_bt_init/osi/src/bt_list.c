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
*	    bt_list.c
*
*	Abstract:
*	    To implement list data structure
*
*	Major Change History:
*	      When             Who         What
*    	--------------------------------------------------------------
*	    2016-09-01       caicheng       Created
*
*	Notes:
*
******************************************************************************/
#include "../include/osi_include_int.h"
#include "../include/osi_include_ext.h"

//****************************************************************************
// Structure
//****************************************************************************


//****************************************************************************
// FUNCTION
//****************************************************************************
//Initialize a list with its header
void ListInitializeHeader(PRT_LIST_HEAD ListHead)
{
    ListHead->Next = ListHead;
    ListHead->Prev = ListHead;
}

/**
    Tell whether the list is empty
    \param [IN] ListHead          <RT_LIST_ENTRY>                 : List header of which to be test
*/
unsigned char ListIsEmpty(PRT_LIST_HEAD ListHead)
{
    return ListHead->Next == ListHead;
}

/*
    Insert a new entry between two known consecutive entries.
    This is only for internal list manipulation where we know the prev&next entries already
    @New : New element to be added
    @Prev: previous element in the list
    @Next: Next element in the list
*/
void
    ListAdd(
    PRT_LIST_ENTRY New,
    PRT_LIST_ENTRY Prev,
    PRT_LIST_ENTRY Next
    )
{
    Next->Prev = New;
    New->Next = Next;
    New->Prev = Prev;
    Prev->Next = New;
}
/**
    Add a new entry to the list.
    Insert a new entry after the specified head. This is good for implementing stacks.
    \param [IN] ListNew            <RT_LIST_ENTRY>                 : new entry to be added
    \param [IN OUT] ListHead    <RT_LIST_ENTRY>                 : List header after which to add new entry
*/
void
ListAddToHead(
    PRT_LIST_ENTRY ListNew,
    PRT_LIST_HEAD ListHead
    )
{
    ListAdd(ListNew, ListHead, ListHead->Next);
}

/**
    Add a new entry to the list.
    Insert a new entry before the specified head. This is good for implementing queues.
    \param [IN] ListNew            <RT_LIST_ENTRY>                 : new entry to be added
    \param [IN OUT] ListHead    <RT_LIST_ENTRY>                 : List header before which to add new entry
*/
void
ListAddToTail(
    PRT_LIST_ENTRY ListNew,
    PRT_LIST_HEAD ListHead
    )
{
    ListAdd(ListNew, ListHead->Prev, ListHead);
}

RT_LIST_ENTRY*
ListGetTop(
    PRT_LIST_HEAD ListHead
)
{

    if (ListIsEmpty(ListHead))
        return 0;

    return ListHead->Next;
}

RT_LIST_ENTRY*
ListGetTail(
    PRT_LIST_HEAD ListHead
)
{
    if (ListIsEmpty(ListHead))
        return 0;

    return ListHead->Prev;
}
/**
    Delete entry from the list
    Note: ListIsEmpty() on this list entry would not return true, since its state is undefined
    \param [IN] ListToDelete     <RT_LIST_ENTRY>                 : list entry to be deleted
*/
void ListDeleteNode(PRT_LIST_ENTRY ListToDelete)
{
//    if (ListToDelete->Next != NULL && ListToDelete->Prev != NULL)
    {
        ListToDelete->Next->Prev = ListToDelete->Prev;
        ListToDelete->Prev->Next = ListToDelete->Next;
        ListToDelete->Next = ListToDelete->Prev = ListToDelete;
    }
}
