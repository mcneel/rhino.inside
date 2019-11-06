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
using Color   = System.Drawing.Color;
using Brushes = System.Drawing.Brushes;

using System.Windows.Media.Imaging;
using System.Windows.Media;

namespace RhinoInside
{
  static class ImageBuilder
  {
    static internal BitmapImage LoadBitmapImage(string name, bool small = false)
    {
      using (var resource = Assembly.GetExecutingAssembly().GetManifestResourceStream(name))
      {
        var bitmapImage = new BitmapImage();
        bitmapImage.BeginInit();
        bitmapImage.StreamSource = resource;
        bitmapImage.EndInit();

        int desiredSize = small ? 16 : 32;
        if ((int) bitmapImage.Height != desiredSize || (int) bitmapImage.Width != desiredSize)
        {
          var scaledBitmapImage = new BitmapImage();
          scaledBitmapImage.BeginInit();
          scaledBitmapImage.StreamSource = resource;
          scaledBitmapImage.DecodePixelWidth  = (int) Math.Round(bitmapImage.PixelWidth  * (desiredSize / bitmapImage.Width));
          scaledBitmapImage.DecodePixelHeight = (int) Math.Round(bitmapImage.PixelHeight * (desiredSize / bitmapImage.Height));
          scaledBitmapImage.EndInit();

          return scaledBitmapImage;
        }

        return bitmapImage;
      }
    }

    public static System.Windows.Media.PixelFormat ToMediaPixelFormat(this System.Drawing.Imaging.PixelFormat pixelFormat)
    {
      switch (pixelFormat)
      {
        case System.Drawing.Imaging.PixelFormat.Format16bppGrayScale:
          return System.Windows.Media.PixelFormats.Gray16;
        case System.Drawing.Imaging.PixelFormat.Format16bppRgb555:
          return System.Windows.Media.PixelFormats.Bgr555;
        case System.Drawing.Imaging.PixelFormat.Format16bppRgb565:
          return System.Windows.Media.PixelFormats.Bgr565;

        case System.Drawing.Imaging.PixelFormat.Indexed:
          return System.Windows.Media.PixelFormats.Bgr101010;
        case System.Drawing.Imaging.PixelFormat.Format1bppIndexed:
          return System.Windows.Media.PixelFormats.Indexed1;
        case System.Drawing.Imaging.PixelFormat.Format4bppIndexed:
          return System.Windows.Media.PixelFormats.Indexed4;
        case System.Drawing.Imaging.PixelFormat.Format8bppIndexed:
          return System.Windows.Media.PixelFormats.Indexed8;

        case System.Drawing.Imaging.PixelFormat.Format16bppArgb1555:
          return System.Windows.Media.PixelFormats.Bgr555;

        case System.Drawing.Imaging.PixelFormat.Format24bppRgb:
          return System.Windows.Media.PixelFormats.Bgr24;

        case System.Drawing.Imaging.PixelFormat.Format32bppArgb:
          return System.Windows.Media.PixelFormats.Bgr32;
        case System.Drawing.Imaging.PixelFormat.Format32bppPArgb:
          return System.Windows.Media.PixelFormats.Pbgra32;
        case System.Drawing.Imaging.PixelFormat.Format32bppRgb:
          return System.Windows.Media.PixelFormats.Bgr32;

        case System.Drawing.Imaging.PixelFormat.Format48bppRgb:
          return System.Windows.Media.PixelFormats.Rgb48;

        case System.Drawing.Imaging.PixelFormat.Format64bppArgb:
          return System.Windows.Media.PixelFormats.Prgba64;
      }

      throw new NotSupportedException();
    }

    public static BitmapSource ToBitmapSource(this Icon icon, bool small = false)
    {
      using (var bitmap = icon.ToBitmap())
      {
        var bitmapData = bitmap.LockBits
        (
          new Rectangle(0, 0, bitmap.Width, bitmap.Height),
          ImageLockMode.ReadOnly, bitmap.PixelFormat
        );

        var mediaPixelFormat = bitmap.PixelFormat.ToMediaPixelFormat();
        var bitmapSource = BitmapSource.Create
        (
          bitmapData.Width, bitmapData.Height,
          small ? bitmap.HorizontalResolution * 2 : bitmap.HorizontalResolution,
          small ? bitmap.VerticalResolution   * 2 : bitmap.VerticalResolution,
          mediaPixelFormat, null,
          bitmapData.Scan0, bitmapData.Stride * bitmapData.Height, bitmapData.Stride
        );

        bitmap.UnlockBits(bitmapData);
        return bitmapSource;
      }
    }

