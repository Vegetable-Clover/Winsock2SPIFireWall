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
    public partial class FormOfPort : Form
    {
        private List<string> ruleList;

        string filepath = @"C:\mydll\Comm\Port.txt";

        public FormOfPort()
        {
            InitializeComponent();
        }

        private void FormOfPort_Load(object sender, EventArgs e)
        {
            ruleList = new List<string>();
            WriteReadHelper.setFilePath(filepath);
            try
            {
                WriteReadHelper.setReadDataSet(ruleList);
                WriteReadHelper.ReadFromFile();
                //MessageBox.Show("读取完成！");
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            if(ruleList.Count != 0)
            {
                lstOfPortRule.DataSource = ruleList;
                //lstOfPortRule.DisplayMember = "Sign";
            }
            lstOfPortRule.SelectedIndex = -1;
            
        }

        private void btn_port_delete_Click(object sender, EventArgs e)
        {
            string temp_port = lstOfPortRule.SelectedItem.ToString();
            ruleList.RemoveAt(ruleList.IndexOf(temp_port));
            RefleshTheListBox();
            if(ruleList.Count == 0)
            {
                btn_port_delete.Enabled = false;
            }

        }

        private void lstOfPortRule_MouseClick(object sender, MouseEventArgs e)
        {
            if(((ListBox)sender).SelectedIndex != -1)
            {
                btn_port_delete.Enabled = true;
            }
            else
            {
                btn_port_delete.Enabled = false;
            }
        }

        private void RefleshTheListBox()
        {
            lstOfPortRule.DataSource = null;
            lstOfPortRule.DataSource = ruleList;
            //lstOfPortRule.DisplayMember = "Sign";
        }

        private void btn_port_add_Click(object sender, EventArgs e)
        {
            bool eye = true;
            try
            {
                if (txt_port_Input.Text.Trim() == string.Empty)
                {
                    MessageBox.Show("端口输入不可为空！");
                    return;
                }
                string port = txt_port_Input.Text.Trim();
                ruleList.ForEach(item =>
                {
                    if(item == port)
                    {
                        eye = false;
                    }
                });
                if (eye)
                {
                    ruleList.Add(port);
                    RefleshTheListBox();
                    lstOfPortRule.SelectedIndex = -1;
                }
                else
                {
                    MessageBox.Show("端口已存在", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("请输入正确的端口号", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txt_port_Input.Text = string.Empty;
            }
        }

        private void btn_load_ruleOfPort_Click(object sender, EventArgs e)
        {
            WriteReadHelper.setFilePath(filepath);
            try
            {
                WriteReadHelper.setWriteDataSet(ruleList);
                WriteReadHelper.WriteIntoFile();
                MessageBox.Show("导入成功！");
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
