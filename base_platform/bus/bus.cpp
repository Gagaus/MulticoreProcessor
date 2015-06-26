/**
 * @file      memory.cpp
 * @author    Bruno de Carvalho Albertini
 *
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "bus.h"

//////////////////////////////////////////////////////////////////////////////

mips* proc0, *proc1, *proc2, *proc3, *proc4, *proc5, *proc6, *proc7;

/// Constructor
ac_tlm_bus::ac_tlm_bus(sc_module_name module_name):
  sc_module(module_name),
  target_export("iport"),
  MEM_port("MEM_port", 5242880U) // This is the memory port, assigned for 5MB
{
    /// Binds target_export to the memory
    target_export(*this);

}

/// Destructor
ac_tlm_bus::~ac_tlm_bus() 
{
}

void procPointer(mips* procx, int id){
    if (id == 0) 
        proc0 = procx;
    else if (id == 1)
        proc1 = procx;
    else if (id == 2)
        proc2 = procx;
    else if (id == 3)
        proc3 = procx;
    else if (id == 4)
        proc4 = procx;
    else if (id == 5)
        proc5 = procx;
    else if (id == 6)
        proc6 = procx;
    else if (id == 7)
        proc7 = procx;
}

/** Mensagens aos processadores sao da seguinte forma:
 * 0x7000xx == Pause o processador xx / 4
 * 0x7010xx == Resume o processador xx/4
 * */

/// This is the transport method. Everything should go through this file.
/// To connect more components, you will need to have an if/then/else or a switch
/// statement inside this method. Notice that ac_tlm_req has an address field.
ac_tlm_rsp ac_tlm_bus::transport(const ac_tlm_req &request) 
{
    ac_tlm_rsp response;
    if (request.addr < 5242880U)
        response = MEM_port->transport(request);
    else if (request.addr == 0x700000){
        proc0->ISA.PauseProcessor();
    }
    else if (request.addr == 0x701000){
        proc0->ISA.ResumeProcessor();
    }
    else if (request.addr == 0x700000 + 1*4){
        proc1->ISA.PauseProcessor();
        
    }
    else if (request.addr == 0x701000  + 1*4){ 
        proc1->ISA.ResumeProcessor();
        
    }
    else if (request.addr == 0x700000 + 2*4){
        proc2->ISA.PauseProcessor();
        
    }
    else if (request.addr == 0x701000 + 2*4){ 
        proc2->ISA.ResumeProcessor();        
    }
    else if (request.addr == 0x700000 + 3*4){
        proc3->ISA.PauseProcessor();
        
    }
    else if (request.addr == 0x701000 + 3*4){  
        proc3->ISA.ResumeProcessor();        
    }
    else if (request.addr == 0x700000 + 4*4){ 
        proc4->ISA.PauseProcessor();
        
    }
    else if (request.addr == 0x701000 + 4*4){   
        proc4->ISA.ResumeProcessor();        
    }
    else if (request.addr == 0x700000 + 5*4){ 
        proc5->ISA.PauseProcessor();
    }
    else if (request.addr == 0x701000 + 5*4){ 
        proc5->ISA.ResumeProcessor();        
    }
    else if (request.addr == 0x700000 + 6*4){ 
        proc6->ISA.PauseProcessor();
        
    }
    else if (request.addr == 0x701000 + 6*4){  
        proc6->ISA.ResumeProcessor();        
    }
    else if (request.addr == 0x700000 + 7*4){
        proc7->ISA.PauseProcessor();
        
    }
    else if (request.addr == 0x701000 + 7*4){ 
        proc7->ISA.ResumeProcessor();        
    }
    
    return response;
}
