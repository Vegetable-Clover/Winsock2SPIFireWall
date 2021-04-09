using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace testTheInstallDll
{
    class WriteReadHelper
    {

        private WriteReadHelper()
        {

        }

        private static string filePath = string.Empty;

        private static List<string> readDataSet = null;

        private static List<string> writeDataSet = null;

        public static void setReadDataSet(List<string> readDataSet)
        {
            WriteReadHelper.readDataSet = readDataSet;
        }

        public static void setWriteDataSet(List<string> writeDataSet)
        {
            WriteReadHelper.writeDataSet = writeDataSet;
        }

        public static void setFilePath(string filePath)
        {
            WriteReadHelper.filePath = filePath;
        }


        public static void ReadFromFile()
        {
            try
            {
                Read();
            }
            catch (Exception e)
            {
                throw e;
            }
        }

        public static void WriteIntoFile()
        {
            try
            {
                Write();
            }
            catch (Exception e)
            {
                throw e;
            }
        }


        private static void Read()
        {
            try
            {
                // 创建一个 StreamReader 的实例来读取文件 
                // using 语句也能关闭 StreamReader
                using (StreamReader sr = new StreamReader(filePath))
                {
                    string line;
                    // 从文件读取并显示行，直到文件的末尾 
                    while ((line = sr.ReadLine()) != null)
                    {
                        readDataSet.Add(line);
                        //Console.WriteLine(line);
                    }
                }
            }
            catch (Exception e)
            {
                // 向用户显示出错消息
                //Console.WriteLine("The file could not be read:");
                //Console.WriteLine(e.Message);
                throw e;
            }
        }

        private static void Write()
        {
            using (StreamWriter sw = new StreamWriter(filePath, false))
            {
                try
                {
                    writeDataSet.ForEach(x => {
                        sw.WriteLine(x);
                    });
                    //sw.WriteLine("127.0.0.2");
                }
                catch (Exception e)
                {
                    throw e;
                }
            }
        }

    }
}
