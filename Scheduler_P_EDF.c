#include "Scheduler.h"
#include "Led.h"

static void ExecuteTask (Taskp t)
{
  /* insert code */
  t->Invoked++;
  _EINT();
  t->Taskf(t->ExecutionTime); // execute task
  _DINT();
  /* insert code */
}

void Scheduler_P_EDF (Task Tasks[])
{ 
  /* insert code */
  /* Use ExecuteTask function to execute a task */
  /* insert code */

  uint8_t i = 0;
	uint16_t EarliestDeadline = 1;
	uint16_t SmallestTaskN = 0;
	Taskp t = &Tasks[i];
	while(EarliestDeadline !=0 )
    {
	    EarliestDeadline = 0;
      SmallestTaskN = 0;

        for (i = 0; i < NUMTASKS; i++)
        {
            t = &Tasks[i];
            if (t->Activated != t->Invoked) // kan zijn dat tar niet word herkent
            {
                if (EarliestDeadline == 0 || t->NextRelease < EarliestDeadline)
                {
                    SmallestTaskN = i;
                    EarliestDeadline = t->NextRelease;
                }
            }
        }
        t = &Tasks[SmallestTaskN];
        if (t->Activated != t->Invoked)
        {
            ExecuteTask(t);
        }
    }

}
