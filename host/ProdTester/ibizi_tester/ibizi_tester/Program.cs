using HidLibrary;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;

namespace ibizi_tester
{
    class Program
    {
        private const int VendorId = 0x1209;
        private const int ProductId = 0xB100;

        private static List<Color> _colors = new List<Color>()
        {
            new Color(0xff, 0xff, 0xff),
            new Color(0xff, 0x00, 0x00),
            new Color(0x00, 0xff, 0x00),
            new Color(0x00, 0x00, 0xff)
        };

        private static int _colorIndex = 0;

        private static Timer _timer = new Timer(1000);
        private static bool _connectedToDriver = false;
        private static HidDevice _device;

        static void Main(string[] args)
        {
            _timer.Elapsed += _timer_Elapsed;
            _device = HidDevices.Enumerate(VendorId, ProductId).FirstOrDefault();
            if (_device != null)
            {
                _device.OpenDevice();
                
                _device.Inserted += DeviceAttachedHandler;
                _device.Removed += DeviceRemovedHandler;

                _device.MonitorDeviceEvents = true;

                Console.WriteLine("Beginning test.");
                while(Console.ReadKey().Key != ConsoleKey.X)
                {
                    // wait and such
                }
                Console.WriteLine("Ending test.");

                _timer.Stop();
                _device.CloseDevice();
                return;

            }
            else
            {
                Console.WriteLine("Could not find device.");
                Console.ReadKey();
            }
        }

        private static void _timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            Console.WriteLine("Sending " + _colorIndex.ToString());

            var color = _colors[_colorIndex];

            SendColor(color.Red, color.Green, color.Blue);

            _colorIndex++;

            if(_colorIndex >= _colors.Count())
            {
                _colorIndex = 0;
            }
        }

        private static void DeviceRemovedHandler()
        {
            _connectedToDriver = false;
            _timer.Stop();
            _colorIndex = 0;
        }

        private static void DeviceAttachedHandler()
        {
            _connectedToDriver = true;
            _timer.Start();
        }

        private static void SendColor(byte red, byte green, byte blue)
        {
            if (_connectedToDriver)
            {
                byte[] data = new byte[9];
                data[0] = 0x00; // reportid
                data[1] = red;
                data[2] = green;
                data[3] = blue;

                _device.Write(data);
            }
        }
    }

    public class Color
    {
        public Color(byte red, byte green, byte blue)
        {
            Red = red;
            Green = green;
            Blue = blue;
        }

        public byte Red { get; set; }
        public byte Green { get; set; }
        public byte Blue { get; set; }

    }
}
