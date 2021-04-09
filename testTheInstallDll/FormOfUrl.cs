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
    public partial class FormOfUrl : Form
    {
        private List<string> ruleList;

        string filepath = @"C:\mydll\Comm\URL.txt";

        public FormOfUrl()
        {
            InitializeComponent();
        }

        private void FormOfUrl_Load(object sender, EventArgs e)
        {
            ruleList = new List<string>();
            WriteReadHelper.setFilePath(filepath);
            try
            {
                WriteReadHelper.setReadDataSet(ruleList);
                WriteReadHelper.ReadFromFile();
                //MessageBox.Show("读取完成！");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            if (ruleList.Count != 0)
            {
                lstOfUrlRule.DataSource = ruleList;
                //lstOfPortRule.DisplayMember = "Sign";
            }
            lstOfUrlRule.SelectedIndex = -1;
        }

        private void RefleshTheListBox()
        {
            lstOfUrlRule.DataSource = null;
            lstOfUrlRule.DataSource = ruleList;
            //lstOfUrlRule.DisplayMember = "Sign";
        }

        private void btn_url_add_Click(object sender, EventArgs e)
        {
            bool eye = true;
            try
            {
                if(txt_url_Input.Text.Trim() == string.Empty)
                {
                    MessageBox.Show("Url输入不可为空！");
                    return;
                }
                string url = txt_url_Input.Text.Trim();
                ruleList.ForEach(item =>
                {
                    if (item == url)
                    {
                        eye = false;
                    }
                });
                if (eye)
                {
                    ruleList.Add(url);
                    RefleshTheListBox();
                    lstOfUrlRule.SelectedIndex = -1;
                }
                else
                {
                    MessageBox.Show("Url已存在", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("请输入合适的Url", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txt_url_Input.Text = string.Empty;
            }
        }


        private void btn_url_delete_Click(object sender, EventArgs e)
        {
            string temp_port = lstOfUrlRule.SelectedItem.ToString();
            ruleList.RemoveAt(ruleList.IndexOf(temp_port));
            RefleshTheListBox();
            if (ruleList.Count == 0)
            {
                btn_url_delete.Enabled = false;
            }
        }

        private void btn_load_ruleOfUrl_Click(object sender, EventArgs e)
        {
            WriteReadHelper.setFilePath(filepath);
            try
            {
                WriteReadHelper.setWriteDataSet(ruleList);
                WriteReadHelper.WriteIntoFile();
                MessageBox.Show("导入成功！");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void lstOfUrlRule_MouseClick(object sender, MouseEventArgs e)
        {
            if (((ListBox)sender).SelectedIndex != -1)
            {
                btn_url_delete.Enabled = true;
            }
            else
            {
                btn_url_delete.Enabled = false;
            }
        }
    }
}
