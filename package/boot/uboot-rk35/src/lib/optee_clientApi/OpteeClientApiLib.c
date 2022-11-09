/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <optee_include/OpteeClientApiLib.h>
#include <optee_include/OpteeClientMem.h>
#include <optee_include/OpteeClientRPC.h>
#include <optee_include/OpteeClientSMC.h>
#include <optee_include/OpteeClientRkFs.h>
#include <optee_include/teesmc.h>
#include <optee_include/teesmc_optee.h>
#include <optee_include/teesmc_v2.h>

#define OPTEE_MSG_REVISION_MAJOR        2
#define OPTEE_MSG_REVISION_MINOR        0

static bool optee_is_init;

static bool optee_api_revision_is_compatible(void)
{
	ARM_SMC_ARGS ArmSmcArgs = {0};

	ArmSmcArgs.Arg0 = OPTEE_SMC_CALLS_REVISION;

	tee_smc_call(&ArmSmcArgs);

	if (ArmSmcArgs.Arg0 == OPTEE_MSG_REVISION_MAJOR &&
	    ArmSmcArgs.Arg1 >= OPTEE_MSG_REVISION_MINOR) {
		printf("optee api revision: %d.%d\n",
		       ArmSmcArgs.Arg0, ArmSmcArgs.Arg1);
		return true;
	} else {
		printf("optee check api revision fail: %d.%d\n",
		       ArmSmcArgs.Arg0, ArmSmcArgs.Arg1);
		return false;
	}
}

void optee_get_shm_config(phys_addr_t *base, phys_size_t *size)
{
	ARM_SMC_ARGS ArmSmcArgs = {0};

	ArmSmcArgs.Arg0 = OPTEE_SMC_GET_SHM_CONFIG_V2;

	tee_smc_call(&ArmSmcArgs);

	*base = ArmSmcArgs.Arg1;
	*size = ArmSmcArgs.Arg2;
}

/*
 * Initlialize the library
 */
TEEC_Result OpteeClientApiLibInitialize(void)
{
	TEEC_Result status = TEEC_SUCCESS;

	if (optee_is_init)
		return TEEC_SUCCESS;

	/* check api revision compatibility */
	if (!optee_api_revision_is_compatible())
		panic("optee api revision is too low");

	status = OpteeClientMemInit();
	if (status != TEEC_SUCCESS) {
		printf("TEEC: OpteeClientMemInit fail!\n");
		return status;
	}
	status = OpteeClientRkFsInit();
	if (status != TEEC_SUCCESS) {
		printf("TEEC: OpteeClientRkFsInit fail!\n");
		return status;
	}

	optee_is_init = true;

	return TEEC_SUCCESS;
}

/*
 * This function initializes a new TEE Context, connecting this Client
 * application to the TEE indentified by the name name.
 *
 * name == NULL will give the default TEE.
 *
 * In this implementation only the default name is supported.
 * If name != NULL then TEEC_ERROR_ITEM_NOT_FOUND is returned.
 */
TEEC_Result TEEC_InitializeContext(const char *name,
				TEEC_Context *context)
{
	TEEC_Result teecresult = TEEC_SUCCESS;

	debug("TEEC_InitializeContext Enter: name=%s  context=%s  0x%X\n",
			name, context->devname, context->fd);

	if (context == NULL) {
		teecresult = TEEC_ERROR_BAD_PARAMETERS;
		goto exit;
	}

	if (name != NULL) {
		teecresult = TEEC_ERROR_ITEM_NOT_FOUND;
		goto exit;
	}

	memset(context, 0, sizeof(*context));

exit:
	debug("TEEC_InitializeContext Exit : teecresult=0x%X\n", teecresult);
	return teecresult;
}

/*
 * This function destroys an initialized TEE Context, closing the connection
 * between the Client and the TEE.
 * The function implementation MUST do nothing if context is NULL
 *
 * There is nothing to do here since there is no context state.
 */
TEEC_Result TEEC_FinalizeContext(TEEC_Context *context)
{
	debug("TEEC_FinalizeContext Enter-Exit: context=0x%zu\n",
		(size_t)context);
	return TEEC_SUCCESS;
}

