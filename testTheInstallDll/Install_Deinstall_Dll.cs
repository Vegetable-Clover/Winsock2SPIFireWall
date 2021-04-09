using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Threading.Tasks;
using System.Runtime.InteropServices; //包含DllImport的using指令 

namespace testTheInstallDll
{

    public delegate Boolean DLLFunc_Install();

    public delegate Boolean DLLFunc_Deinstall();

    class Install_Deinstall_Dll
    {

        [DllImport(@"C:\mydll\InstallAndDeinstall.dll", EntryPoint = "Install", CallingConvention = CallingConvention.Cdecl)]

        public static extern Boolean Install();

        [DllImport(@"C:\mydll\InstallAndDeinstall.dll", EntryPoint = "Uninstall", CallingConvention = CallingConvention.Cdecl)]

        public static extern Boolean Uninstall();

        public static Boolean DLLFunc_Install()
        {
            return Install();
        }

        public static Boolean DLLFunc_Deinstall()
        {
            return Uninstall();
        }

    }


}
