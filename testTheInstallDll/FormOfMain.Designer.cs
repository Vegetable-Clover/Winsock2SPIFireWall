namespace testTheInstallDll
{
    partial class FormOfMain
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_install = new System.Windows.Forms.Button();
            this.btn2_deinstall = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btn_set_exe_rule = new System.Windows.Forms.Button();
            this.btn_set_url_rule = new System.Windows.Forms.Button();
            this.btn_set_port_rule = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_install
            // 
            this.btn_install.Location = new System.Drawing.Point(16, 20);
            this.btn_install.Name = "btn_install";
            this.btn_install.Size = new System.Drawing.Size(117, 30);
            this.btn_install.TabIndex = 0;
            this.btn_install.Text = "安装LSP";
            this.btn_install.UseVisualStyleBackColor = true;
            this.btn_install.Click += new System.EventHandler(this.btn_install_Click);
            // 
            // btn2_deinstall
            // 
            this.btn2_deinstall.Location = new System.Drawing.Point(16, 65);
            this.btn2_deinstall.Name = "btn2_deinstall";
            this.btn2_deinstall.Size = new System.Drawing.Size(117, 30);
            this.btn2_deinstall.TabIndex = 1;
            this.btn2_deinstall.Text = "卸载LSP";
            this.btn2_deinstall.UseVisualStyleBackColor = true;
            this.btn2_deinstall.Click += new System.EventHandler(this.btn2_deinstall_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_install);
            this.groupBox1.Controls.Add(this.btn2_deinstall);
            this.groupBox1.Location = new System.Drawing.Point(55, 26);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(158, 107);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设置";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btn_set_exe_rule);
            this.groupBox2.Controls.Add(this.btn_set_url_rule);
            this.groupBox2.Controls.Add(this.btn_set_port_rule);
            this.groupBox2.Location = new System.Drawing.Point(255, 26);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(182, 211);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "过滤规则";
            // 
            // btn_set_exe_rule
            // 
            this.btn_set_exe_rule.Location = new System.Drawing.Point(22, 149);
            this.btn_set_exe_rule.Name = "btn_set_exe_rule";
            this.btn_set_exe_rule.Size = new System.Drawing.Size(130, 40);
            this.btn_set_exe_rule.TabIndex = 2;
            this.btn_set_exe_rule.Text = "设置EXE规则";
            this.btn_set_exe_rule.UseVisualStyleBackColor = true;
            // 
            // btn_set_url_rule
            // 
            this.btn_set_url_rule.Location = new System.Drawing.Point(22, 84);
            this.btn_set_url_rule.Name = "btn_set_url_rule";
            this.btn_set_url_rule.Size = new System.Drawing.Size(130, 40);
            this.btn_set_url_rule.TabIndex = 1;
            this.btn_set_url_rule.Text = "设置URL规则";
            this.btn_set_url_rule.UseVisualStyleBackColor = true;
            this.btn_set_url_rule.Click += new System.EventHandler(this.btn_set_url_rule_Click);
            // 
            // btn_set_port_rule
            // 
            this.btn_set_port_rule.Location = new System.Drawing.Point(22, 20);
            this.btn_set_port_rule.Name = "btn_set_port_rule";
            this.btn_set_port_rule.Size = new System.Drawing.Size(130, 40);
            this.btn_set_port_rule.TabIndex = 0;
            this.btn_set_port_rule.Text = "设置端口规则";
            this.btn_set_port_rule.UseVisualStyleBackColor = true;
            this.btn_set_port_rule.Click += new System.EventHandler(this.btn_set_port_rule_Click);
            // 
            // FormOfMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(462, 270);
            this.ControlBox = false;
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "FormOfMain";
            this.Text = "个人防火墙";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_install;
        private System.Windows.Forms.Button btn2_deinstall;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btn_set_exe_rule;
        private System.Windows.Forms.Button btn_set_url_rule;
        private System.Windows.Forms.Button btn_set_port_rule;
    }
}

