namespace TestCS.Main
{
    partial class MainForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(713, 415);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Next";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(124, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Image viewing app";
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "Enemy.gif");
            this.imageList1.Images.SetKeyName(1, "fireBallDark.bmp");
            this.imageList1.Images.SetKeyName(2, "floor.bmp");
            this.imageList1.Images.SetKeyName(3, "fon.bmp");
            this.imageList1.Images.SetKeyName(4, "Grass.bmp");
            this.imageList1.Images.SetKeyName(5, "hit.bmp");
            this.imageList1.Images.SetKeyName(6, "House.bmp");
            this.imageList1.Images.SetKeyName(7, "HouseMC.bmp");
            this.imageList1.Images.SetKeyName(8, "houseWall.bmp");
            this.imageList1.Images.SetKeyName(9, "hpBar.bmp");
            this.imageList1.Images.SetKeyName(10, "Steve.bmp");
            this.imageList1.Images.SetKeyName(11, "SteveMask.bmp");
            this.imageList1.Images.SetKeyName(12, "SteveMaskR.bmp");
            this.imageList1.Images.SetKeyName(13, "SteveR.bmp");
            this.imageList1.Images.SetKeyName(14, "stoneGrassed.bmp");
            this.imageList1.Images.SetKeyName(15, "TreeBig.bmp");
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ImageList imageList1;
    }
}