namespace testTheInstallDll
{
    partial class FormOfUrl
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btn_url_add = new System.Windows.Forms.Button();
            this.btn_load_ruleOfUrl = new System.Windows.Forms.Button();
            this.btn_url_delete = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.lstOfUrlRule = new System.Windows.Forms.ListBox();
            this.txt_url_Input = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btn_url_add);
            this.groupBox1.Controls.Add(this.btn_load_ruleOfUrl);
            this.groupBox1.Controls.Add(this.btn_url_delete);
            this.groupBox1.Location = new System.Drawing.Point(340, 35);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(135, 116);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            // 
            // btn_url_add
            // 
            this.btn_url_add.Location = new System.Drawing.Point(31, 20);
            this.btn_url_add.Name = "btn_url_add";
            this.btn_url_add.Size = new System.Drawing.Size(75, 23);
            this.btn_url_add.TabIndex = 1;
            this.btn_url_add.Text = "添加";
            this.btn_url_add.UseVisualStyleBackColor = true;
            this.btn_url_add.Click += new System.EventHandler(this.btn_url_add_Click);
            // 
            // btn_load_ruleOfUrl
            // 
            this.btn_load_ruleOfUrl.Location = new System.Drawing.Point(31, 78);
            this.btn_load_ruleOfUrl.Name = "btn_load_ruleOfUrl";
            this.btn_load_ruleOfUrl.Size = new System.Drawing.Size(75, 23);
            this.btn_load_ruleOfUrl.TabIndex = 5;
            this.btn_load_ruleOfUrl.Text = "导入规则";
            this.btn_load_ruleOfUrl.UseVisualStyleBackColor = true;
            this.btn_load_ruleOfUrl.Click += new System.EventHandler(this.btn_load_ruleOfUrl_Click);
            // 
            // btn_url_delete
            // 
            this.btn_url_delete.Enabled = false;
            this.btn_url_delete.Location = new System.Drawing.Point(31, 49);
            this.btn_url_delete.Name = "btn_url_delete";
            this.btn_url_delete.Size = new System.Drawing.Size(75, 23);
            this.btn_url_delete.TabIndex = 3;
            this.btn_url_delete.Text = "删除";
            this.btn_url_delete.UseVisualStyleBackColor = true;
            this.btn_url_delete.Click += new System.EventHandler(this.btn_url_delete_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(56, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "  URL：";
            // 
            // lstOfUrlRule
            // 
            this.lstOfUrlRule.FormattingEnabled = true;
            this.lstOfUrlRule.ItemHeight = 12;
            this.lstOfUrlRule.Location = new System.Drawing.Point(58, 99);
            this.lstOfUrlRule.Name = "lstOfUrlRule";
            this.lstOfUrlRule.Size = new System.Drawing.Size(252, 172);
            this.lstOfUrlRule.TabIndex = 8;
            this.lstOfUrlRule.MouseClick += new System.Windows.Forms.MouseEventHandler(this.lstOfUrlRule_MouseClick);
            // 
            // txt_url_Input
            // 
            this.txt_url_Input.Location = new System.Drawing.Point(115, 35);
            this.txt_url_Input.Name = "txt_url_Input";
            this.txt_url_Input.Size = new System.Drawing.Size(143, 21);
            this.txt_url_Input.TabIndex = 7;
            // 
            // FormOfUrl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(528, 318);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lstOfUrlRule);
            this.Controls.Add(this.txt_url_Input);
            this.Name = "FormOfUrl";
            this.Text = "FormOfUrl";
            this.Load += new System.EventHandler(this.FormOfUrl_Load);
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btn_url_add;
        private System.Windows.Forms.Button btn_load_ruleOfUrl;
        private System.Windows.Forms.Button btn_url_delete;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox lstOfUrlRule;
        private System.Windows.Forms.TextBox txt_url_Input;
    }
}