#include "osi_usb.h"

int osi_usb_control_msg(struct osi_usb_device *dev, unsigned int pipe,
		unsigned char request, unsigned char requesttype,
		unsigned short value, unsigned short index,
		void *data, unsigned short size, int timeout)
{
    int len;
	len = usb_control_msg((struct usb_device *)(dev->context),
			      pipe,
			      request,
			      requesttype,
			      value, index, data, size,
			      timeout);

    return len;
}

/*
 * submits an Interrupt Message
 */
int osi_usb_submit_int_msg(struct osi_usb_device *dev, unsigned long pipe,
		void *buffer, int transfer_len, int interval)
{
    int ret_val = 0;
    ret_val = usb_submit_int_msg(
        (struct usb_device *)(dev->context), pipe,
        buffer, transfer_len, interval);

    return ret_val;
}
