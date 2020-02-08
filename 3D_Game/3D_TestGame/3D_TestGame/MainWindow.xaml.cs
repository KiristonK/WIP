using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using HelixToolkit;
using HelixToolkit.Wpf;
using HelixToolkit.Wpf.Properties;

namespace _3D_TestGame
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("User32.dll")]
        private static extern bool SetCursorPos(int X, int Y);

        private static Point _globPos;
        public MainWindow()
        {
            InitializeComponent();
            this.Width = SystemParameters.WorkArea.Width;
            this.Height = SystemParameters.WorkArea.Height;
            _globPos = new Point(Width / 2, Height / 2);

        }

        private void ButtonBase_OnClick(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void MainWindow_OnMouseEnter(object sender, MouseEventArgs e)
        {
            //Mouse.OverrideCursor = Cursors.None;
        }

        private void MainWindow_OnMouseMove(object sender, MouseEventArgs e)
        {
            var curPos = e.MouseDevice.GetPosition(this);
            var testBtnMargin = TestBtn.Margin;
            testBtnMargin.Top = _globPos.Y - curPos.Y;
            testBtnMargin.Left = _globPos.X - curPos.X;
            Values.Text = "midPos: " + _globPos.X + " " + _globPos.Y
                + "\ncurPos: " + curPos.X + " " + curPos.Y + "\nMarginBtn: " + testBtnMargin.Top + " " +
                          testBtnMargin.Bottom + " " + testBtnMargin.Left + " " + testBtnMargin.Right;
            TestBtn.Margin = testBtnMargin;
            //SetCursorPos(Convert.ToInt32(_globPos.X), Convert.ToInt32(_globPos.Y));
        }
    }
}
