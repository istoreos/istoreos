/************************************************************************
 *
 *  ir.h
 *
 *  Public header file for IR module
 *
 ************************************************************************/

#ifndef IR_H
#define IR_H

/************************************************************************
 *  Definition
 ************************************************************************/

/************************************************************************
 *  Public functions
 ************************************************************************/
void IR_init(void);
unsigned int IR_Get_irdvf(void);
void IR_Set_irdvf(unsigned int data);
unsigned int IR_Parsing_key(void);
int IR_config_wakeup_keys(void *addr);

#endif /* #ifndef IR_H */