/*
 * Allocates or registers shared memory.
 *
 * Since EDK2 is configured flat with virtual memory == physical memory
 * then we don't need to perform any special operations to get physical
 * contiguous memory.
 */
TEEC_Result TEEC_AllocateSharedMemory(TEEC_Context *context,
			TEEC_SharedMemory *shared_memory)
{
	TEEC_Result TeecResult = TEEC_SUCCESS;

	debug("TEEC_AllocateSharedMemory Enter: context=%s 0x%X, shared_memory=0x%zu\n",
		context->devname, context->fd, shared_memory->size);

	if ((context == NULL) || (shared_memory == NULL)) {
		TeecResult = TEEC_ERROR_BAD_PARAMETERS;
		goto Exit;
	}

	if (shared_memory->flags != 0) {
		TeecResult = TEEC_ERROR_BAD_PARAMETERS;
		goto Exit;
	}

	shared_memory->buffer = NULL;
	shared_memory->alloc_buffer = 0;

	debug("TEEC_AllocateSharedMemory: size=0x%zu, flags=0x%X\n",
			shared_memory->size, shared_memory->flags);

	shared_memory->buffer = OpteeClientMemAlloc(shared_memory->size);
	if (shared_memory->buffer == NULL) {
		TeecResult = TEEC_ERROR_OUT_OF_MEMORY;
		goto Exit;
	}

	shared_memory->alloc_buffer = shared_memory->buffer;

Exit:
	debug("TEEC_AllocateSharedMemory Exit : TeecResult=0x%X\n", TeecResult);
	return TeecResult;
}

/*
 * Releases shared memory.
 *
 * The optee_client implementation allows this to be called with a null pointer
 * and null buffer but we'll assert this is not the case for better debugging.
 */
void TEEC_ReleaseSharedMemory(TEEC_SharedMemory *shared_memory)
{
	debug("TEEC_ReleaseSharedMemory Enter: shared_memory=0x%zu\n",
				shared_memory->size);

	if (shared_memory == NULL)
		goto Exit;

	if (shared_memory->buffer == NULL)
		goto Exit;

	if (shared_memory->alloc_buffer != 0) {
		OpteeClientMemFree(shared_memory->alloc_buffer);
		shared_memory->alloc_buffer = 0;
	}

	shared_memory->buffer = NULL;
	shared_memory->size = 0;

Exit:
	return;
}

/*
 * Register shared memory
 *
 * If the supplied buffer is compatible we can use it as supplied otherwise
 * we'll need to allocate a copy buffer for the transfer instead.
 */
TEEC_Result TEEC_RegisterSharedMemory(TEEC_Context *context,
			TEEC_SharedMemory *shared_memory)
{
	TEEC_Result TeecResult = TEEC_SUCCESS;

	if ((context == NULL) || (shared_memory == NULL)) {
		TeecResult = TEEC_ERROR_BAD_PARAMETERS;
		goto Exit;
	}

	if (shared_memory->buffer == NULL) {
		TeecResult = TEEC_ERROR_BAD_PARAMETERS;
		goto Exit;
	}

	shared_memory->alloc_buffer = 0;

	phys_addr_t start = (phys_addr_t) shared_memory->buffer;

	if ((start % 4096) != 0) {
		TEEC_SharedMemory TempSharedMemory;
		TempSharedMemory.size  = shared_memory->size;
		TempSharedMemory.flags = shared_memory->flags;

		TeecResult = TEEC_AllocateSharedMemory
			(context, &TempSharedMemory);

		if (TeecResult != TEEC_SUCCESS)
			goto Exit;

		shared_memory->alloc_buffer = TempSharedMemory.alloc_buffer;
	}

Exit:
	debug("TEEC_RegisterSharedMemory Exit : TeecResult=0x%X\n", TeecResult);
	return TeecResult;
}

/*
 * This function opens a new Session between the Client application and the
 * specified TEE application.
 *
 * Only connection_method == TEEC_LOGIN_PUBLIC is supported connection_data and
 * operation shall be set to NULL.
 */
