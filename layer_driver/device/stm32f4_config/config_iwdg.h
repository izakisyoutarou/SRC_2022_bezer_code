#ifdef STM32F405RG
#ifndef CONFIG_IWDG_H
#define CONFIG_IWDG_H

#ifdef __cplusplus
 extern "C" {
#endif

int Init_watchdog();
void watchdog_reset();


#ifdef __cplusplus
}
#endif


#endif
#endif//STM32F405RG
