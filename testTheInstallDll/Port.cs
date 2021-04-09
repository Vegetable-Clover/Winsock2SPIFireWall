using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;
using System.Threading.Tasks;

namespace testTheInstallDll
{
    class Port
    {
        private int num;

        public int Num
        {
            get
            {
                return num;
            }
            set
            {
                num = value;
            }
        }

        private string sign;

        public string Sign
        {
            get
            {
                return ToString();
            }
        }

        public Port(string port)
        {
            num = Convert.ToInt32(port);
        }

        public Port(int port)
        {
            num = port;
        }

        public override string ToString()
        {
            return "已禁用端口号： " + num;
        }
    }
}
