using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Threading;
using System.Threading.Tasks;
using Accord;
using Accord.Imaging.Filters;
using Accord.Vision.Detection;
using Accord.Vision.Detection.Cascades;
using AForge.Imaging;
using AForge.Video;
using AForge.Video.DirectShow;

namespace FaceFind
{
    public partial class Form1 : Form
    {
        private VideoCaptureDevice _camVideoInput;
        public Form1()
        {
            InitializeComponent();
        }
        private int t = DateTime.Now.Millisecond;
        private void button1_Click(object sender, EventArgs e)
        {
            var videoList = new FilterInfoCollection(FilterCategory.VideoInputDevice);
            foreach (FilterInfo i in videoList)
            {
                camList.Items.Add(i.Name);
            }
            camList.SelectedIndex = 0;
            camList.Items.Add($"Camera selected : {camList.Items[camList.SelectedIndex]}");

            _camVideoInput = new VideoCaptureDevice(videoList[camList.SelectedIndex].MonikerString);
            _camVideoInput.NewFrame += video_NewFrame;
            _camVideoInput.Start();
            Thread.Sleep(5000);
            _camVideoInput.SignalToStop();
        }

        private void pictureBox2Imaging(object bmpBitmap)
        {
            FaceFindAlgorythm faceFind = new FaceFindAlgorythm((Bitmap)bmpBitmap);
            pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox2.Image = faceFind.DrawBitmap();
        }
        private void video_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            Bitmap bmp = (Bitmap)eventArgs.Frame.Clone();
            Bitmap bmp1 = (Bitmap) eventArgs.Frame.Clone();
            FaceFindAlgorythm faceFind = new FaceFindAlgorythm(bmp);
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox1.Image = /*faceFind.DrawBitmap(ref richTextBox1);*/bmp1;
            
            pictureBox2.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBox2.Image = faceFind.DrawBitmap();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (_camVideoInput != null)
            {
                _camVideoInput.SignalToStop();
                _camVideoInput.WaitForStop();
            }
        }

