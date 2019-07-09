#include "ApexApi.h"
#include "datas/masterprinter.hpp"

int main()
{
    printer.AddPrinterFunction(reinterpret_cast<void*>(printf));

    IADF *hdr = IADF::Create("forearm_l_n.hrmeshc");
    //hdr->DumpDefinitions("forearm_l_n.xml");

    return 0;
}