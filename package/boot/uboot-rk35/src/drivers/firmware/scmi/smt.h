/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2015-2019, Arm Limited and Contributors. All rights reserved.
 * Copyright (C) 2019-2020 Linaro Limited.
 */
#ifndef SCMI_SMT_H
#define SCMI_SMT_H

#include <asm/types.h>

/**
 * struct scmi_smt_header - Description of the shared memory message buffer
 *
 * SMT stands for Shared Memory based Transport.
 * SMT uses 28 byte header prior message payload to handle the state of
 * the communication channel realized by the shared memory area and
 * to define SCMI protocol information the payload relates to.
 */
struct scmi_smt_header {
	__le32 reserved;
	__le32 channel_status;
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR	BIT(1)
#define SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE	BIT(0)
	__le32 reserved1[2];
	__le32 flags;
#define SCMI_SHMEM_FLAG_INTR_ENABLED		BIT(0)
	__le32 length;
	__le32 msg_header;
	u8 msg_payload[0];
};

#define SMT_HEADER_TOKEN(token)		(((token) << 18) & GENMASK(31, 18))
#define SMT_HEADER_PROTOCOL_ID(proto)	(((proto) << 10) & GENMASK(17, 10))
#define SMT_HEADER_MESSAGE_TYPE(type)	(((type) << 18) & GENMASK(9, 8))
#define SMT_HEADER_MESSAGE_ID(id)	((id) & GENMASK(7, 0))

/**
 * struct scmi_smt - Description of a SMT memory buffer
 * @buf:	Shared memory base address
 * @size:	Shared memory byte size
 */
struct scmi_smt {
	u8 *buf;
	size_t size;
};

static inline bool scmi_smt_channel_is_free(struct scmi_smt *smt)
{
	struct scmi_smt_header *hdr = (void *)smt->buf;

	return hdr->channel_status & SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE;
}

static inline bool scmi_smt_channel_reports_error(struct scmi_smt *smt)
{
	struct scmi_smt_header *hdr = (void *)smt->buf;

	return hdr->channel_status & SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR;
}

static inline void scmi_smt_get_channel(struct scmi_smt *smt)
{
	struct scmi_smt_header *hdr = (void *)smt->buf;

	hdr->channel_status &= ~SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE;
}

static inline void scmi_smt_put_channel(struct scmi_smt *smt)
{
	struct scmi_smt_header *hdr = (void *)smt->buf;

	hdr->channel_status |= SCMI_SHMEM_CHAN_STAT_CHANNEL_FREE;
	hdr->channel_status &= ~SCMI_SHMEM_CHAN_STAT_CHANNEL_ERROR;
}

int scmi_dt_get_smt_buffer(struct udevice *dev, struct scmi_smt *smt);

int scmi_write_msg_to_smt(struct udevice *dev, struct scmi_smt *smt,
			  struct scmi_msg *msg);

int scmi_read_resp_from_smt(struct udevice *dev, struct scmi_smt *smt,
			    struct scmi_msg *msg);

void scmi_clear_smt_channel(struct scmi_smt *smt);

#endif /* SCMI_SMT_H */
