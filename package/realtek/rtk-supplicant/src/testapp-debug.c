#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "rtkcontrol.h"

#define DEBUG_TIME (1<<0)  // 1
#define DEBUG_INPUT (1<<1)  // 2
#define DEBUG_SHOWLIST (1<<2) // 4
#define DEBUG_VOWB (1<<3) // 8
#define DEBUG_FRMDROP (1<<4) // 16
#define DEBUG_VERSION (1<<5) //32
#define DEBUG_VSYNC (1<<6) //64
#define DEBUG_WRITEFRAME (1<<7) //128
#define DEBUG_WRITEFB (1<<8) //256
#define DEBUG_BLANKST (1<<9) //512
#define DEBUG_DUMP_DECODEDFRAME (1<<10) //1024
#define DEBUG_DUMP_FRAMEBUFFER (1<<11) //2048
#define DEBUG_FRAME_CTRL (1<<12) //4096
#define DEBUG_QUEUE_ST (1<<13) //8192
#define DEBUG_SAVE_WRITEBUFFER_TO_FILE (1<<14) //16384

void printUsage(void)
{
    printf("\n\n");
    printf("Usage:\n");
    printf("\t./testapp-debug [OPTION] [CMD] [VALUE]\n");
    printf("[OPTION]\n");
    printf("\t-d: Display Debug ...... (Default: disable)\n");
    printf("\t-i: IPC Debug ...... (Default: disable)\n\n");
    printf("[CMD] [VALUE]\n");
    printf("\tDisplay Debug:\n");
    printf("\t\t(a) VOWB processing time ...... (Checks if the vowb processing is bigger than 16.67ms)\n");
    printf("\t\t(b) Input status ...... (Shows input frame status)\n");
    printf("\t\t(c) Linked list status ...... (Shows the index of vowb linked list)\n");
    printf("\t\t(d) VOWB processing count ...... (Shows the amount of vowb processing item)\n");
    printf("\t\t(e) Frame Drop ...... (If Display drops frames, shows it)\n");
    printf("\t\t(f) Version ...... (Shows the version of NVRDaemon)\n");
    printf("\t\t(g) Vsync status ...... (Shows the HDMITX VSync status)\n");
    printf("\t\t(h) VOWB status ...... (Send a const frame to vowb instead of decoded frame)\n");
    printf("\t\t     ./testapp-debug [param]\n");
    printf("\t\t     [param]: bit[31..24]=>window id, bit[23..16]=>Y value, bit[15..8]=>U value, bit[7..0]=>V value\n");
    printf("\t\t     e.g. Send YUV ={0x10, 0x20, 0x30} to window 5\n");
    printf("\t\t          ./testapp-debug -d h 0x05102030\n");
    printf("\t\t     PS: Go back to normal display: ./testapp-debug -d 0\n");
    printf("\t\t(i) FB status ...... (Send a const frame to display frame buffer)\n");
    printf("\t\t     ./testapp-debug [param]\n");
    printf("\t\t     [param]: bit[31..24]=>enable, bit[23..16]=>R value, bit[15..8]=>G value, bit[7..0]=>B value\n");
    printf("\t\t     e.g. Send RGB ={0x40, 0x50, 0x60} to display FB\n");
    printf("\t\t          ./testapp-debug -d i 0x01405060\n");
    printf("\t\t(j) Blank status ...... (Shows blank status)\n");
    printf("\t\t(k) Dump decoded frame ...... (Dump decoded frame to yuv, default: /tmp/decFrm.yuv)\n");
    printf("\t\t     ./testapp-debug k [windowID] [path]\n");
    printf("\t\t     e.g. Dump windId 2 to /mnt/sda1/test.yuv\n");
    printf("\t\t          ./testapp-debug -d k 2 /mnt/sda1/test.yuv\n");
    printf("\t\t(l) Dump display FB ...... (Dump display frame buffer to yuv, default: /tmp/frmBuf.yuv)\n");
    printf("\t\t     ./testapp-debug l [path]\n");
    printf("\t\t     e.g. Dump frame buffer to /mnt/sda1/test.yuv\n");
    printf("\t\t          ./testapp-debug -d l /mnt/sda1/test.yuv\n");
    printf("\t\t(m) Frame control status ...... (Shows frame status: Drop/Normal/Repeat)\n");
    printf("\t\t(n) Queue status ...... (Shows wait queue status)\n");
    printf("\t\t(o) Save bistream...... (Save input bitstream to individual channel files)\n");
    printf("\t\t          ./testapp-debug -d o /mnt/sda1/dump/ \n");
    printf("\n\t\tExample:(Set display debug to option c)\n");
    printf("\t\t\t./testapp-debug -d c\n\n");
    printf("\tIPC Debug:\n");
    printf("\t\t[(r)eset/(e)nable/(d)isable] [ChannelID]......(Default value: 0)\n");
    printf("\n\t\tExample:(Enable IPC debug for channel 6)\n");
    printf("\t\t\t./testapp-debug -i e 6\n\n");
}


