namespace testTheInstallDll
{
    partial class FormOfPort
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txt_port_Input = new System.Windows.Forms.TextBox();
            this.btn_port_add = new System.Windows.Forms.Button();
            this.lstOfPortRule = new System.Windows.Forms.ListBox();
            this.btn_port_delete = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_load_ruleOfPort = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // txt_port_Input
            // 
            this.txt_port_Input.Location = new System.Drawing.Point(147, 33);
            this.txt_port_Input.Name = "txt_port_Input";
            this.txt_port_Input.Size = new System.Drawing.Size(143, 21);
            this.txt_port_Input.TabIndex = 0;
            // 
            // btn_port_add
            // 
            this.btn_port_add.Location = new System.Drawing.Point(31, 20);
            this.btn_port_add.Name = "btn_port_add";
            this.btn_port_add.Size = new System.Drawing.Size(75, 23);
            this.btn_port_add.TabIndex = 1;
            this.btn_port_add.Text = "添加";
            this.btn_port_add.UseVisualStyleBackColor = true;
            this.btn_port_add.Click += new System.EventHandler(this.btn_port_add_Click);
            // 
            // lstOfPortRule
            // 
            this.lstOfPortRule.FormattingEnabled = true;
            this.lstOfPortRule.ItemHeight = 12;
            this.lstOfPortRule.Location = new System.Drawing.Point(90, 97);
            this.lstOfPortRule.Name = "lstOfPortRule";
            this.lstOfPortRule.Size = new System.Drawing.Size(252, 172);
            this.lstOfPortRule.TabIndex = 2;
            this.lstOfPortRule.MouseClick += new System.Windows.Forms.MouseEventHandler(this.lstOfPortRule_MouseClick);
            // 
            // btn_port_delete
            // 
            this.btn_port_delete.Enabled = false;
            this.btn_port_delete.Location = new System.Drawing.Point(31, 49);
            this.btn_port_delete.Name = "btn_port_delete";
            this.btn_port_delete.Size = new System.Drawing.Size(75, 23);
            this.btn_port_delete.TabIndex = 3;
            this.btn_port_delete.Text = "删除";
            this.btn_port_delete.UseVisualStyleBackColor = true;
            this.btn_port_delete.Click += new System.EventHandler(this.btn_port_delete_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(88, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "端口号：";
            // 
            // btn_load_ruleOfPort
            // 
            this.btn_load_ruleOfPort.Location = new System.Drawing.Point(31, 78);
            this.btn_load_ruleOfPort.Name = "btn_load_ruleOfPort";
            this.btn_load_ruleOfPort.Size = new System.Drawing.Size(75, 23);
            this.btn_load_ruleOfPort.TabIndex = 5;
            this.btn_load_ruleOfPort.Text = "导入规则";
            this.btn_load_ruleOfPort.UseVisualStyleBackColor = true;
            this.btn_load_ruleOfPort.Click += new System.EventHandler(this.btn_load_ruleOfPort_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_port_add);
            this.groupBox1.Controls.Add(this.btn_load_ruleOfPort);
            this.groupBox1.Controls.Add(this.btn_port_delete);
            this.groupBox1.Location = new System.Drawing.Point(372, 33);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(135, 116);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            // 
            // FormOfPort
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(538, 318);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lstOfPortRule);
            this.Controls.Add(this.txt_port_Input);
            this.Name = "FormOfPort";
            this.Text = "端口规则";
            this.Load += new System.EventHandler(this.FormOfPort_Load);
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_port_Input;
        private System.Windows.Forms.Button btn_port_add;
        private System.Windows.Forms.ListBox lstOfPortRule;
        private System.Windows.Forms.Button btn_port_delete;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_load_ruleOfPort;
        private System.Windows.Forms.GroupBox groupBox1;
    }
}