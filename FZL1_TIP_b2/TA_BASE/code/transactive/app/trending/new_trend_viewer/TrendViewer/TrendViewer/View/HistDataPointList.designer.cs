namespace TrendViewer.View
{
    partial class HistDataPointList
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            this.dataPointListDataGridViewprogressBar = new System.Windows.Forms.ProgressBar();
            this.histDpListGrpBox = new System.Windows.Forms.GroupBox();
            this.dataPointListDataGridView = new System.Windows.Forms.DataGridView();
            this.panel3 = new System.Windows.Forms.Panel();
            this.pageNumDataPointListDataGridView = new System.Windows.Forms.NumericUpDown();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.firstdataPointListDataGridView = new System.Windows.Forms.ToolStripButton();
            this.prevdataPointListDataGridView = new System.Windows.Forms.ToolStripButton();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.nextdataPointListDataGridView = new System.Windows.Forms.ToolStripButton();
            this.lastdataPointListDataGridView = new System.Windows.Forms.ToolStripButton();
            this.totalDataPointListDataGridView = new System.Windows.Forms.ToolStripLabel();
            this.TotalPage_Tlbl = new System.Windows.Forms.ToolStripLabel();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addDataPointToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadDataConfigToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveDataConfigToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.histDpListGrpBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataPointListDataGridView)).BeginInit();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pageNumDataPointListDataGridView)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataPointListDataGridViewprogressBar
            // 
            this.dataPointListDataGridViewprogressBar.ForeColor = System.Drawing.Color.Lime;
            this.dataPointListDataGridViewprogressBar.Location = new System.Drawing.Point(104, 124);
            this.dataPointListDataGridViewprogressBar.Name = "dataPointListDataGridViewprogressBar";
            this.dataPointListDataGridViewprogressBar.Size = new System.Drawing.Size(889, 23);
            this.dataPointListDataGridViewprogressBar.TabIndex = 15;
            // 
            // histDpListGrpBox
            // 
            this.histDpListGrpBox.BackColor = System.Drawing.Color.Transparent;
            this.histDpListGrpBox.Controls.Add(this.dataPointListDataGridViewprogressBar);
            this.histDpListGrpBox.Controls.Add(this.dataPointListDataGridView);
            this.histDpListGrpBox.Location = new System.Drawing.Point(12, 12);
            this.histDpListGrpBox.Name = "histDpListGrpBox";
            this.histDpListGrpBox.Size = new System.Drawing.Size(1096, 270);
            this.histDpListGrpBox.TabIndex = 7;
            this.histDpListGrpBox.TabStop = false;
            this.histDpListGrpBox.Text = "Historical Datapoint List";
            // 
            // dataPointListDataGridView
            // 
            this.dataPointListDataGridView.AllowUserToAddRows = false;
            this.dataPointListDataGridView.AllowUserToDeleteRows = false;
            this.dataPointListDataGridView.AllowUserToOrderColumns = true;
            this.dataPointListDataGridView.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            dataGridViewCellStyle1.FormatProvider = new System.Globalization.CultureInfo("en-US");
            this.dataPointListDataGridView.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.dataPointListDataGridView.BackgroundColor = System.Drawing.SystemColors.Window;
            this.dataPointListDataGridView.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.dataPointListDataGridView.ColumnHeadersHeight = 24;
            this.dataPointListDataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
            this.dataPointListDataGridView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataPointListDataGridView.EditMode = System.Windows.Forms.DataGridViewEditMode.EditProgrammatically;
            this.dataPointListDataGridView.Location = new System.Drawing.Point(3, 18);
            this.dataPointListDataGridView.MultiSelect = false;
            this.dataPointListDataGridView.Name = "dataPointListDataGridView";
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleCenter;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle2.FormatProvider = new System.Globalization.CultureInfo("en-US");
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataPointListDataGridView.RowHeadersDefaultCellStyle = dataGridViewCellStyle2;
            this.dataPointListDataGridView.RowHeadersVisible = false;
            this.dataPointListDataGridView.RowTemplate.Height = 23;
            this.dataPointListDataGridView.Size = new System.Drawing.Size(1090, 249);
            this.dataPointListDataGridView.TabIndex = 4;
            this.dataPointListDataGridView.Text = "dataGridView2";
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.Transparent;
            this.panel3.Controls.Add(this.pageNumDataPointListDataGridView);
            this.panel3.Controls.Add(this.toolStrip1);
            this.panel3.Location = new System.Drawing.Point(12, 289);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(1093, 24);
            this.panel3.TabIndex = 56;
            // 
            // pageNumDataPointListDataGridView
            // 
            this.pageNumDataPointListDataGridView.Location = new System.Drawing.Point(69, 1);
            this.pageNumDataPointListDataGridView.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.pageNumDataPointListDataGridView.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.pageNumDataPointListDataGridView.Name = "pageNumDataPointListDataGridView";
            this.pageNumDataPointListDataGridView.Size = new System.Drawing.Size(102, 22);
            this.pageNumDataPointListDataGridView.TabIndex = 7;
            this.pageNumDataPointListDataGridView.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // toolStrip1
            // 
            this.toolStrip1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.firstdataPointListDataGridView,
            this.prevdataPointListDataGridView,
            this.toolStripTextBox1,
            this.nextdataPointListDataGridView,
            this.lastdataPointListDataGridView,
            this.totalDataPointListDataGridView,
            this.TotalPage_Tlbl});
            this.toolStrip1.Location = new System.Drawing.Point(0, -1);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1093, 25);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // firstdataPointListDataGridView
            // 
            this.firstdataPointListDataGridView.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.firstdataPointListDataGridView.Image = global::TrendViewer.Properties.Resources.PreviousEnd;
            this.firstdataPointListDataGridView.ImageTransparentColor = System.Drawing.Color.Transparent;
            this.firstdataPointListDataGridView.Name = "firstdataPointListDataGridView";
            this.firstdataPointListDataGridView.Size = new System.Drawing.Size(23, 22);
            this.firstdataPointListDataGridView.Click += new System.EventHandler(this.firstdataPointListDataGridView_Click);
            // 
            // prevdataPointListDataGridView
            // 
            this.prevdataPointListDataGridView.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.prevdataPointListDataGridView.Image = global::TrendViewer.Properties.Resources.Previous;
            this.prevdataPointListDataGridView.ImageTransparentColor = System.Drawing.Color.Transparent;
            this.prevdataPointListDataGridView.Margin = new System.Windows.Forms.Padding(0, 1, 5, 2);
            this.prevdataPointListDataGridView.Name = "prevdataPointListDataGridView";
            this.prevdataPointListDataGridView.Size = new System.Drawing.Size(23, 22);
            this.prevdataPointListDataGridView.Click += new System.EventHandler(this.prevdataPointListDataGridView_Click);
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.Margin = new System.Windows.Forms.Padding(10, 0, 1, 0);
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(100, 25);
            // 
            // nextdataPointListDataGridView
            // 
            this.nextdataPointListDataGridView.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.nextdataPointListDataGridView.Image = global::TrendViewer.Properties.Resources.Next;
            this.nextdataPointListDataGridView.ImageTransparentColor = System.Drawing.Color.Transparent;
            this.nextdataPointListDataGridView.Margin = new System.Windows.Forms.Padding(5, 1, 0, 2);
            this.nextdataPointListDataGridView.Name = "nextdataPointListDataGridView";
            this.nextdataPointListDataGridView.Size = new System.Drawing.Size(23, 22);
            this.nextdataPointListDataGridView.Click += new System.EventHandler(this.nextdataPointListDataGridView_Click);
            // 
            // lastdataPointListDataGridView
            // 
            this.lastdataPointListDataGridView.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.lastdataPointListDataGridView.Image = global::TrendViewer.Properties.Resources.NextEnd;
            this.lastdataPointListDataGridView.ImageTransparentColor = System.Drawing.Color.Transparent;
            this.lastdataPointListDataGridView.Name = "lastdataPointListDataGridView";
            this.lastdataPointListDataGridView.Size = new System.Drawing.Size(23, 22);
            this.lastdataPointListDataGridView.Click += new System.EventHandler(this.lastdataPointListDataGridView_Click);
            // 
            // totalDataPointListDataGridView
            // 
            this.totalDataPointListDataGridView.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.totalDataPointListDataGridView.Name = "totalDataPointListDataGridView";
            this.totalDataPointListDataGridView.Size = new System.Drawing.Size(13, 22);
            this.totalDataPointListDataGridView.Text = "0";
            // 
            // TotalPage_Tlbl
            // 
            this.TotalPage_Tlbl.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.TotalPage_Tlbl.Name = "TotalPage_Tlbl";
            this.TotalPage_Tlbl.Size = new System.Drawing.Size(77, 22);
            this.TotalPage_Tlbl.Text = "Total Page :    ";
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addDataPointToolStripMenuItem,
            this.loadDataConfigToolStripMenuItem,
            this.saveDataConfigToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(238, 70);
            // 
            // addDataPointToolStripMenuItem
            // 
            this.addDataPointToolStripMenuItem.Name = "addDataPointToolStripMenuItem";
            this.addDataPointToolStripMenuItem.Size = new System.Drawing.Size(237, 22);
            this.addDataPointToolStripMenuItem.Text = "Add Datapoint Configuration";
            // 
            // loadDataConfigToolStripMenuItem
            // 
            this.loadDataConfigToolStripMenuItem.Name = "loadDataConfigToolStripMenuItem";
            this.loadDataConfigToolStripMenuItem.Size = new System.Drawing.Size(237, 22);
            this.loadDataConfigToolStripMenuItem.Text = "Load Historical Data Configuration";
            // 
            // saveDataConfigToolStripMenuItem
            // 
            this.saveDataConfigToolStripMenuItem.Name = "saveDataConfigToolStripMenuItem";
            this.saveDataConfigToolStripMenuItem.Size = new System.Drawing.Size(237, 22);
            this.saveDataConfigToolStripMenuItem.Text = "Save Datapoint Configuration";
            // 
            // HistDataPointList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.WhiteSmoke;
            this.ClientSize = new System.Drawing.Size(1120, 325);
            this.ContextMenuStrip = this.contextMenuStrip1;
            this.Controls.Add(this.histDpListGrpBox);
            this.Controls.Add(this.panel3);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "HistDataPointList";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Historical Datapoint Viewer";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.DataPointHistoryViewer_Paint);
            this.histDpListGrpBox.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataPointListDataGridView)).EndInit();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pageNumDataPointListDataGridView)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.contextMenuStrip1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ProgressBar dataPointListDataGridViewprogressBar;
        private System.Windows.Forms.GroupBox histDpListGrpBox;
        private System.Windows.Forms.DataGridView dataPointListDataGridView;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.NumericUpDown pageNumDataPointListDataGridView;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton firstdataPointListDataGridView;
        private System.Windows.Forms.ToolStripButton prevdataPointListDataGridView;
        private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
        private System.Windows.Forms.ToolStripButton nextdataPointListDataGridView;
        private System.Windows.Forms.ToolStripButton lastdataPointListDataGridView;
        private System.Windows.Forms.ToolStripLabel totalDataPointListDataGridView;
        private System.Windows.Forms.ToolStripLabel TotalPage_Tlbl;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem addDataPointToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadDataConfigToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveDataConfigToolStripMenuItem;
    }
}
