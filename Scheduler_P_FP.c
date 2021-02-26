#include "Scheduler.h"
#include "Led.h"
#define DEBUGPORT P4OUT
static void ExecuteTask (Taskp t)
{
  /* ----------------------- INSERT CODE HERE ----------------------- */
  DEBUGPORT = 0x1;
  t->Invoked++;
  _EINT();
  t->Taskf(t->ExecutionTime); // execute task
  _DINT();
  DEBUGPORT = 0x9;
  /* ---------------------------------------------------------------- */

}

void Scheduler_P_FP (Task Tasks[])
{ 
  /* ----------------------- INSERT CODE HERE ----------------------- */
  // code willem

    // while loop omheen die net zo lang loopt tot SmallestTask 0 is
	uint8_t i = 0;
	uint16_t SmallestTask = 1;
	uint16_t SmallestTaskN = 0;
	Taskp t = &Tasks[i];
	while(SmallestTask !=0 )
    {
	    SmallestTask = 0;
        SmallestTaskN = 0;

        for (i = 0; i < NUMTASKS; i++)
        {
            t = &Tasks[i];
            if (t->Activated != t->Invoked) // kan zijn dat tar niet word herkent
            {
                if (SmallestTask == 0 || t->Period < SmallestTask)
                {
                    SmallestTaskN = i;
                    SmallestTask = t->Period;
                }
            }
        }
        t = &Tasks[SmallestTaskN];
        if (t->Activated != t->Invoked)
        {
            ExecuteTask(t);
        }
    }


	



  ///* Super simple, single task example */
  //Taskp t = &Tasks[0];
  //
  //if (t->Activated != t->Invoked)
  //{
  //  ExecuteTask(t);
  //}
  ///* End of example*/

  /* ---------------------------------------------------------------- */
}
