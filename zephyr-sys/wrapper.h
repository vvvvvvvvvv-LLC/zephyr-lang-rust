/*
 * Copyright (c) 2024 Linaro LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * This file is the seed point for bindgen.  This determines every header that will be visited for
 * binding generation.  It should include any Zephyr headers we need bindings for.  The driver in
 * build.rs will also select which functions need generation, which will determine the types that
 * are output.
 */

#ifdef RUST_BINDGEN
/* errno is coming from somewhere in Zephyr's build.  Add the symbol when running bindgen so that it
 * is defined here.
 */
extern int errno;
#endif

/* First, make sure we have all of our config settings. */
#include <zephyr/autoconf.h>

/* Gcc defines __SOFT_FP__ when the target uses software floating point, and the CMSIS headers get
 * confused without this.
 */
#if defined(CONFIG_CPU_CORTEX_M)
#if !defined(CONFIG_FP_HARDABI) && !defined(FORCE_FP_HARDABI) && !defined(__SOFTFP__)
#define __SOFTFP__
#endif
#endif

#include <zephyr/kernel.h>
#include <zephyr/kernel/thread_stack.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/bluetooth/bluetooth.h>

/*
 * bindgen will output #defined constant that resolve to simple numbers.  There are some symbols
 * that we want exported that, at least in some situations, are more complex, usually with a type
 * case.
 *
 * We'll use the prefix "ZR_" to avoid conflicts with other symbols.
 */
const uintptr_t ZR_STACK_ALIGN = Z_KERNEL_STACK_OBJ_ALIGN;
const uintptr_t ZR_STACK_RESERVED = K_KERNEL_STACK_RESERVED;

const uint32_t ZR_POLL_TYPE_SEM_AVAILABLE = K_POLL_TYPE_SEM_AVAILABLE;
const uint32_t ZR_POLL_TYPE_SIGNAL = K_POLL_TYPE_SIGNAL;
const uint32_t ZR_POLL_TYPE_DATA_AVAILABLE = K_POLL_TYPE_DATA_AVAILABLE;
