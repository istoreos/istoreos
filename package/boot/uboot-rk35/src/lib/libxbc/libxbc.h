/*
 * Copyright (C) 2021 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBXBC_H_
#define LIBXBC_H_

// memcpy and strncmp
#include <common.h>

/*
 * Add a string of boot config parameters to memory appended by the trailer.
 * This memory needs to be immediately following the end of the ramdisks.
 * The new boot config trailer will be written to the end of the entire
 * parameter section(previous + new). The trailer contains a 4 byte size of the
 * parameters, followed by a 4 byte checksum of the parameters, followed by a 12
 * byte magic string.
 *
 * @param params pointer to string of boot config parameters
 * @param params_size size of params string in bytes
 * @param bootconfig_start_addr address that the boot config section is starting
 *        at in memory.
 * @param bootconfig_size size of the current bootconfig section in bytes.
 * @return number of bytes added to the boot config section. -1 for error.
 */
int addBootConfigParameters(char *params, uint32_t params_size,
                            uint64_t bootconfig_start_addr,
                            uint32_t bootconfig_size);

/*
 * Add the boot config trailer to the end of the boot config parameter section.
 * This can be used after the vendor bootconfig section has been placed into
 * memory if there are no additional parameters that need to be added.
 * The new boot config trailer will be written to the end of the entire
 * parameter section at (bootconfig_start_addr + bootconfig_size).
 * The trailer contains a 4 byte size of the parameters, followed by a 4 byte
 * checksum of the parameters, followed by a 12 byte magic string.
 *
 * @param bootconfig_start_addr address that the boot config section is starting
 *        at in memory.
 * @param bootconfig_size size of the current bootconfig section in bytes.
 * @return number of bytes added to the boot config section. -1 for error.
 */
int addBootConfigTrailer(uint64_t bootconfig_start_addr,
                         uint32_t bootconfig_size);

#endif /* LIBXBC_H_ */