TEEC_Result TEEC_OpenSession(TEEC_Context *context,
			TEEC_Session *session,
			const TEEC_UUID *destination,
			uint32_t connection_method,
			const void *connection_data,
			TEEC_Operation *operation,
			uint32_t *error_origin)
{
	TEEC_Result TeecResult = TEEC_SUCCESS;
	uint32_t TeecErrorOrigin = TEEC_ORIGIN_API;

	debug("TEEC_OpenSession: session=0x%X, ...\n", session->id);

	if ((context == NULL) || (session == NULL) || (destination == NULL)) {
		TeecResult = TEEC_ERROR_BAD_PARAMETERS;
		goto Exit;
	}

	if (connection_method != TEEC_LOGIN_PUBLIC) {
		TeecResult = TEEC_ERROR_NOT_SUPPORTED;
		goto Exit;
	}

	TEEC_Operation TeecNullOperation = {0};
	TEEC_Operation *TeecOperation;

	if (operation == NULL) {
		memset(&TeecNullOperation, 0, sizeof(TEEC_Operation));
		TeecOperation = &TeecNullOperation;
	} else {
		TeecOperation = operation;
	}

	TeecResult = TEEC_SMC_OpenSession(context, session, destination,
				TeecOperation, &TeecErrorOrigin);

Exit:
	if (error_origin != NULL)
		*error_origin = TeecErrorOrigin;

	debug("TEEC_OpenSession Exit : TeecResult=0x%X, TeecErrorOrigin=0x%X\n",
				TeecResult, TeecErrorOrigin);
	return TeecResult;
}

/*
 * This function closes a session which has been opened with a TEE
 * application.
 */
void TEEC_CloseSession(TEEC_Session *session)
{
	TEEC_Result TeecResult = TEEC_SUCCESS;
	uint32_t TeecErrorOrigin = TEEC_ORIGIN_API;

	debug("TEEC_CloseSession Enter: session=0x%X\n", session->id);

	if (session == NULL)
		goto Exit;

	TeecResult = TEEC_SMC_CloseSession(session, &TeecErrorOrigin);

Exit:
	debug("TEEC_CloseSession Exit : TeecResult=0x%X, TeecErrorOrigin=0x%X\n",
			TeecResult, TeecErrorOrigin);
	return;
}

/*
 * Invokes a TEE command (secure service, sub-PA or whatever).
 */
TEEC_Result TEEC_InvokeCommand(TEEC_Session *session,
				uint32_t cmd_id,
				TEEC_Operation *operation,
				uint32_t *error_origin)
{
	TEEC_Result TeecResult = TEEC_SUCCESS;
	uint32_t TeecErrorOrigin = TEEC_ORIGIN_API;

	debug("TEEC_InvokeCommand Enter: session=0x%X, cmd_id=0x%X\n",
			session->id, cmd_id);

	if (session == NULL) {
		TeecResult = TEEC_ERROR_BAD_PARAMETERS;
		goto Exit;
	}

	TEEC_Operation TeecNullOperation = {0};
	TEEC_Operation *TeecOperation;

	if (operation == NULL)
		TeecOperation = &TeecNullOperation;
	else
		TeecOperation = operation;

	TeecResult = TEEC_SMC_InvokeCommand(session, cmd_id,
			TeecOperation, &TeecErrorOrigin);

Exit:
	if (error_origin != NULL)
		*error_origin = TeecErrorOrigin;

	debug("TEEC_InvokeCommand Exit : TeecResult=0x%X, TeecErrorOrigin=0x%X\n",
				TeecResult, TeecErrorOrigin);

	return TeecResult;
}

/*
 * Request a cancellation of a in-progress operation (best effort)
 */
void TEEC_RequestCancellation(TEEC_Operation *operation)
{
	TEEC_Result TeecResult = TEEC_SUCCESS;
	uint32_t TeecErrorOrigin = TEEC_ORIGIN_API;

	if (operation == NULL)
		goto Exit;

	TeecResult = TEEC_SMC_RequestCancellation(operation, &TeecErrorOrigin);

Exit:
	debug("TEEC_RequestCancellation Exit : TeecResult=0x%X, TeecErrorOrigin=0x%X\n",
			TeecResult, TeecErrorOrigin);

	return;
}
