using System;
using System.Collections.Generic;
using System.ServiceModel;
using System.Text;
using System.Diagnostics;

namespace Arkiv.RccServiceArbiter
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single, ConcurrencyMode = ConcurrencyMode.Multiple)]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "3.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(Namespace = "http://arkiv.com/", ConfigurationName = "RCCServiceSoap")]
    [System.ServiceModel.XmlSerializerFormat(Style=OperationFormatStyle.Document, Use=OperationFormatUse.Literal)]
    class RccService : Arkiv.Grid.Rcc.Server.RCCServiceSoap
    {
        private JobManager jobManager;

        public RccService()
        {
            jobManager = new JobManager();
        }
        public void initializeJobManager()
        {
            jobManager.initialize();
        }
        #region Converters


        private static Arkiv.Grid.Rcc.Job convert(Arkiv.Grid.Rcc.Server.Job job)
        {
            Arkiv.Grid.Rcc.Job result = new Arkiv.Grid.Rcc.Job();
            result.id = job.id;
            result.category = job.category;
            result.cores = job.cores;
            result.expirationInSeconds = job.expirationInSeconds;
            return result;
        }
        private static Arkiv.Grid.Rcc.Server.Job convert(Arkiv.Grid.Rcc.Job job)
        {
            Arkiv.Grid.Rcc.Server.Job result = new Arkiv.Grid.Rcc.Server.Job();
            result.id = job.id;
            result.category = job.category;
            result.cores = job.cores;
            result.expirationInSeconds = job.expirationInSeconds;
            return result;
        }
        private static Arkiv.Grid.Rcc.LuaType convert(Arkiv.Grid.Rcc.Server.LuaType luaType)
        {
            switch (luaType)
            {
                case Arkiv.Grid.Rcc.Server.LuaType.LUA_TBOOLEAN: return Arkiv.Grid.Rcc.LuaType.LUA_TBOOLEAN;
                case Arkiv.Grid.Rcc.Server.LuaType.LUA_TNIL: return Arkiv.Grid.Rcc.LuaType.LUA_TNIL;
                case Arkiv.Grid.Rcc.Server.LuaType.LUA_TNUMBER: return Arkiv.Grid.Rcc.LuaType.LUA_TNUMBER;
                case Arkiv.Grid.Rcc.Server.LuaType.LUA_TSTRING: return Arkiv.Grid.Rcc.LuaType.LUA_TSTRING;
                case Arkiv.Grid.Rcc.Server.LuaType.LUA_TTABLE: return Arkiv.Grid.Rcc.LuaType.LUA_TTABLE;
            }
            throw new Exception("Unknown LuaType");
        }
        private static Arkiv.Grid.Rcc.Server.LuaType convert(Arkiv.Grid.Rcc.LuaType luaType)
        {
            switch (luaType)
            {
                case Arkiv.Grid.Rcc.LuaType.LUA_TBOOLEAN: return Arkiv.Grid.Rcc.Server.LuaType.LUA_TBOOLEAN;
                case Arkiv.Grid.Rcc.LuaType.LUA_TNIL: return Arkiv.Grid.Rcc.Server.LuaType.LUA_TNIL;
                case Arkiv.Grid.Rcc.LuaType.LUA_TNUMBER: return Arkiv.Grid.Rcc.Server.LuaType.LUA_TNUMBER;
                case Arkiv.Grid.Rcc.LuaType.LUA_TSTRING: return Arkiv.Grid.Rcc.Server.LuaType.LUA_TSTRING;
                case Arkiv.Grid.Rcc.LuaType.LUA_TTABLE: return Arkiv.Grid.Rcc.Server.LuaType.LUA_TTABLE;
            }
            throw new Exception("Unknown LuaType");
        }
        private static Arkiv.Grid.Rcc.LuaValue[] convert(Arkiv.Grid.Rcc.Server.LuaValue[] luaValues)
        {
            if (luaValues == null) return null;

            Arkiv.Grid.Rcc.LuaValue[] result = new Arkiv.Grid.Rcc.LuaValue[luaValues.Length];
            int i = 0;
            foreach (Arkiv.Grid.Rcc.Server.LuaValue luaValue in luaValues)
            {
                result[i++] = convert(luaValue);
            }
            return result;
        }
        private static Arkiv.Grid.Rcc.Server.LuaValue[] convert(Arkiv.Grid.Rcc.LuaValue[] luaValues)
        {
            if (luaValues == null) return null;

            Arkiv.Grid.Rcc.Server.LuaValue[] result = new Arkiv.Grid.Rcc.Server.LuaValue[luaValues.Length];
            int i = 0;
            foreach (Arkiv.Grid.Rcc.LuaValue luaValue in luaValues)
            {
                result[i++] = convert(luaValue);
            }
            return result;
        }


        private static Arkiv.Grid.Rcc.LuaValue convert(Arkiv.Grid.Rcc.Server.LuaValue luaValue)
        {
            Arkiv.Grid.Rcc.LuaValue result = new Arkiv.Grid.Rcc.LuaValue();
            result.type = convert(luaValue.type);
            result.value = luaValue.value;
            result.table = convert(luaValue.table);
            return result;
        }

        private static Arkiv.Grid.Rcc.Server.LuaValue convert(Arkiv.Grid.Rcc.LuaValue luaValue)
        {
            Arkiv.Grid.Rcc.Server.LuaValue result = new Arkiv.Grid.Rcc.Server.LuaValue();
            result.type = convert(luaValue.type);
            result.value = luaValue.value;
            result.table = convert(luaValue.table);
            return result;
        }


        private static Arkiv.Grid.Rcc.ScriptExecution convert(Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            Arkiv.Grid.Rcc.ScriptExecution result = new Arkiv.Grid.Rcc.ScriptExecution();
            result.name = script.name;
            result.script = script.script;
            result.arguments = convert(script.arguments);
            return result;
        }

        #endregion 

        private string ToString(Arkiv.Grid.Rcc.Server.LuaValue[] values)
        {
            string result = "";
            foreach (Arkiv.Grid.Rcc.Server.LuaValue value in values)
            {
                switch (value.type)
                {
                    case Arkiv.Grid.Rcc.Server.LuaType.LUA_TBOOLEAN:
                    case Arkiv.Grid.Rcc.Server.LuaType.LUA_TNUMBER:
                    case Arkiv.Grid.Rcc.Server.LuaType.LUA_TSTRING:
                        result += value.value + "\n";
                        break;
                    case Arkiv.Grid.Rcc.Server.LuaType.LUA_TNIL:
                        result += "[NIL]";
                        break;
                    case Arkiv.Grid.Rcc.Server.LuaType.LUA_TTABLE:
                        result += "{\n" + ToString(value.table) + "}\n";
                        break;
                }
            }
            return result;
        }
        public string GetStats(bool clearExceptions)
        {
            return jobManager.GetStats(clearExceptions);
        }

        public void SetMultiProcess(bool value)
        {
            jobManager.SetMultiProcess(value);
        }

        public void SetRecycleProcess(bool value)
        {
            jobManager.SetRecycleProcess(value);
        }
        public void SetRecycleProcessCount(int value)
        {
            jobManager.SetRecycleProcessCount(value);
        }



        public void SetThreadConfigScript(string script, bool broadcast)
        {
            jobManager.SetStartScript(script, broadcast);
        }

        #region RCCServiceSoap Members

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/HelloWorld", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override string HelloWorld()
        {
            if (Properties.Settings.Default.Verbose) Console.WriteLine("HelloWorld()");

            try
            {
                string result;
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.AnyJob(30))
                {
                    result = rccService.HelloWorld();
                }
                Log.Event("HelloWorld - Success");
                return result;
            }
            catch (Exception e)
            {
                Log.Event(String.Format("HelloWorld - Exception - {0}", e.Message));
                throw;
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/GetVersion", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override string GetVersion()
        {
            //if (Properties.Settings.Default.Verbose) Console.WriteLine("GetVersion()");
            using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.AnyJob(30))
            {
                return rccService.GetVersion();
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/OpenJob", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormat(Style = OperationFormatStyle.Document, Use = OperationFormatUse.Literal)]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] OpenJob(Arkiv.Grid.Rcc.Server.Job job, Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            System.Threading.ThreadPool.QueueUserWorkItem((dummy) =>
            {
                try
                {
                    OpenJobEx(job, script); 
                }
                catch (Exception ex)
                {
                    ExceptionHandler.LogException(ex);
                }
            });
            return null; 
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/OpenJobEx", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormat(Style = OperationFormatStyle.Document, Use = OperationFormatUse.Literal)]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] OpenJobEx(Arkiv.Grid.Rcc.Server.Job job, Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            try
            {
                if (Properties.Settings.Default.Verbose) Console.WriteLine("OpenJob(" + job.ToString() + ")");

                Console.WriteLine("OpenJobEx, script name: " + script.name);
                Arkiv.Grid.Rcc.Server.LuaValue[] finalResult;
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.NewJob(job.id, job.expirationInSeconds, "OpenJobEx"))
                {
                    //Create a new process, and have it execute this Job
                    Arkiv.Grid.Rcc.LuaValue[] result = rccService.OpenJob(convert(job), convert(script));
                    finalResult = convert(result);
                }

                Log.Event(String.Format("OpenJobEx('{0}', {1}, {2}) - Success", job.id, job.category, job.expirationInSeconds));
                return finalResult;
            }
            catch (Exception e)
            {
                Log.Event(String.Format("OpenJobEx('{0}', {1}, {2}) - Exception - {3}", job.id, job.category, job.expirationInSeconds, e.Message));
                throw;
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/BatchJob", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] BatchJob(Arkiv.Grid.Rcc.Server.Job job, Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            throw new Exception("BatchJob is deprecated, use BatchJobEx");
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/BatchJobEx", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] BatchJobEx(Arkiv.Grid.Rcc.Server.Job job, Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            try
            {
                if (Properties.Settings.Default.Verbose) Console.WriteLine("BatchJob(" + job.ToString() + ")");
                string jobId = "Batch" + job.id;
                Arkiv.Grid.Rcc.Server.LuaValue[] result;
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.NewJob(jobId, job.expirationInSeconds, "BatchJob"))
                {
                    try
                    {
                        result = convert(rccService.BatchJob(convert(job), convert(script)));
                    }
                    finally
                    {
                        jobManager.CloseJob(jobId);
                    }
                }
                Log.Event(String.Format("BatchJobEx('{0}', {1}, {2}) - Success", job.id, job.category, job.expirationInSeconds));
                return result;

            }
            catch (Exception e)
            {
                Log.Event(String.Format("BatchJobEx('{0}', {1}, {2}) - Exception - {3}", job.id, job.category, job.expirationInSeconds, e.Message));
                throw;
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/RenewLease", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override double RenewLease(string jobID, double expirationInSeconds)
        {
            System.Threading.ThreadPool.QueueUserWorkItem((dummy) =>
            {
                try
                {
                    RenewLeaseSync(jobID, expirationInSeconds);                    
                }
                catch (Exception ex)
                {
                    ExceptionHandler.LogException(ex);                        
                }
            });
            return 0;
        }
        private void RenewLeaseSync(string jobID, double expirationInSeconds)
        {
            try
            {
                if (Properties.Settings.Default.Verbose) Console.WriteLine("RenewLease(" + jobID + "," + expirationInSeconds + ")");
                jobManager.RenewLease(jobID, expirationInSeconds);
                double result;
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.GetJob(jobID, "RenewLease", ""))
                {
                    result = rccService.RenewLease(jobID, expirationInSeconds);
                }
                Log.Event(String.Format("RenewLease('{0}', {1}) - Success", jobID, expirationInSeconds));                
            }
            catch (Exception e)
            {
                Log.Event(String.Format("RenewLease('{0}', {1}) - Exception - {2}", jobID, expirationInSeconds, e.Message));
                throw;
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/Execute", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] Execute(string jobID, Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            throw new Exception("Execute is deprecated, use ExecuteEx");
        }
       
        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/ExecuteEx", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] ExecuteEx(string jobID, Arkiv.Grid.Rcc.Server.ScriptExecution script)
        {
            try
            {
                if (Properties.Settings.Default.Verbose) Console.WriteLine("Execute(" + jobID + ")");

                Arkiv.Grid.Rcc.Server.LuaValue[] finalResult;
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.GetJob(jobID, "ExecuteEx", script.script.Substring(0, Math.Min(30, script.script.Length))))
                {
                    Arkiv.Grid.Rcc.LuaValue[] result = rccService.Execute(jobID, convert(script));
                    finalResult = convert(result);
                }
                Log.Event(String.Format("ExecuteEx('{0}', {1}) - Success", jobID, script.name));
                return finalResult;
            }
            catch (Exception e)
            {
                Log.Event(String.Format("ExecuteEx('{0}', {1}) - Exception - {2}", jobID, script.name, e.Message));
                throw;
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/CloseJob", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override void CloseJob(string jobID)
        {
            System.Threading.ThreadPool.QueueUserWorkItem((dummy) =>
            {
                try
                {
                    CloseJobSync(jobID);
                }
                catch (Exception ex)
                {
                    ExceptionHandler.LogException(ex);
                }
            });            
        }
        
        public void CloseJobSync(string jobID)
        {
            try
            {
                if (Properties.Settings.Default.Verbose) Console.WriteLine("CloseJob(" + jobID + ")");
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.GetJob(jobID, "CloseJob", ""))
                {
                    rccService.CloseJob(jobID);
                }
            }
            catch (Exception e)
            {
                Log.Event(String.Format("CloseJob('{0}') - Exception - {1}", jobID, e.Message));
                throw;
            }
            finally
            {
                jobManager.CloseJob(jobID);
            }
            Log.Event(String.Format("CloseJob('{0}') - Success", jobID));
        }


        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/GetExpiration", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override double GetExpiration(string jobID)
        {
            if (Properties.Settings.Default.Verbose) Console.WriteLine("GetExpiration(" + jobID + ")");
            using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.GetJob(jobID, "GetExpiration", ""))
            {
                return rccService.GetExpiration(jobID);
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/Diag", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] Diag(int type, string jobID)
        {
            throw new Exception("Diag is deprecated, use DiagEx");
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/DiagEx", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.LuaValue[] DiagEx(int type, string jobID)
        {

            if (Properties.Settings.Default.Verbose) Console.WriteLine("Diag(" +    type + "," + jobID + ")");
            if (jobID != "")
            {
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.GetJob(jobID, "DiagEx", ""))
                {
                    return convert(rccService.Diag(type, jobID));
                }
            }
            else
            {
                using (Arkiv.Grid.Rcc.RCCServiceSoap rccService = jobManager.AnyJob(60))
                {
                    return convert(rccService.Diag(type, jobID));
                }
            }
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/GetStatus", ReplyAction = "http://arkiv.com/GetStatusResponse")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.Status GetStatus()
        {
            //if (Properties.Settings.Default.Verbose) Console.WriteLine("GetStatus()");
            Arkiv.Grid.Rcc.Server.Status result = new Arkiv.Grid.Rcc.Server.Status();
            result.environmentCount = 0;

            //Pick version from 1
            result.version = GetVersion();

            jobManager.DispatchRequest(delegate(Arkiv.Grid.Rcc.RCCServiceSoap rccService)
                {
                    //Call GetStatus on all dependent processes
                    Arkiv.Grid.Rcc.Status status = rccService.GetStatus();

                    //Ensure all have same version
                    Debug.Assert(status.version != result.version);

                    //Sum environmentCount from each process
                    result.environmentCount += status.environmentCount;
                });
            return result;
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/GetAllJobs", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.Job[] GetAllJobs()
        {
            throw new Exception("GetAllJobs is deprecated, use GetAllJobsEx");
        }


        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/GetAllJobsEx", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override Arkiv.Grid.Rcc.Server.Job[] GetAllJobsEx()
        {
            if (Properties.Settings.Default.Verbose) Console.WriteLine("GetAllJobs()");
            System.Collections.Generic.List<Arkiv.Grid.Rcc.Server.Job> result = new List<Arkiv.Grid.Rcc.Server.Job>();

            jobManager.DispatchRequest(delegate(Arkiv.Grid.Rcc.RCCServiceSoap rccService)
            {
                Arkiv.Grid.Rcc.Job[] jobs = rccService.GetAllJobs();
                foreach (Arkiv.Grid.Rcc.Job job in jobs)
                    result.Add(convert(job));
            });
            return result.ToArray();
    }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/CloseExpiredJobs", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override int CloseExpiredJobs()
        {
            if (Properties.Settings.Default.Verbose) Console.WriteLine("CloseExpiredJobs()");
            int result = 0;
            //Forward to all processes
            jobManager.DispatchRequest(delegate(Arkiv.Grid.Rcc.RCCServiceSoap rccService)
                {
                    result += rccService.CloseExpiredJobs();
                });

            return result;
        }

        [System.ServiceModel.OperationContractAttribute(Action = "http://arkiv.com/CloseAllJobs", ReplyAction = "*")]
        [System.ServiceModel.XmlSerializerFormatAttribute()]
        public override int CloseAllJobs()
        {
            if (Properties.Settings.Default.Verbose) Console.WriteLine("CloseAllJobs()");
            int result = 0;
            //Forward to all processes
            jobManager.DispatchRequest(delegate(Arkiv.Grid.Rcc.RCCServiceSoap rccService)
                {
                    result += rccService.CloseAllJobs();
                });

            return result;
        }        
        #endregion
    }
}
