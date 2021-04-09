using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace testTheInstallDll
{

    public partial class FormOfMain : Form
    {

        public FormOfMain()
        {
            InitializeComponent();
        }

        private void btn_install_Click(object sender, EventArgs e)
        {
            if (Install_Deinstall_Dll.DLLFunc_Install())
            {
                MessageBox.Show("安装成功");
            }
            else
            {
                MessageBox.Show("安装失败");
            }
        }

        private void btn2_deinstall_Click(object sender, EventArgs e)
        {
            if (Install_Deinstall_Dll.DLLFunc_Deinstall()){
                MessageBox.Show("卸载成功");
                this.ControlBox = true;
            }
            else
            {
                MessageBox.Show("卸载失败");
            }
            
        }

        private void btn_set_port_rule_Click(object sender, EventArgs e)
        {
            FormOfPort formOfPort = new FormOfPort();
            formOfPort.ShowDialog();

        }

        private void btn_set_url_rule_Click(object sender, EventArgs e)
        {
            FormOfUrl formOfUrl = new FormOfUrl();
            formOfUrl.ShowDialog();
        }
    }
}
