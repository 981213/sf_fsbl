/*
 * Linker script for the preloader of Siflower SF21H8898/SF21A6826
 * Boot ROM uses the first 20K as its data/bss/stack, and load the
 * FSBL to 0x1c005000.
 *
 * Adapted from T-Head sample code. Original copyright:
 * 
 * Copyright 2018-2021 T-Head Semiconductor Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
MEMORY
{
	SRAM0(RWX)  : ORIGIN = 0x1c000000,  LENGTH = 0x5000
	SRAM1(RWX)  : ORIGIN = 0x1c005000,  LENGTH = 0xb000
}

ENTRY(_start)

SECTIONS {
    .text :
    {
        *(.text)
        *(.text*)
    } >SRAM1
    .rodata :
    {
      *(.rodata*)
       . = ALIGN(0x8);
        __erodata = .;
    } > SRAM1
    .data :
    {
      __data_start__ = .;
        . = ALIGN(0x8);
        *(.data*)
        *(.sdata*)
        *(.got*)
        __data_end__ = .;
        . = ALIGN(0x8);
    } >SRAM0 AT >SRAM1
    .bss :
    {
      __bss_start__ = .;
        . = ALIGN(0x8);
        *(.bss*)
        *(.sbss*)
        __bss_end__ = .;
        . = ALIGN(0x8);
          *.(COMMON)
    } >SRAM0
    .heap (COPY):
    {
      __end__ = .;
      end = __end__;
      *(.heap*)
      __HeapLimit = .;
    } >SRAM0

    _heap_start = .;
    .stack_dummy (COPY):
    {
      *(.stack*)
    } > SRAM0
    __StackTop = ORIGIN(SRAM0) + LENGTH(SRAM0);
    __StackLimit = __StackTop - SIZEOF(.stack_dummy);
    PROVIDE(__stack = __StackTop);
    ASSERT(__StackLimit >= __HeapLimit, "region RAM overflowed with stack")
}