        private Bitmap FaceFind(Bitmap bmpBitmap)
        {
            HaarObjectDetector faceDetector = new HaarObjectDetector(new FaceHaarCascade(), minSize: 300, searchMode: ObjectDetectorSearchMode.Single);
            RectanglesMarker faceMarker = new RectanglesMarker(Color.Red)
            {
                Rectangles = faceDetector.ProcessFrame(bmpBitmap)
            };
            faceMarker.ApplyInPlace(bmpBitmap);
            return bmpBitmap;
        }
    }

    public class FaceFindAlgorythm : Form
    {
        private readonly Bitmap _sourceBitmap;
        private Bitmap _processBitmap;
        private RichTextBox _richTextBox;

        private RGB[] SkinRgbs { get; } =
        {
            new RGB(255, 220, 177),
            new RGB(229, 194, 152),
            new RGB(228, 185, 142),
            new RGB(226, 185, 143),
            new RGB(227, 161, 115),
            new RGB(217, 145, 100),
            new RGB(204, 132, 67),
            new RGB(199, 122, 88),
            new RGB(165, 57, 0),
            new RGB(134, 4, 0),
            new RGB(113, 2, 0),
            new RGB(68, 0, 0),
            new RGB(225, 224, 196),
            new RGB(238, 207, 180),
            new RGB(222, 171, 127),
            new RGB(224, 177, 132),
            new RGB(223, 166, 117),
            new RGB(190, 114, 60),
            new RGB(100, 25, 0),
            new RGB(91, 0, 0),
            //new RGB(0,0,0), 
            new RGB(253, 228, 200),
            new RGB(239, 214, 189),
            new RGB(234, 189, 157),
            new RGB(227, 194, 124),
            new RGB(223, 185, 151),
            new RGB(208, 146, 110),
            new RGB(189, 151, 120),
            new RGB(187, 109, 74),
            new RGB(148, 10, 0),
            new RGB(225, 173, 164),
            new RGB(165, 136, 105),
            new RGB(123, 0, 0),
            new RGB(114, 0, 0),
            new RGB(56, 0, 0)
        };

        public FaceFindAlgorythm(Bitmap source)
        {
            _sourceBitmap = source;
        }

       // private Bitmap _processBitmap;
        private void FaceDetect()
        {
            _processBitmap = /*ConvolutionFilter(_sourceBitmap, xSobel, ySobel);*/ new Bitmap(_sourceBitmap.Width, _sourceBitmap.Height);
            Bitmap tmpBitmap = ConvolutionFilter(_sourceBitmap, xSobel, ySobel);
            int x;
            int width = _processBitmap.Width, height = _processBitmap.Height;
            Graphics g = Graphics.FromImage(_sourceBitmap);
            for (x = 0; x < width; x++)
            {
                int y;
                for (y = 0; y < height; y++)
                {
                    if (_sourceBitmap.GetPixel(x, y) == Color.WhiteSmoke)
                    {
                        _processBitmap.SetPixel(x, y, Color.White);
                        // g.DrawRectangle(new Pen(Color.Red,5), new Rectangle(x,y,500,500));
                        //return;
                    }
                }
            }
        }

        
        //Sobel operator kernel for horizontal pixel changes
        private static double[,] xSobel
        {
            get
            {
                return new double[,]
                {
                    { -1, 0, 1 },
                    { -2, 0, 2 },
                    { -1, 0, 1 }
                };
            }
        }

        //Sobel operator kernel for vertical pixel changes
        private static double[,] ySobel
        {
            get
            {
                return new double[,]
                {
                    {  1,  2,  1 },
                    {  0,  0,  0 },
                    { -1, -2, -1 }
                };
            }
        }

        private static Bitmap ConvolutionFilter(Bitmap sourceImage, double[,] xkernel, double[,] ykernel, double factor = 1, int bias = 0, bool grayscale = false)
        {

            //Image dimensions stored in variables for convenience
            int width = sourceImage.Width;
            int height = sourceImage.Height;

            //Lock source image bits into system memory
            BitmapData srcData = sourceImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

            //Get the total number of bytes in your image - 32 bytes per pixel x image width x image height -> for 32bpp images
            int bytes = srcData.Stride * srcData.Height;


            //Create byte arrays to hold pixel information of your image
            byte[] pixelBuffer = new byte[bytes];
            byte[] resultBuffer = new byte[bytes];

            //Get the address of the first pixel data
            IntPtr srcScan0 = srcData.Scan0;

            //Copy image data to one of the byte arrays
            Marshal.Copy(srcScan0, pixelBuffer, 0, bytes);

            //Unlock bits from system memory -> we have all our needed info in the array
            sourceImage.UnlockBits(srcData);

            //Convert your image to grayscale if necessary
            if (grayscale == true)
            {
                float rgb = 0;
                for (int i = 0; i < pixelBuffer.Length; i += 4)
                {
                    rgb = pixelBuffer[i] * .21f;
                    rgb += pixelBuffer[i + 1] * .71f;
                    rgb += pixelBuffer[i + 2] * .071f;
                    pixelBuffer[i] = (byte)rgb;
                    pixelBuffer[i + 1] = pixelBuffer[i];
                    pixelBuffer[i + 2] = pixelBuffer[i];
                    pixelBuffer[i + 3] = 255;
                }
            }

            //Create variable for pixel data for each kernel
            double xr = 0.0;
            double xg = 0.0;
            double xb = 0.0;
            double yr = 0.0;
            double yg = 0.0;
            double yb = 0.0;
            double rt = 0.0;
            double gt = 0.0;
            double bt = 0.0;

            //This is how much your center pixel is offset from the border of your kernel
            //Sobel is 3x3, so center is 1 pixel from the kernel border
            int filterOffset = 1;
            int calcOffset = 0;
            int byteOffset = 0;

            //Start with the pixel that is offset 1 from top and 1 from the left side
            //this is so entire kernel is on your image
            for (int OffsetY = filterOffset; OffsetY < height - filterOffset; OffsetY++)
            {
                for (int OffsetX = filterOffset; OffsetX < width - filterOffset; OffsetX++)
                {
                    //reset rgb values to 0
                    xr = xg = xb = yr = yg = yb = 0;
                    rt = gt = bt = 0.0;

                    //position of the kernel center pixel
                    byteOffset = OffsetY * srcData.Stride + OffsetX * 4;

                    //kernel calculations
                    for (int filterY = -filterOffset; filterY <= filterOffset; filterY++)
                    {
                        for (int filterX = -filterOffset; filterX <= filterOffset; filterX++)
                        {
                            calcOffset = byteOffset + filterX * 4 + filterY * srcData.Stride;
                            xb += (double)(pixelBuffer[calcOffset]) * xkernel[filterY + filterOffset, filterX + filterOffset];
                            xg += (double)(pixelBuffer[calcOffset + 1]) * xkernel[filterY + filterOffset, filterX + filterOffset];
                            xr += (double)(pixelBuffer[calcOffset + 2]) * xkernel[filterY + filterOffset, filterX + filterOffset];
                            yb += (double)(pixelBuffer[calcOffset]) * ykernel[filterY + filterOffset, filterX + filterOffset];
                            yg += (double)(pixelBuffer[calcOffset + 1]) * ykernel[filterY + filterOffset, filterX + filterOffset];
                            yr += (double)(pixelBuffer[calcOffset + 2]) * ykernel[filterY + filterOffset, filterX + filterOffset]; 
                        }
                    }

                    //total rgb values for this pixel
                    bt = Math.Sqrt((xb * xb) + (yb * yb));
                    gt = Math.Sqrt((xg * xg) + (yg * yg));
                    rt = Math.Sqrt((xr * xr) + (yr * yr));

                    //set limits, bytes can hold values from 0 up to 255;
                    if (bt > 255) bt = 255;
                    else if (bt < 0) bt = 0;
                    if (gt > 255) gt = 255;
                    else if (gt < 0) gt = 0;
                    if (rt > 255) rt = 255;
                    else if (rt < 0) rt = 0;

                    //set new data in the other byte array for your image data
                    resultBuffer[byteOffset] = (byte)(bt);
                    resultBuffer[byteOffset + 1] = (byte)(gt);
                    resultBuffer[byteOffset + 2] = (byte)(rt);
                    resultBuffer[byteOffset + 3] = 255;
                }
            }

            //Create new bitmap which will hold the processed data
            Bitmap resultImage = new Bitmap(width, height);

            //Lock bits into system memory
            BitmapData resultData = resultImage.LockBits(new Rectangle(0, 0, width, height), ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);

            //Copy from byte array that holds processed data to bitmap
            Marshal.Copy(resultBuffer, 0, resultData.Scan0, resultBuffer.Length);

            //Unlock bits from system memory
            resultImage.UnlockBits(resultData);

            //Return processed image
            return resultImage;
        }
        
        public Bitmap DrawBitmap()
        {
            FaceDetect();
            return  _processBitmap;
        }
        public Bitmap DrawBitmap(ref RichTextBox richTextBox)
        {
            this._richTextBox = richTextBox;
            this._richTextBox.Multiline = true;
            FaceDetect();
            return _sourceBitmap;
        }
    }

}