int htoi(char s[])
{
    int n = 0;
    int i = 0;
    int base = 10;

    while (s[i] != '\0' && s[i] != '\n')
    {
        if (s[i] == '0')
        {
            if (s[i+1] == 'x' || s[i+1] == 'X')
            {
                i+=2;
                base = 16;
            }
        }

        if (s[i] >= '0' && s[i] <= '9')
            n = n * base + (s[i] - '0');
        else if (base == 16 && s[i] >= 'a' && s[i] <= 'f')
            n = n * base + (s[i] - 'a') + 10;
        else if (base == 16 && s[i] >= 'A' && s[i] <= 'F')
            n = n * base + (s[i] - 'A') + 10;
        else
            return -1;

        ++i;
    }
    return n;
}

int main(int argc, char* argv[])
{
    int value = 0;
    unsigned int ipcEnable = 0;
    char path[512] = {0};
    unsigned int cmd = 0;


    if(argc<3)
    {
        goto printHowToUse;
    }

    if((strcmp(argv[1], "-d") == 0))
    {
        if((strcmp(argv[2], "a") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_TIME;
        }
        else if((strcmp(argv[2], "b") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_INPUT;
        }
        else if((strcmp(argv[2], "c") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_SHOWLIST;
        }
        else if((strcmp(argv[2], "d") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_VOWB;
        }
        else if((strcmp(argv[2], "e") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_FRMDROP;
        }
        else if((strcmp(argv[2], "f") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_VERSION;
        }
        else if((strcmp(argv[2], "g") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_VSYNC;
        }
        else if((strcmp(argv[2], "h") == 0))
        {
            if(argc>4)
                goto printHowToUse;
            else if(argc == 4)
                value = htoi(argv[3]);

            cmd = DEBUG_WRITEFRAME;
        }
        else if((strcmp(argv[2], "i") == 0))
        {
            if(argc>4)
                goto printHowToUse;
            else if(argc == 4)
                value = htoi(argv[3]);

            cmd = DEBUG_WRITEFB;
        }
        else if((strcmp(argv[2], "j") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_BLANKST;
        }
        else if((strcmp(argv[2], "k") == 0))
        {
            if(argc > 5 || argc == 3)
                goto printHowToUse;
            else if(argc == 5)
                strcpy(path, argv[4]);

            value = htoi(argv[3]);

            cmd = DEBUG_DUMP_DECODEDFRAME;
        }
        else if((strcmp(argv[2], "l") == 0))
        {
            if(argc>4)
                goto printHowToUse;
            else if(argc == 4)
                strcpy(path, argv[3]);

            cmd = DEBUG_DUMP_FRAMEBUFFER;
        }
        else if((strcmp(argv[2], "m") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_FRAME_CTRL;
        }
        else if((strcmp(argv[2], "n") == 0))
        {
            if(argc>=4)
                goto printHowToUse;

            cmd = DEBUG_QUEUE_ST;
        }
        else if((strcmp(argv[2], "o") == 0))
        {
            if(argc>4)
                goto printHowToUse;

            strcpy(path, argv[3]);
            cmd = DEBUG_SAVE_WRITEBUFFER_TO_FILE;
        }
        else
        {
            cmd = htoi(argv[2]);
            if(cmd == -1)
                goto printHowToUse;
            if(argc == 4)
            {
                value = htoi(argv[3]);
                if(value == -1)
                {
                    value = 0;
                    strcpy(path, argv[3]);
                }
            }
            else if(argc == 5)
            {
                value = htoi(argv[3]);
                strcpy(path, argv[4]);
            }
        }

        rtk_disp_set_debug(cmd, value, path);
        printf("Display debug cmd %d, value %d, path %s\n", cmd, value, path);
    }
    else if((strcmp(argv[1], "-i") == 0))
    {
        if(argc == 3 || argc > 4)
        {
            goto printHowToUse;
        }

        if((strcmp(argv[2], "r") == 0) || (strcmp(argv[2], "reset") == 0))
        {
            printf("IPC reset ch %d\n", htoi(argv[3]));
            rtk_ipc_debug_reset(atoi(argv[3]));
        }
        else
        {
            if((strcmp(argv[2], "e") == 0) || (strcmp(argv[2], "enable") == 0))
                ipcEnable = 1;
            else if((strcmp(argv[2], "d") == 0) || (strcmp(argv[2], "disable") == 0))
                ipcEnable = 0;
            else
            {
                goto printHowToUse;
            }

            printf("IPC %s debug ch %d\n", ipcEnable?"Enable":"Disable", htoi(argv[3]));
            rtk_ipc_debug_printInfo(htoi(argv[3]), ipcEnable);
        }
    }
    else
    {
        goto printHowToUse;
    }
    return 0;

printHowToUse:
    printUsage();
    return 0;
}
