using System;
using System.Text;
using System.IO.Ports;
using System.Threading;


public class PortChat
{
    static bool _continue;
    static SerialPort _serialPort;


    public static void Main()
    {
        Console.WriteLine("1 - COM1\n2 - COM2");
        int a = Convert.ToInt32(Console.ReadLine());
        string name;
        string message;
        StringComparer stringComparer = StringComparer.OrdinalIgnoreCase;
        Thread readThread = new Thread(Read);

        switch (a)
        {
            case 1:
                {
                    _serialPort = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.One);
                    break;
                }
            case 2:
                {
                    _serialPort = new SerialPort("COM2", 9600, Parity.None, 8, StopBits.One);
                    break;
                }
        }
        _serialPort.ReadTimeout = 500;
        _serialPort.WriteTimeout = 500;

        _serialPort.Open();
        _continue = true;
        readThread.Start();

        Console.Write("Name: ");
        name = Console.ReadLine();

        Console.WriteLine("E - exit\nC - change speed");

        while (_continue)
        {
            message = Console.ReadLine();

            if (stringComparer.Equals("e", message))
            {
                _continue = false;
            }
            else if (stringComparer.Equals("c", message))
            {
                int speed;
                do
                {
                    Console.WriteLine("Speeds: 110 150 300 600 1200 2400 4800 9600 19200 38400 57600 115200");
                    speed = Convert.ToInt32(Console.ReadLine());
                } while (speed != 110 && speed != 150 && speed != 300 && speed != 600 && speed != 1200 && speed != 2400 && speed != 4800 && speed != 9600 && speed != 19200 && speed != 38400 && speed != 57600 && speed != 115200);
                _serialPort.BaudRate = speed;
                Console.Write("New speed is: ");
                Console.Write(_serialPort.BaudRate);
                Console.Write("\n");
            }
            else
            {
                _serialPort.WriteLine(message);

            }
        }

        readThread.Join();
        _serialPort.Close();
    }

    public static void Read()
    {
        while (_continue)
        {
            try
            {
                string message = _serialPort.ReadLine();
                Console.WriteLine(message);
            }
            catch (TimeoutException) { }
        }
    }

}