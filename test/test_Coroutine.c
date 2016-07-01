#include "unity.h"
#include "Coroutine.h"
#include "mock_MockFunction.h"
#include <malloc.h>
#include "Linklist.h"


#include "peripherals.h"
#include "Host.h"
#include "Registers.h"

void setUp(void)
{
 HostGpioA= malloc((sizeof(GPIO_TypeDef)));
}

void tearDown(void)
{
   free(HostGpioA);
   HostGpioA = NULL;
}

