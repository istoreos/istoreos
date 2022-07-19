#ifndef OSI_USB_H
#define OSI_USB_H
#include "osi_data_types.h"
#include "osi_func.h"
/*
 * USB directions
 *
 * This bit flag is used in endpoint descriptors' bEndpointAddress field.
 * It's also one of three fields in control requests bRequestType.
 */
#define OSI_USB_DIR_OUT			    0		/* to device */
#define OSI_USB_DIR_IN			    0x80		/* to host */

#define OSI_USB_MAXENDPOINTS		16


/*
 * USB types, the second of three bRequestType fields
 */
#define OSI_USB_TYPE_MASK			(0x03 << 5)
#define OSI_USB_TYPE_STANDARD		(0x00 << 5)
#define OSI_USB_TYPE_CLASS			(0x01 << 5)
#define OSI_USB_TYPE_VENDOR			(0x02 << 5)
#define OSI_USB_TYPE_RESERVED		(0x03 << 5)

/* "pipe" definitions */

#define OSI_PIPE_ISOCHRONOUS    0
#define OSI_PIPE_INTERRUPT      1
#define OSI_PIPE_CONTROL        2
#define OSI_PIPE_BULK           3
#define OSI_PIPE_DEVEP_MASK     0x0007ff00

#define OSI_USB_ISOCHRONOUS    0
#define OSI_USB_INTERRUPT      1
#define OSI_USB_CONTROL        2
#define OSI_USB_BULK           3


struct osi_usb_interface_descriptor {
	u8 bLength;
	u8 bDescriptorType;	/* 0x04 */
	u8 bInterfaceNumber;
	u8 bAlternateSetting;
	u8 bNumEndpoints;
	u8 bInterfaceClass;
	u8 bInterfaceSubClass;
	u8 bInterfaceProtocol;
	u8 iInterface;
} __attribute__ ((packed));

struct osi_usb_configuration_descriptor {
	u8 bLength;
	u8 bDescriptorType;	/* 0x2 */
	u16 wTotalLength;
	u8 bNumInterfaces;
	u8 bConfigurationValue;
	u8 iConfiguration;
	u8 bmAttributes;
	u8 bMaxPower;
} __attribute__ ((packed));

struct osi_usb_device_descriptor {
	u8 bLength;
	u8 bDescriptorType;	/* 0x01 */
	u16 bcdUSB;
	u8 bDeviceClass;
	u8 bDeviceSubClass;
	u8 bDeviceProtocol;
	u8 bMaxPacketSize0;
	u16 idVendor;
	u16 idProduct;
	u16 bcdDevice;
	u8 iManufacturer;
	u8 iProduct;
	u8 iSerialNumber;
	u8 bNumConfigurations;
} __attribute__ ((packed));


/* USB_DT_ENDPOINT: Endpoint descriptor */
struct osi_usb_endpoint_descriptor {
	u8  bLength;
	u8  bDescriptorType;

	u8  bEndpointAddress;
	u8  bmAttributes;
	u16 wMaxPacketSize;
	u8  bInterval;

	/* NOTE:  these two are _only_ in audio endpoints. */
	/* use USB_DT_ENDPOINT*_SIZE in bLength, not sizeof. */
	u8  bRefresh;
	u8  bSynchAddress;
} __attribute__ ((packed));


/* USB_DT_SS_ENDPOINT_COMP: SuperSpeed Endpoint Companion descriptor */
struct osi_usb_ss_ep_comp_descriptor {
	u8  bLength;
	u8  bDescriptorType;

	u8  bMaxBurst;
	u8  bmAttributes;
	u16 wBytesPerInterval;
} __attribute__ ((packed));

/* Interface */
struct osi_usb_interface {
	struct osi_usb_interface_descriptor desc;

	unsigned char	no_of_ep;
	unsigned char	num_altsetting;
	unsigned char	act_altsetting;

	struct osi_usb_endpoint_descriptor ep_desc[OSI_USB_MAXENDPOINTS];
	/*
	 * Super Speed Device will have Super Speed Endpoint
	 * Companion Descriptor  (section 9.6.7 of usb 3.0 spec)
	 * Revision 1.0 June 6th 2011
	 */
	struct osi_usb_ss_ep_comp_descriptor ss_ep_comp_desc[OSI_USB_MAXENDPOINTS];
} __attribute__ ((packed));



struct osi_usb_device {
	int	devnum;			/* Device number on USB bus */
	int	speed;			/* full/low/high */
	char	mf[32];			/* manufacturer */
	char	prod[32];		/* product */
	char	serial[32];		/* serial number */

    /* Maximum packet size; one of: PACKET_SIZE_* */
	int maxpacketsize;
    struct osi_usb_device_descriptor descriptor;
    void*   context;
};


/* Create various pipes... */
#define osi_create_pipe(dev,endpoint) \
		(((dev)->devnum << 8) | ((endpoint) << 15) | \
		(dev)->maxpacketsize)

#define osi_usb_sndctrlpipe(dev, endpoint)	((OSI_PIPE_CONTROL << 30) | \
					 osi_create_pipe(dev, endpoint))
#define osi_usb_rcvctrlpipe(dev, endpoint)	((OSI_PIPE_CONTROL << 30) | \
					 osi_create_pipe(dev, endpoint) | \
					 OSI_USB_DIR_IN)


#define osi_usb_sndintpipe(dev, endpoint)	((OSI_PIPE_INTERRUPT << 30) | \
					 osi_create_pipe(dev, endpoint))
#define osi_usb_rcvintpipe(dev, endpoint)	((OSI_PIPE_INTERRUPT << 30) | \
					 osi_create_pipe(dev, endpoint) | \
					 OSI_USB_DIR_IN)

int osi_usb_control_msg(struct osi_usb_device *dev, unsigned int pipe,
		unsigned char request, unsigned char requesttype,
		unsigned short value, unsigned short index,
		void *data, unsigned short size, int timeout);

/*
 * submits an Interrupt Message
 */
int osi_usb_submit_int_msg(struct osi_usb_device *dev, unsigned long pipe,
		void *buffer, int transfer_len, int interval);

#endif
