/** \file
  \brief Профайлер кода на основе макросов . <br><br>


Пример использования:
\code

#include <gb/base/macroprofiler.h>

int main()
{

// после это макроса следует проверяемый код.
// Он будет выполняться в цикле многократным повторением  10000000 раз.
// Поправочный коэф. будет 3 наносекунды
GB_MACROPROFILE_BEGIN(10000000,3.0)

	//  далее следует проверяемый код  ...
	float f1 =  4545.454f; float fg = sin(f1*0.45f) + cos(f1*1.124f);

// завершение кода.
GB_MACROPROFILE_END


	return 0;
}

\endcode

Количество итерраций  следуе выбирать таким образом, чтобы время ожидания было 1-2 секунды.
Если меньше , то снижается точность, если выше, тогда долгое ожидание.




*/

#pragma once

#include <time.h> 
#include <math.h>
#include <conio.h>
#include <ostream>
#include <iostream>
#include <string>


#ifdef _MSC_VER 
#pragma warning( disable : 4996 )
#endif 


/** \brief    Начало кода, время выполнения которого требуется замерить.
  Парамертры макроса: сколько итераций выполнять  и  поправочный коэфициент,
	который будет вычитатьсяиз результата.  */
#define   GB_MACROPROFILE_BEGIN(num_iterrations,ksub_correction) \
	while(true)	{\
	std::cout << "\n\nBEGIN PROFILE   .........\n";\
	double g_gbprofvar_kSub_nanoseconds = (ksub_correction) ;  \
	size_t g_gbprofvar_numiterr =  (num_iterrations) ; \
	clock_t g_gbprofvar_tcurr_time = clock();\
	size_t  g_gbprofvar_count =0;\
	/* begin loop ... */ \
	while( g_gbprofvar_count < g_gbprofvar_numiterr ) { \



//! \brief  Завершение профайлируемого кода.
#define	  GB_MACROPROFILE_END \
	/* end loop. */ \
	g_gbprofvar_count++; }  \
	/* analize ... */  \
	double g_gbprofvar_time =  (double) (   clock() - g_gbprofvar_tcurr_time   );\
	g_gbprofvar_time   /= (double)CLOCKS_PER_SEC ;\
	g_gbprofvar_time  /= (double)g_gbprofvar_numiterr;\
	g_gbprofvar_time  *= 1000000000.0; \
	g_gbprofvar_time -=  g_gbprofvar_kSub_nanoseconds;\
	/* correction ...*/    \
	if (g_gbprofvar_time < 0.0) g_gbprofvar_time  = 0.0; \
	/* print result ...  */  \
	std::cout << "      Perfomance time = " << g_gbprofvar_time << " nanoseconds.\n" ; \
	std::cout << "END PROFILE. Press key ('Q' or Esc - break).     ...\n"; \
	char usr_res = getch(); \
	if(  (usr_res == 'Q') || (usr_res == 'q') ||(usr_res ==  27)  )   break; \
	/*  end .  */ \
	} \

