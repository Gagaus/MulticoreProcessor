/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 
// Rodolfo editou aqui
//
const char *project_name="mips";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include <systemc.h>
#include "mips.H"
#include "memory.h"
#include "bus.h"
#include "off.h"


int sc_main(int ac, char *av[]) {
  //!  ISA simulator
  mips mips_proc0("mips");
  mips mips_proc1("mips_1");
  mips mips_proc2("mips_2");
  mips mips_proc3("mips_3");
  mips mips_proc4("mips_4");
  mips mips_proc5("mips_5");
  mips mips_proc6("mips_6");
  mips mips_proc7("mips_7");
  //! Bus
  ac_tlm_bus bus("bus");
  // Memory
  ac_tlm_mem mem("mem");
  // OFF
  ac_tlm_off off("off");

#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
#endif 

  mips_proc0.DM_port(bus.target_export);
  mips_proc1.DM_port(bus.target_export);
  mips_proc2.DM_port(bus.target_export);
  mips_proc3.DM_port(bus.target_export);
  mips_proc4.DM_port(bus.target_export);
  mips_proc5.DM_port(bus.target_export);
  mips_proc6.DM_port(bus.target_export);
  mips_proc7.DM_port(bus.target_export);
  bus.MEM_port(mem.target_export);
  bus.OFF_port(off.target_export);

  int ac_aux = ac;
  char av_aux[2][100];
  strcpy(av_aux[0], av[0]);
  strcpy(av_aux[1], av[1]);

  mips_proc0.init(ac, av);

  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc1.init(ac, av);
  
  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc2.init(ac, av);
  
  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc3.init(ac, av);
  
  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc4.init(ac, av);
  
  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc5.init(ac, av);
  
  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc6.init(ac, av);
  
  ac = ac_aux; 
  strcpy(av[0], av_aux[0]);
  strcpy(av[1], av_aux[1]);
  printf("%s %s\n", av[0], av[1]);
  mips_proc7.init(ac, av);
  
  procPointer(&mips_proc0, 0);
  procPointer(&mips_proc1, 1);
  procPointer(&mips_proc2, 2);
  procPointer(&mips_proc3, 3);
  procPointer(&mips_proc4, 4);
  procPointer(&mips_proc5, 5);
  procPointer(&mips_proc6, 6);
  procPointer(&mips_proc7, 7);
  cerr << endl;
  
  mips_proc1.ISA.PauseProcessor();
  mips_proc2.ISA.PauseProcessor();
  mips_proc3.ISA.PauseProcessor();
  mips_proc4.ISA.PauseProcessor();
  mips_proc5.ISA.PauseProcessor();
  mips_proc6.ISA.PauseProcessor();
  mips_proc7.ISA.PauseProcessor();
  
  sc_start();
  
  mips_proc0.PrintStat();
  mips_proc1.PrintStat();
  mips_proc2.PrintStat();
  mips_proc3.PrintStat();
  mips_proc4.PrintStat();
  mips_proc5.PrintStat();
  mips_proc6.PrintStat();
  mips_proc7.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  mips1_proc0.ac_sim_stats.time = sc_simulation_time();
  mips1_proc0.ac_sim_stats.print();
  mips1_proc1.ac_sim_stats.time = sc_simulation_time();
  mips1_proc1.ac_sim_stats.print();
  mips1_proc2.ac_sim_stats.time = sc_simulation_time();
  mips1_proc2.ac_sim_stats.print();
  mips1_proc3.ac_sim_stats.time = sc_simulation_time();
  mips1_proc3.ac_sim_stats.print();
  mips1_proc4.ac_sim_stats.time = sc_simulation_time();
  mips1_proc4.ac_sim_stats.print();
  mips1_proc5.ac_sim_stats.time = sc_simulation_time();
  mips1_proc5.ac_sim_stats.print();
  mips1_proc6.ac_sim_stats.time = sc_simulation_time();
  mips1_proc6.ac_sim_stats.print();
  mips1_proc7.ac_sim_stats.time = sc_simulation_time();
  mips1_proc7.ac_sim_stats.print();
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return mips_proc1.ac_exit_status;
}
