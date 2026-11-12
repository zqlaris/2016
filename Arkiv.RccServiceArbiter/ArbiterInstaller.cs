using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ServiceProcess;

namespace Arkiv.RccServiceArbiter
{
    [RunInstaller(true)]
    public class ArbiterInstaller : ServiceInstaller
    {
        public ArbiterInstaller()
        {
            ServiceName = "Arkiv.RccServiceArbiter";
            DisplayName = "Arkiv RccService Arbiter";
            Description = "Manages a handful of processes running the RCC web service.";
        }
    }
}
