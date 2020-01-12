using System.Text.RegularExpressions;

namespace ExamAppWinForm
{
    partial class Form1
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
            this.FromComBox = new System.Windows.Forms.ComboBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.ToComBox = new System.Windows.Forms.ComboBox();
            this.StartCurrency = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.EndCurrency = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.FromAmount = new System.Windows.Forms.TextBox();
            this.ResultAmount = new System.Windows.Forms.TextBox();
            this.ResultLabel = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // ToComBox
            // 
            this.ToComBox.FormattingEnabled = true;
            this.ToComBox.Location = new System.Drawing.Point(454, 90);
            this.ToComBox.Name = "ToComBox";
            this.ToComBox.Size = new System.Drawing.Size(442, 24);
            this.ToComBox.TabIndex = 3;
            this.ToComBox.SelectedValueChanged += new System.EventHandler(this.ToComBox_SelectedValueChanged);
            // 
            // FromComBox
            // 
            this.FromComBox.FormattingEnabled = true;
            this.FromComBox.Location = new System.Drawing.Point(454, 43);
            this.FromComBox.Name = "FromComBox";
            this.FromComBox.Size = new System.Drawing.Size(442, 24);
            this.FromComBox.TabIndex = 0;
            this.FromComBox.SelectedValueChanged += new System.EventHandler(this.FromComBox_SelectedValueChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(908, 28);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(54, 24);
            this.saveToolStripMenuItem.Text = "Save";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(47, 24);
            this.exitToolStripMenuItem.Text = "Exit";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Lucida Sans", 30F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(13, 32);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(327, 35);
            this.label1.TabIndex = 2;
            this.label1.Text = "Wybierz walute bazową";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Lucida Sans", 30F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(13, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(350, 35);
            this.label2.TabIndex = 4;
            this.label2.Text = "Wybierz walute docelową";
            // 
            // StartCurrency
            // 
            this.StartCurrency.AutoSize = true;
            this.StartCurrency.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.StartCurrency.Location = new System.Drawing.Point(16, 140);
            this.StartCurrency.Name = "StartCurrency";
            this.StartCurrency.Size = new System.Drawing.Size(50, 25);
            this.StartCurrency.TabIndex = 5;
            this.StartCurrency.Text = "PLN";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(171, 140);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(34, 25);
            this.label4.TabIndex = 6;
            this.label4.Text = "do";
            // 
            // EndCurrency
            // 
            this.EndCurrency.AutoSize = true;
            this.EndCurrency.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.EndCurrency.Location = new System.Drawing.Point(211, 140);
            this.EndCurrency.Name = "EndCurrency";
            this.EndCurrency.Size = new System.Drawing.Size(50, 25);
            this.EndCurrency.TabIndex = 7;
            this.EndCurrency.Text = "PLN";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(267, 140);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(101, 25);
            this.label6.TabIndex = 8;
            this.label6.Text = "otrzymasz";
            // 
            // FromAmount
            // 
            this.FromAmount.Location = new System.Drawing.Point(65, 143);
            this.FromAmount.Name = "FromAmount";
            this.FromAmount.Size = new System.Drawing.Size(100, 22);
            this.FromAmount.TabIndex = 9;
            this.FromAmount.Text = "0";
            this.FromAmount.WordWrap = false;
            this.FromAmount.TextChanged += new System.EventHandler(this.Input_TextChanged);
            // 
            // ResultAmount
            // 
            this.ResultAmount.Location = new System.Drawing.Point(374, 144);
            this.ResultAmount.Name = "ResultAmount";
            this.ResultAmount.ReadOnly = true;
            this.ResultAmount.Size = new System.Drawing.Size(466, 22);
            this.ResultAmount.TabIndex = 11;
            // 
            // ResultLabel
            // 
            this.ResultLabel.AutoSize = true;
            this.ResultLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Pixel, ((byte)(204)));
            this.ResultLabel.Location = new System.Drawing.Point(846, 140);
            this.ResultLabel.Name = "ResultLabel";
            this.ResultLabel.Size = new System.Drawing.Size(50, 25);
            this.ResultLabel.TabIndex = 12;
            this.ResultLabel.Text = "PLN";
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.button1.Location = new System.Drawing.Point(703, 182);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(193, 42);
            this.button1.TabIndex = 13;
            this.button1.Text = "Wymień waluty";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(908, 458);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.ResultLabel);
            this.Controls.Add(this.ResultAmount);
            this.Controls.Add(this.FromAmount);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.EndCurrency);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.StartCurrency);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.ToComBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.FromComBox);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox FromComBox;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox ToComBox;
        private System.Windows.Forms.Label StartCurrency;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label EndCurrency;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox FromAmount;
        private System.Windows.Forms.TextBox ResultAmount;
        private System.Windows.Forms.Label ResultLabel;
        private System.Windows.Forms.Button button1;
    }
}

