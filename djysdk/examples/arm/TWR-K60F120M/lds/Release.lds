ENTRY(Load_Preload)

INCLUDE  ..\lds\memory.lds

/*��ͬ��make�����ļ�·����ʾ��ʽ���ǲ�ͬ�ģ���������ļ���д��Ҫ��Ӧ�޸�*/
/*��ȷ��д�����ɲο�console�������������*/
SECTIONS
{
    Iboot_RevRam :
    {
        g_cIbootFlag = .;      /*�ַ���������c�п��ã������жϽ���APP����Iboot*/
    }>BootFlagRAM1
    
    Iboot_AppCtrl :
    {
        gc_ptIbootCtrl = .;   /*�ṹ������c�п��ã����ڼ��APP��ȷ��*/
    }>AppCtlRom
    
    Iboot_AppInfo :
    {
        gc_ptAppInfo = .;   
        LONG( . + 256);
        gc_AppSize = .;          /*ROM�� �洢APP��bin�ļ���С */
        LONG(pProgRomEnd - gc_AppSize + 4); /* APP��bin�ļ���С */
    }>AppVerfyRom
    
    Iboot_AppStart :
    {
        gc_AppAddr = .;         /*����ָ�������ָ��APP����ʼ��ַ*/
    }>AppRom
    
    stack_rRAM1_lRAM1 (NOLOAD) :
    {
        . = ALIGN(0x08);
        msp_bottom = .;
        KEEP(* (.data.InitStack))
        msp_top = ALIGN(0x08);
    }>RAM1 

    text_startup_rAppRom_lAppRom :
    {
       . = ALIGN(0x08);
        KEEP(*liblibOS_twrk60_o2.a:pre_loader.o (.text .text.Load_Preload))
        KEEP(*liblibOS_twrk60_o2.a:pre_loader.o (.text .text.* .rodata .rodata.*))
    }>AppRom

    text_preload_rAppRom_lAppRom :
    {
       . = ALIGN(0x08);
        g_pAppCodeStartRamAddr = .;
        *liblibOS_twrk60_o2.a:loader.o (.text .text.* .rodata .rodata.*)
        *liblibOS_twrk60_o2.a:int_hard.o (.text .text.* .rodata .rodata.*) 
        KEEP(*liblibOS_twrk60_o2.a:hard-exps.o (.text .text.* .rodata .rodata.*)) 
        *liblibOS_twrk60_o2.a:hard-exp.o (.text .text.* .rodata .rodata.*)
        *liblibOS_twrk60_o2.a:int.o (.text .text.* .rodata .rodata.*)
        *liblibOS_twrk60_o2.a:ints.o (.text .text.* .rodata .rodata.*)
        *src/critical/*.o (.text .text.* .rodata .rodata.*)
        *liblibOS_twrk60_o2.a:heap-static.o (.text .text.* .rodata .rodata.*)
        *liblibOS_twrk60_o2.a:list.o (.text .text.* .rodata .rodata.*)
    }>AppRom
    
    text_sysload_rAppRom_lAppRom :
    {
       . = ALIGN(0x08);
        * (.text .text.* .rodata .rodata.*)  
        g_pAppCodeEndRamAddr = .;
    }>AppRom

    rw_preload_rRAM1_lAppRom :
    {
       . = ALIGN(0x08);
        *liblibOS_twrk60_o2.a:loader.o (.data .data.*)
        *liblibOS_twrk60_o2.a:int_hard.o (.data .data.*)
        KEEP(*liblibOS_twrk60_o2.a:hard-exps.o (.data .data.*))
        *liblibOS_twrk60_o2.a:hard-exp.o (.data .data.*)
        *liblibOS_twrk60_o2.a:int.o (.data .data.*)
        *liblibOS_twrk60_o2.a:ints.o (.data .data.*)
        *src/critical/*.o (.data .data.*)
        *liblibOS_twrk60_o2.a:heap-static.o (.data .data.*)
        *liblibOS_twrk60_o2.a:list.o (.data .data.*)
    }>RAM1 AT>AppRom

    zi_preload_rRAM1_lRAM1 (NOLOAD) :
    {
       . = ALIGN(0x100);
        KEEP(* (.table.exceptions .table.exceptions.*))
        KEEP(* (.table.vectors .table.vectors.*))
        *liblibOS_twrk60_o2.a:loader.o (.bss .bss.* COMMON)
        *liblibOS_twrk60_o2.a:int_hard.o (.bss .bss.* COMMON)
        KEEP(*liblibOS_twrk60_o2.a:hard-exps.o (.bss .bss.* COMMON))
        *liblibOS_twrk60_o2.a:hard-exp.o (.bss .bss.* COMMON)
        *liblibOS_twrk60_o2.a:int.o (.bss .bss.* COMMON)
        *liblibOS_twrk60_o2.a:ints.o (.bss .bss.* COMMON)
        *src/critical/*.o (.bss .bss.* COMMON)
        *liblibOS_twrk60_o2.a:heap-static.o (.bss .bss.* COMMON)
        *liblibOS_twrk60_o2.a:list.o (.bss .bss.* COMMON)
    }>RAM1

     rw_sysload_rRAM1_lAppRom :
    {
       . = ALIGN(0x08);
        * (.data .data.*)
    }>RAM1 AT>AppRom

    zi_sysload_rRAM1_lRAM1 (NOLOAD) :
    {
       . = ALIGN(0x08);
        * (.bss .bss.* COMMON)
    }>RAM1

    preload_cp_table :
    {
       . = ALIGN(0x08);
        preload_copy_table = .;
        LONG(16)
        LONG(3)

        LONG(LOADADDR(text_preload_rAppRom_lAppRom))
        LONG(ADDR(text_preload_rAppRom_lAppRom))
        LONG(SIZEOF(text_preload_rAppRom_lAppRom))
        LONG(1)

        LONG(LOADADDR(rw_preload_rRAM1_lAppRom))
        LONG(ADDR(rw_preload_rRAM1_lAppRom))
        LONG(SIZEOF(rw_preload_rRAM1_lAppRom))
        LONG(1)

        LONG(LOADADDR(zi_preload_rRAM1_lRAM1))
        LONG(ADDR(zi_preload_rRAM1_lRAM1))
        LONG(SIZEOF(zi_preload_rRAM1_lRAM1))
        LONG(0)
    }>AppRom

    sysload_cp_table :
    {
       . = ALIGN(0x08);
        sysload_copy_table = .;
        LONG(16)
        LONG(3)

        LONG(LOADADDR(text_sysload_rAppRom_lAppRom))
        LONG(ADDR(text_sysload_rAppRom_lAppRom))
        LONG(SIZEOF(text_sysload_rAppRom_lAppRom))
        LONG(1)

        LONG(LOADADDR(rw_sysload_rRAM1_lAppRom))
        LONG(ADDR(rw_sysload_rRAM1_lAppRom))
        LONG(SIZEOF(rw_sysload_rRAM1_lAppRom))
        LONG(1)

        LONG(LOADADDR(zi_sysload_rRAM1_lRAM1))
        LONG(ADDR(zi_sysload_rRAM1_lRAM1))
        LONG(SIZEOF(zi_sysload_rRAM1_lRAM1))
        LONG(0)
    }>AppRom

    heap_rRAM1_lRAM1 (NOLOAD) :
    {
       . = ALIGN(0x08);
        sys_heap_bottom = .;
    }>RAM1   
    sys_heap_top = 0x1FFF0000+128k-16;

    heap_cp_table :
    {
       . = ALIGN(0x08);
        pHeapList = .;

/* Ĭ�϶ѣ���������λ�����ֱ����ǡ�sys�� */
        LONG(2)                     /*��ʾ�ö��������ڴ����*/
        LONG(0)                     /*�ö��Ϸ�����ڴ�Ķ���ߴ磬0��ʾʹ��ϵͳ����*/
        LONG(0)                     /*0=ͨ�ö�,1=ר�ö�,���ϵͳֻ��Ψһһ����,��ֻ����ͨ�ö�*/
        LONG(sys_heap_bottom)       /*��һ�λ�ַ������϶���Ҫ��*/
        LONG(sys_heap_top)          /*��һ�ε�ַ���ޣ�������������϶���Ҫ��*/
        LONG(32)                    /*��һ��ҳ�ߴ�=32bytes*/
        LONG(msp_bottom)            /*�ڶ��λ�ַ�����ճ�ʼ��ջ������϶���Ҫ��*/
        LONG(msp_top - 1024)         /*�ڶ��ε�ַ���ޣ���������1024�������ж�ʹ�õģ�����϶���Ҫ��*/
        LONG(24)                    /*�ڶ���ҳ�ߴ�=24bytes*/
        BYTE(0x73)                  /*'s'*/
        BYTE(0x79)                  /*'y'*/
        BYTE(0x73)                  /*'s'*/
        BYTE(0)                     /*��������"sys"�Ƕѵ�����*/

        . = ALIGN(0x04);
        LONG(0)                     /*������־*/
    }>AppRom
    
    rom_prog_end :
    {
       . = ALIGN(0x04);
        pProgRomEnd = .;
    }>AppRom 
}
/**** The End ****/