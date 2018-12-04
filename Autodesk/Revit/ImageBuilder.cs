using System;
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Drawing;
using System.Drawing.Imaging;
using System.Drawing.Drawing2D;

using System.Windows.Media.Imaging;

namespace RhinoInside
{
  static class ImageBuilder
  {
    static internal BitmapImage LoadBitmapImage(string name)
    {
      using (var resource = Assembly.GetExecutingAssembly().GetManifestResourceStream(name))
      {
        var bitmapImage = new BitmapImage();
        bitmapImage.BeginInit();
        bitmapImage.StreamSource = resource;
        bitmapImage.EndInit();
        return bitmapImage;
      }
    }

    public static BitmapImage ToBitmapImage(this Bitmap bitmap)
    {
      using (var memory = new MemoryStream())
      {
        bitmap.Save(memory, ImageFormat.Png);
        memory.Position = 0;

        var bitmapImage = new BitmapImage();
        bitmapImage.BeginInit();
        bitmapImage.StreamSource = memory;
        bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
        bitmapImage.EndInit();
        bitmapImage.Freeze();

        return bitmapImage;
      }
    }

    static public Bitmap BuildIcon(string tag, int width = 24, int height = 24)
    {
      var bitmap = new Bitmap(width, height);
      var g = System.Drawing.Graphics.FromImage(bitmap);

      g.SmoothingMode = SmoothingMode.AntiAlias;
      g.InterpolationMode = InterpolationMode.HighQualityBicubic;
      g.PixelOffsetMode = PixelOffsetMode.HighQuality;
      float offset = 0.25f * (float) tag.Length;
      var rect = new RectangleF(0.0f + offset, 1.0f + offset, width, height);

      var format = new StringFormat()
      {
        Alignment = StringAlignment.Center,
        LineAlignment = StringAlignment.Center
      };

      g.FillEllipse(Brushes.Black, new Rectangle(1, 1, width - 1, height - 1));
      g.DrawString(tag, new System.Drawing.Font("Calibri", (width - 1) / (float) tag.Length, GraphicsUnit.Pixel), Brushes.White, rect, format);
      return bitmap;
    }

    static public System.Windows.Media.ImageSource BuildImage(string tag)
    {
      return BuildIcon(tag, 32, 32).ToBitmapImage();
    }
  }
}
