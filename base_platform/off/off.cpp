//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "off.h"

//////////////////////////////////////////////////////////////////////////////


/// Constructor
ac_tlm_off::ac_tlm_off( sc_module_name module_name , int k ) :
  sc_module( module_name ),
  target_export("iport")
{
    target_export( *this );

}

/// Destructor
ac_tlm_off::~ac_tlm_off() {
  
}

ac_tlm_rsp_status ac_tlm_off::writem( const uint32_t &a , const uint32_t &d )
{
  // seu codigo aqui
  return SUCCESS;
}