    public static BitmapImage ToBitmapImage(this Bitmap bitmap, int PixelWidth = 0, int PixelHeight = 0)
    {
      using (var memory = new MemoryStream())
      {
        bitmap.Save(memory, ImageFormat.Png);
        memory.Position = 0;

        var bitmapImage = new BitmapImage();
        bitmapImage.BeginInit();
        bitmapImage.StreamSource = memory;
        bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
        bitmapImage.DecodePixelWidth = PixelWidth;
        bitmapImage.DecodePixelHeight = PixelHeight;
        bitmapImage.EndInit();
        bitmapImage.Freeze();

        return bitmapImage;
      }
    }

    public static Bitmap BuildIcon(string tag, int width = 24, int height = 24)
    {
      var bitmap = new Bitmap(width, height);
      using (var g = Graphics.FromImage(bitmap))
      {
        var iconBounds = new RectangleF(0, 0, width, height);
        iconBounds.Inflate(-0.5f, -0.5f);

        using (var capsule = Grasshopper.GUI.Canvas.GH_Capsule.CreateCapsule(iconBounds, Grasshopper.GUI.Canvas.GH_Palette.Transparent))
          capsule.Render(g, false, false, false);

        g.SmoothingMode = SmoothingMode.AntiAlias;
        g.InterpolationMode = InterpolationMode.HighQualityBicubic;
        g.PixelOffsetMode = PixelOffsetMode.HighQuality;
        var rect = new RectangleF(0.5f, 1.0f, width, height);

        var format = new StringFormat()
        {
          Alignment = StringAlignment.Center,
          LineAlignment = StringAlignment.Center
        };

        float emSize = ((float) (width) / ((float) tag.Length));
        if (width == 24)
        {
          switch (tag.Length)
          {
            case 1: emSize = 20.0f; break;
            case 2: emSize = 13.0f; break;
            case 3: emSize = 11.0f; break;
            case 4: emSize = 8.0f; break;
          }
        }

        // Avoid using ClearType rendering on icons that the user can zoom in like icons on Grashopper components.
        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAliasGridFit;

        using (var Calibri = new System.Drawing.Font("Calibri", emSize, GraphicsUnit.Pixel))
          g.DrawString(tag, Calibri, Brushes.Black, rect, format);
      }

      return bitmap;
    }

    public static Bitmap BuildIcon(Action<Graphics, Rectangle> action, int width = 24, int height = 24)
    {
      var bitmap = new Bitmap(width, height);
      using (var graphics = Graphics.FromImage(bitmap))
        action(graphics, new Rectangle(0, 0, width, height));

      return bitmap;
    }

    public static Bitmap BuildImage(string tag, int width, int height, Color color)
    {
      var bitmap = new Bitmap(width, height);
      using (var g = Graphics.FromImage(bitmap))
      {
        g.SmoothingMode = SmoothingMode.AntiAlias;
        g.InterpolationMode = InterpolationMode.HighQualityBicubic;
        g.PixelOffsetMode = PixelOffsetMode.HighQuality;
        var rect = new RectangleF(0.5f, 1.0f, width, height);

        var format = new StringFormat()
        {
          Alignment = StringAlignment.Center,
          LineAlignment = StringAlignment.Center
        };

        if (color.IsEmpty)
          g.FillEllipse(Brushes.Black, 1.0f, 1.0f, width - 2.0f, height - 2.0f);
        else using (var brush = new SolidBrush(color))
          g.FillEllipse(brush, 1.0f, 1.0f, width - 2.0f, height - 2.0f);

        float emSize = ((float) (width) / ((float) tag.Length));
        if (width == 24)
        {
          switch (tag.Length)
          {
            case 1: emSize = 20.0f; break;
            case 2: emSize = 13.0f; break;
            case 3: emSize = 11.0f; break;
            case 4: emSize = 8.0f; break;
          }
        }

        // Avoid using ClearType rendering on icons that the user can zoom in like icons on Grashopper components.
        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAliasGridFit;

        using (var Calibri = new System.Drawing.Font("Calibri", emSize, GraphicsUnit.Pixel))
          g.DrawString(tag, Calibri, Brushes.White, rect, format);
      }

      return bitmap;
    }

    public static ImageSource BuildImage(string tag, Color color = default(Color))
    {
      using (var g = Graphics.FromHwnd(Revit.Revit.MainWindowHandle))
      {
        int pixelX = (int) Math.Round((g.DpiX / 96.0) * 16);
        int pixelY = (int) Math.Round((g.DpiY / 96.0) * 16);
        return BuildImage(tag, 64, 64, color).ToBitmapImage(pixelX, pixelY);
      }
    }

    public static ImageSource BuildLargeImage(string tag, Color color = default(Color))
    {
      using (var g = Graphics.FromHwnd(Revit.Revit.MainWindowHandle))
      {
        int pixelX = (int) Math.Round((g.DpiX / 96.0) * 32);
        int pixelY = (int) Math.Round((g.DpiY / 96.0) * 32);
        return BuildImage(tag, 64, 64, color).ToBitmapImage(pixelX, pixelY);
      }
    }
  }
}
