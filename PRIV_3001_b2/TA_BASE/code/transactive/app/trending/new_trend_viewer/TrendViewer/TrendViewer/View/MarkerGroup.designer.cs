namespace TrendViewer.View
{
    partial class MarkerGroup
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
            this.configNameBox = new System.Windows.Forms.ComboBox();
            this.okCmd = new System.Windows.Forms.Button();
            this.cancelCmd = new System.Windows.Forms.Button();
            this.configNameLbl = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // configNameBox
            // 
            this.configNameBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.configNameBox.FormattingEnabled = true;
            this.configNameBox.Location = new System.Drawing.Point(181, 13);
            this.configNameBox.Name = "configNameBox";
            this.configNameBox.Size = new System.Drawing.Size(309, 24);
            this.configNameBox.TabIndex = 26;
            // 
            // okCmd
            // 
            this.okCmd.BackColor = System.Drawing.Color.Transparent;
            this.okCmd.Image = global::TrendViewer.Properties.Resources.Yes_v3;
            this.okCmd.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.okCmd.Location = new System.Drawing.Point(181, 44);
            this.okCmd.Margin = new System.Windows.Forms.Padding(4);
            this.okCmd.Name = "okCmd";
            this.okCmd.Size = new System.Drawing.Size(104, 31);
            this.okCmd.TabIndex = 24;
            this.okCmd.Text = "OK";
            this.okCmd.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.okCmd.UseVisualStyleBackColor = false;
            // 
            // cancelCmd
            // 
            this.cancelCmd.BackColor = System.Drawing.Color.Transparent;
            this.cancelCmd.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelCmd.Image = global::TrendViewer.Properties.Resources.Cancel;
            this.cancelCmd.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.cancelCmd.Location = new System.Drawing.Point(293, 44);
            this.cancelCmd.Margin = new System.Windows.Forms.Padding(4);
            this.cancelCmd.Name = "cancelCmd";
            this.cancelCmd.Size = new System.Drawing.Size(104, 31);
            this.cancelCmd.TabIndex = 25;
            this.cancelCmd.Text = "Cancel";
            this.cancelCmd.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.cancelCmd.UseVisualStyleBackColor = false;
            this.cancelCmd.Click += new System.EventHandler(this.cancelCmd_Click);
            // 
            // configNameLbl
            // 
            this.configNameLbl.BackColor = System.Drawing.Color.Transparent;
            this.configNameLbl.Location = new System.Drawing.Point(12, 16);
            this.configNameLbl.Name = "configNameLbl";
            this.configNameLbl.Size = new System.Drawing.Size(163, 16);
            this.configNameLbl.TabIndex = 23;
            this.configNameLbl.Text = "Configuration Name :";
            this.configNameLbl.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // MarkerGroup
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.WhiteSmoke;
            this.ClientSize = new System.Drawing.Size(536, 88);
            this.Controls.Add(this.configNameBox);
            this.Controls.Add(this.okCmd);
            this.Controls.Add(this.cancelCmd);
            this.Controls.Add(this.configNameLbl);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "MarkerGroup";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Load Marker Configuration";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.LoadConfigMarker_Paint);
            this.ResumeLayout(false);

        }

        #endregion

        internal System.Windows.Forms.ComboBox configNameBox;
        internal System.Windows.Forms.Button okCmd;
        private System.Windows.Forms.Button cancelCmd;
        private System.Windows.Forms.Label configNameLbl;
    }
}